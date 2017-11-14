//
//  main.cpp
//  最大流
//
//  Created by 伏开宇 on 2017/5/9.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Graph.hpp"
#include <queue>
#include <fstream>
#include <map>
#include <math.h>
//读取最短增广路径
void FindPath(LinkGraph* G, int t, vector<Edge* > &p, Edge** e){
    if(G->v[t]->p == nullptr)
        ;
    else{
        FindPath(G, G->v[t]->p->num, p, e);
        p.push_back(e[t]);
    }
}
//寻找增广路径,使用原图进行广搜，如果e(u,v).f < e(u,v).value 则存在u->v的边，如果e(u,v).f > 0 则存在v->u的边
bool FindAugmentRoute(LinkGraph* G, int s, int t, Edge** e, ListNode1** tail){
    for (int i = 1; i <= G->NumOfVertex; i++) {
        G->v[i]->p = nullptr;
        G->v[i]->color = 0;
    }
    ListQueue* Queue = new ListQueue;
    Queue->enqueue(s);
    G->v[s]->color = 1;
    G->v[s]->p = nullptr;
    while (!Queue->IsEmpty()) {
        int u = Queue->dequeue();
        if(u == t)
            return 1;
        
        Edge* edge = G->v[u]->head;
        while (edge != nullptr) {//扫描正向边
            if(G->v[edge->end]->color == 0){//如果该边的尾结点没被访问过
                if(edge->f < edge->value){ //如果这是一条在原图中存在的边，并且当前流量是小于容量
                    Queue->enqueue(edge->end);
                    e[edge->end] = edge; //将路径上的边加入
                    G->v[edge->end]->color = 1;
                    G->v[edge->end]->p = G->v[u];
                    edge->Is_in_E = 1;//作为正向边
                }
            }
            edge = edge->next;
        }
        for (Node* iter = tail[u]->Sentinel->next; iter != tail[u]->Sentinel; iter = iter->next) {//扫描逆向边
            if( iter->edge->f != 0 and G->v[iter->edge->start]->color ==0 ){//如果该入边的流量不为0，则存在反向边且入结点没有被访问过
                Queue->enqueue(iter->edge->start);
                e[iter->edge->start] = iter->edge;
                G->v[iter->edge->start]->color = 1;
                G->v[iter->edge->start]->p = G->v[u];
                edge->Is_in_E = 0;//作为逆向边
            }
        }
    }
    //如果遍历所有可达结点没有达到t说明不存在增广路径，返回false
    return 0;
}
//寻找增广路径中的最小权
int FindMinimumValue(vector<Edge *> &p){
    int min = INT32_MAX;
    for (auto iter = p.cbegin(); iter != p.cend(); iter++)
    {
        if((*iter)->value - (*iter)->f < min and (*iter)->Is_in_E == 1)
            min = (*iter)->value - (*iter)->f;
        else if((*iter)->f < min and (*iter)->Is_in_E == 0)
            min = (*iter)->f;
    }
    return min;
}
//Edmonds-Karps算法
int FordFulkersonMethod(LinkGraph* G, int s, int t){
    ListNode1** tail = new ListNode1*[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        tail[i] = new ListNode1();
    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            edge->f = 0;
            Node* temp = new Node(edge);
            tail[edge->end]->ListInsert(temp);
            edge = edge->next;
        }
    }
    Edge** temp = new Edge*[G->NumOfVertex + 1];//存放每个结点和父节点之间连接的边的指针数组
    vector<Edge *> p;
    int i = 0;
    while (FindAugmentRoute(G, s, t, temp, tail) == 1) {
        p.clear();
        i++;
        FindPath(G, t, p, temp);//将增广路径包含的边按顺序存放在p里
        int min = FindMinimumValue(p);
        for(auto iter = p.cbegin(); iter != p.cend(); iter++){ //遍历增广路径
            Edge* edge = (*iter);
            if(edge->Is_in_E){ //如果是原来的一条边则增加流量
                edge->f += min;
            }
            else //否则减少流量
                edge->f -= min;
        }
    }
    int max = 0;
    Edge* e = G->v[s]->head;
    while (e != nullptr) {
        max += e->f;
        e = e->next;
    }
    
    return max;
    
}
//****************************
//最大二分匹配
int MaxSplitMatch(){
    int E,V,bound;
    cin>>V>>E>>bound;
    LinkGraph* G = new LinkGraph(V + 2);
    for (int i = 0; i < E; i++) {
        int s,t;
        cin>>s>>t;
        G->AddSingleEdge(s, t);
    }
    for (int i = 1; i <= bound; i++) {
        G->AddSingleEdge(V + 1, i);
    }
    for (int i = bound + 1; i <= V; i++) {
        G->AddSingleEdge(i, V + 2);
    }
    return FordFulkersonMethod(G, V + 1, V + 2);
    
}
//****************************
//推送-重贴标签算法
//创建一个初始的预流
ListNode1** InitializePreflow(LinkGraph* G, int s){
    ListNode1** tail = new ListNode1*[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        tail[i] = new ListNode1();
    }
    for (int i = 1; i <= G->NumOfVertex; i++) {
        G->v[i]->h = 0;
        G->v[i]->e = 0;
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            edge->f = 0;
            Node* temp = new Node(edge);
            tail[edge->end]->ListInsert(temp);
            edge = edge->next;
        }
    }
    G->v[s]->h = G->NumOfVertex;
    Edge* edge = G->v[s]->head;
    while (edge != nullptr) {
        edge->f = edge->value;
        G->v[edge->end]->e = edge->value;
        G->v[s]->e  -= edge->value;
        edge = edge->next;
    }
    return tail;
}
void Push(LinkGraph* G, Edge* edge, int u, int v, queue<int> &Overflow, int t){
    int cf;
    if(edge->Is_in_E == 1)
        cf = edge->value - edge->f;
    else
        cf = edge->f;
    int delta = min(G->v[u]->e, cf);
    if(edge->Is_in_E == 1)
        edge->f += delta;
    else
        edge->f -= delta;
    G->v[u]->e -= delta;
    G->v[v]->e += delta;
    if(G->v[u]->e > 0)
        Overflow.push(u);
    if(G->v[v]->e > 0 and v != t)
        Overflow.push(v);
    
}
int GenericPushRelabel(LinkGraph* G, int s, int t){
    ListNode1** tail;
    tail = InitializePreflow(G, s);
    queue<int> Overflow;
    for (int i = 1; i <= G->NumOfVertex; i++) {
        if(G->v[i]->e > 0)
            Overflow.push(i);
    }
    while (!Overflow.empty()) {
        int u = Overflow.front();
        Overflow.pop();
        int flag = 0;//如果不存在满足push要求的邻结点
        Edge* edge = G->v[u]->head;
        int min = INT32_MAX;//方便重贴标签
        while (edge != nullptr) { //扫描正向边
            if(edge->f < edge->value){//边容量未满
                if(G->v[u]->h == G->v[edge->end]->h + 1){//可以进行推送操作
                    edge->Is_in_E = 1;//作为正向边推送
                    Push(G, edge, u, edge->end, Overflow, t);
                    flag = 1;
                    break;
                }
                if(min > G->v[edge->end]->h)
                    min = G->v[edge->end]->h;
            }
            edge = edge->next;
        }
        for (Node* iter = tail[u]->Sentinel->next; iter != tail[u]->Sentinel; iter = iter->next) {//扫描逆向边
            if(flag == 1)
                break;
            Edge* edge = iter->edge;
            if(edge->f != 0){
                if(G->v[u]->h == G->v[edge->start]->h + 1){//可以进行推送操作
                    edge->Is_in_E = 0;//作为逆向边推送
                    Push(G, edge, u, edge->start, Overflow, t);
                    flag = 1;
                    break;
                }
                if(min > G->v[edge->start]->h)
                    min = G->v[edge->start]->h;
            }
        }
        if(flag == 0){ //可以进行重贴标签操作
            Overflow.push(u);
            G->v[u]->h = min + 1;
        }
        for (int i = 1; i <= G->NumOfVertex; i++) {
            cout<<i<<" "<<G->v[i]->e<<" "<<G->v[i]->h<<endl;
        }
        cout<<endl;
    }
    int max = 0;
    Edge* e = G->v[s]->head;
    while (e != nullptr) {
        max += e->f;
        e = e->next;
    }
    
    return max;
}
//寻找最小割,G已经求得最大流
void DFSVisit(LinkGraph* G, int s){
    G->v[s]->color = 1;
    G->v[s]->key = 1;
    Edge* edge = G->v[s]->head;
    while (edge != nullptr) {
        if(G->v[edge->end]->color == 0){
            DFSVisit(G, edge->end);
        }
        edge = edge->next;
    }
}
void FindMinCut(LinkGraph* G, int s){
    //先求出残存网络
    LinkGraph* Gf = new LinkGraph(G->NumOfVertex);
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(edge->f != 0){
                Gf->AddSingleEdge(edge->end, edge->start);
            }
            if(edge->f < edge->value){
                Gf->AddSingleEdge(edge->start, edge->end);
            }
            edge = edge->next;
        }
    }
    //单次DFS残存网络
    DFSVisit(Gf, s);
    for (int i = 1; i <= Gf->NumOfVertex; i++) {
        if(Gf->v[i]->key == 1){
            cout<<i<<" ";
        }
    }
    cout<<endl;
}
//****************************
void Push1(LinkGraph* G, int u, Node* current){
    int cf;
    int v;
    if(current->key == 1){
        cf = current->edge->value - current->edge->f;
        v = current->edge->end;
    }
    else{
        cf = current->edge->f;
        v = current->edge->start;
    }
    int delta = min(G->v[u]->e, cf);
    if(current->key == 1){
        current->edge->f += delta;
    }
    else{
        current->edge->f -= delta;
    }
    G->v[u]->e -= delta;
    G->v[v]->e += delta;
}
void Discharge(LinkGraph* G, int u, Node* current, ListNode1* N){
    while (G->v[u]->e) {
        int flag = 0;
        if(current == N->Sentinel){
            Node* temp = N->Sentinel->next;
            int min = INT32_MAX;
            while (temp != N->Sentinel) {
                if(temp->key == 1 and temp->edge->f < temp->edge->value and G->v[temp->edge->end]->h < min){ //如果是正向边,并且容量未满
                    min = G->v[temp->edge->end]->h;
                }
                else if(temp->key == 0 and temp->edge->f > 0 and G->v[temp->edge->start]->h < min){ //如果是反向边，并且有流量
                    min = G->v[temp->edge->start]->h;
                }
                temp = temp->next;
            }
            G->v[u]->h = min + 1;
            current = N->Sentinel->next;
            flag = 1;
        }
        else if((current->key == 1 and current->edge->f < current->edge->value) or (current->key == 0 and current->edge->f > 0)){
            int v;
            if(current->key == 1)
                v = current->edge->end;
            else
                v = current->edge->start;
            if(G->v[u]->h == G->v[v]->h + 1){
                Push1(G, u, current);
                flag = 1;
            }
        }
        if(flag == 0){
            current = current->next;
        }
    }
}
//前置重贴标签算法
int RelabelToFront(LinkGraph* G, int s, int t){
    ListNode1** tail;
    tail = InitializePreflow(G, s);
    ListNode1* L = new ListNode1(); //链表L
    for (int i = 1; i <= G->NumOfVertex; i++) {
        if(i != s and i != t){
            L->ListInsert(i);
        }
    }
    ListNode1** N = new ListNode1*[G->NumOfVertex + 1];
    Node** current = new Node*[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        N[i] = new ListNode1();
    }
    for (int i = 1; i <= G->NumOfVertex; i++) { //把相邻结点加入各个结点的邻接链表
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            N[i]->ListInsert(edge, 1); //插入正向边
            edge = edge->next;
        }
        Node* temp = tail[i]->Sentinel->next;
        while (temp != tail[i]->Sentinel) {
            N[i]->ListInsert(temp->edge, 0);//插入逆向边
            temp = temp->next;
        }
        current[i] = N[i]->Sentinel->next; //current初始状态指向head
    }
    
    Node* u = L->Sentinel->next;
    
    while (u != L->Sentinel) {
        int old_height = G->v[u->key]->h;
        Discharge(G, u->key, current[u->key], N[u->key]);
        if(G->v[u->key]->h > old_height){ //将u移动到链表最前端
            L->ListDelete(u);
            L->ListInsert(u);
        }
        u = u->next;
    }
    
    int max = 0;
    Edge* e = G->v[s]->head;
    while (e != nullptr) {
        max += e->f;
        e = e->next;
    }
    
    return max;
}
//练习26.5-2
int Push2(LinkGraph* G, int u, Node* current){
    int cf;
    int v;
    if(current->key == 1){
        cf = current->edge->value - current->edge->f;
        v = current->edge->end;
    }
    else{
        cf = current->edge->f;
        v = current->edge->start;
    }
    int delta = min(G->v[u]->e, cf);
    if(current->key == 1){
        current->edge->f += delta;
    }
    else{
        current->edge->f -= delta;
    }
    int temp = G->v[v]->e;
    G->v[u]->e -= delta;
    G->v[v]->e += delta;
    if(temp == 0 and G->v[v]->e > 0)
        return 1;
    else
        return 0;
}
void Discharge2(LinkGraph* G, int u, Node* current, ListNode1* N, queue<int> &Q, int t){
    while (G->v[u]->e) {
        int flag = 0;
        if(current == N->Sentinel){
            Node* temp = N->Sentinel->next;
            int min = INT32_MAX;
            while (temp != N->Sentinel) {
                if(temp->key == 1 and temp->edge->f < temp->edge->value and G->v[temp->edge->end]->h < min){ //如果是正向边,并且容量未满
                    min = G->v[temp->edge->end]->h;
                }
                else if(temp->key == 0 and temp->edge->f > 0 and G->v[temp->edge->start]->h < min){ //如果是反向边，并且有流量
                    min = G->v[temp->edge->start]->h;
                }
                temp = temp->next;
            }
            G->v[u]->h = min + 1;
            current = N->Sentinel->next;
            flag = 1;
        }
        else if((current->key == 1 and current->edge->f < current->edge->value) or (current->key == 0 and current->edge->f > 0)){
            int v;
            if(current->key == 1)
                v = current->edge->end;
            else
                v = current->edge->start;
            if(G->v[u]->h == G->v[v]->h + 1){
                int v;
                if(current->key == 1)
                    v = current->edge->end;
                else
                    v = current->edge->start;
                
                if(Push2(G, u, current) and v != t) //如果push之后之前没溢出的结点溢出了
                    Q.push(v);
                flag = 1;
            }
        }
        if(flag == 0){
            current = current->next;
        }
    }
}
int RelabelToFront2(LinkGraph* G, int s, int t){
    ListNode1** tail;
    tail = InitializePreflow(G, s);
    queue<int> Q;
    Edge* edge = G->v[s]->head;
    while (edge != nullptr) {
        Q.push(edge->end);
        edge = edge->next;
    }
    ListNode1** N = new ListNode1*[G->NumOfVertex + 1];
    Node** current = new Node*[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        N[i] = new ListNode1();
    }
    for (int i = 1; i <= G->NumOfVertex; i++) { //把相邻结点加入各个结点的邻接链表
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            N[i]->ListInsert(edge, 1); //插入正向边
            edge = edge->next;
        }
        Node* temp = tail[i]->Sentinel->next;
        while (temp != tail[i]->Sentinel) {
            N[i]->ListInsert(temp->edge, 0);//插入逆向边
            temp = temp->next;
        }
        current[i] = N[i]->Sentinel->next; //current初始状态指向head
    }
    
    
    while (!Q.empty()) {
        int u = Q.front();
        Discharge2(G, u, current[u], N[u], Q, t);
        Q.pop();
    }
    
    int max = 0;
    Edge* e = G->v[s]->head;
    while (e != nullptr) {
        max += e->f;
        e = e->next;
    }
    
    return max;
}
//思考题26-1
//流网络标准化 逃逸问题
void Standardize(LinkGraph* G, int* s, int m, int l){
    //无向图反平行边消去
    int n = G->NumOfVertex - 1;
    for(int i = 1; i <= n; i++){ //每当有一个双向边则增加一个结点
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(edge->Is_in_E){
                Vertex** newv = new Vertex*[G->NumOfVertex + 2];
                newv[G->NumOfVertex + 1] = new Vertex(G->NumOfVertex + 1);
                copy(G->v, G->v + G->NumOfVertex + 1, newv);
                delete G->v;
                G->v = newv;
                G->NumOfVertex++;
                G->AddSingleEdge(edge->end, G->v[G->NumOfVertex]->num, 1, 0, 0 , 0);//增加边
                G->AddSingleEdge(G->v[G->NumOfVertex]->num, edge->start, 1, 0, 0, 0);
            }
            edge = edge->next;
        }
    }
    //将结点容量转换为边容量
    for (int i = 1; i <= n; i++) {
        if(G->v[i]->capacity == 1){ //如果该结点有容量
            Vertex** newv = new Vertex*[G->NumOfVertex + 2];
            newv[G->NumOfVertex + 1] = new Vertex(G->NumOfVertex + 1);
            copy(G->v, G->v + G->NumOfVertex + 1, newv);
            delete G->v;
            G->v = newv;
            G->NumOfVertex++;
            G->AddSingleEdge(i, G->v[G->NumOfVertex]->num);//增加一条边再原结点和新节点之间
            Edge* edge = G->v[i]->head->next;
            while (edge != nullptr) {
                G->AddSingleEdge(G->v[G->NumOfVertex]->num, edge->end);//将原结点的出边移动到新生结点上去
                G->DeleteSingleEdge(edge->start, edge->end); //删除原结点的出边
                edge = edge->next;
            }
            if(i <= l or i > n - l or i % l == 1 or i % l == 0 )//如果是边结点则增加一个连接到总汇点的边
                G->AddSingleEdge(G->v[G->NumOfVertex]->num, n + 1);
        }
    }
    //多源多汇化单源单汇
    Vertex** newv = new Vertex*[G->NumOfVertex + 2];
    newv[G->NumOfVertex + 1] = new Vertex(G->NumOfVertex + 1);
    copy(G->v, G->v + G->NumOfVertex + 1, newv);
    delete G->v;
    G->v = newv;
    G->NumOfVertex += 1;
    for (int i = 0; i < m; i++) {
        G->AddSingleEdge(G->NumOfVertex, s[i], 4);//增加总源点和源点之间一条边
    }
}
void prin(LinkGraph* G, int i, int n){
    Edge* edge = G->v[i]->head;
    while (edge != nullptr) {
        if(edge->f == 1){
            if(i <= n)
                cout<<i<<"→";
            prin(G, edge->end, n);
        }
        edge = edge->next;
    }
}
//思考题26-2 最小路径覆盖问题
LinkGraph* CreateGraph(LinkGraph* G){
    LinkGraph* G2 = new LinkGraph(G->NumOfVertex * 2 + 2);
    for (int i = 2; i <= G->NumOfVertex + 1; i++) {
        G2->AddSingleEdge(1, i);
        G2->AddSingleEdge(G->NumOfVertex + 1 + i, G->NumOfVertex + 2);
    }
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            G2->AddSingleEdge(edge->start + 1, edge->end + G->NumOfVertex + 2);
            edge = edge->next;
        }
    }
    return G2;
}
//思考题26-3 算法咨询
//未解决
//思考题26-4 最大流的更新
void MaxFlowIncrease(LinkGraph* G, int s, int t){ //执行一次fulkerson算法
    ListNode1** tail = new ListNode1*[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        tail[i] = new ListNode1();
    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            Node* temp = new Node(edge);
            tail[edge->end]->ListInsert(temp);
            edge = edge->next;
        }
    }
    Edge** temp = new Edge*[G->NumOfVertex + 1];//存放每个结点和父节点之间连接的边的指针数组
    vector<Edge *> p;
    if(FindAugmentRoute(G, s, t, temp, tail) == 1){
        p.clear();
        FindPath(G, t, p, temp);//将增广路径包含的边按顺序存放在p里
        int min = FindMinimumValue(p);
        for(auto iter = p.cbegin(); iter != p.cend(); iter++){ //遍历增广路径
            Edge* edge = (*iter);
            if(edge->Is_in_E){ //如果是原来的一条边则增加流量
                edge->f += min;
            }
            else //否则减少流量
                edge->f -= min;
        }
    }
}
//暂未完全解决
void MaxFlowDecrease(LinkGraph* G, Edge* E, int s, int t){
    if(E->value >= E->f)
        return;
    else{
        for (int i = 1; i <= G->NumOfVertex; i++) {
            G->v[i]->color = 0;
            G->v[i]->p = nullptr;
        }
        G->v[s]->color = 1;
        queue<int> Queue;
        Queue.push(s);
        while (!Queue.empty()) {
            int u = Queue.front();
            Queue.pop();
            Edge* edge = G->v[u]->head;
            while (edge != nullptr) {
                if(G->v[edge->end]->color == 0){
                    G->v[edge->end]->color = 1;
                    G->v[edge->end]->p = G->v[u];
                    Queue.push(edge->end);
                }
                if(edge == E){
                    break;
                }
                edge = edge->next;
            }
        }
        for (int i = 1; i <= G->NumOfVertex; i++) {
            G->v[i]->color = 0;
        }
        queue<int> Queue1;
        Queue1.push(E->end);
        while (!Queue1.empty()) {
            int u = Queue1.front();
            Queue1.pop();
            Edge* edge = G->v[u]->head;
            while (edge != nullptr) {
                if(G->v[edge->end]->color == 0){
                    G->v[edge->end]->color = 1;
                    G->v[edge->end]->p = G->v[u];
                    Queue1.push(edge->end);
                }
                if(edge == E){
                    break;
                }
                edge = edge->next;
            }
        }
    }
}
//思考题26-5　使用伸缩操作来计算最大流
//寻找容量至少为K的增广路径
ListNode1** initial(LinkGraph* G){
    ListNode1** tail = new ListNode1*[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        tail[i] = new ListNode1();
    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            edge->f = 0;
            Node* temp = new Node(edge);
            tail[edge->end]->ListInsert(temp);
            edge = edge->next;
        }
    }
    return tail;
}
vector<Edge *> FindAugment(LinkGraph* G, int s, int t, ListNode1** tail, int K){
    for (int i = 1; i <= G->NumOfVertex; i++) {
        G->v[i]->p = nullptr;
        G->v[i]->color = 0;
    }
    Edge** temp = new Edge*[G->NumOfVertex + 1];
    G->v[s]->color = 1;
    queue<int> Queue;
    Queue.push(s);
    while (!Queue.empty()) {
        int u = Queue.front();
        if(u == t)
            break;
        Edge* edge =G->v[u]->head;
        Queue.pop();
        while (edge != nullptr) {
            if(edge->value - edge->f >= K and G->v[edge->end]->color == 0){
                G->v[edge->end]->color = 1;
                G->v[edge->end]->p = G->v[u];
                Queue.push(edge->end);
                temp[edge->end] = edge;
                edge->Is_in_E = 1;
            }
            edge = edge->next;
        }
        
        for (Node* node = tail[u]->Sentinel->next; node != tail[u]->Sentinel; node = node->next) {
            if(node->edge->f >= K and G->v[node->edge->start]->color == 0){
                G->v[edge->start]->color = 1;
                G->v[edge->start]->p = G->v[u];
                Queue.push(edge->start);
                temp[edge->start] = edge;
                edge->Is_in_E = 0;
            }
        }
    }
    vector<Edge *> p;
    if(G->v[t]->p != nullptr){
        FindPath(G, t, p, temp);//将增广路径包含的边按顺序存放在p里
    }
    else
        p.push_back(nullptr);
    return p;
}
int MaxFlowByScaling(LinkGraph* G, int s, int t){
    ListNode1** tail = initial(G);
    int max = 0;
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(max < edge->value)
                max = edge->value;
            edge = edge->next;
        }
    }
    int K = pow(2, (int) log2(max));
    vector<Edge *> p;
    while (K >= 1) {
        do{
            p = FindAugment(G, s, t, tail, K);
            if(p[0] != nullptr){
                int min = FindMinimumValue(p);
                for (auto iter = p.cbegin(); iter != p.cend(); iter++) {
                    if((* iter)->Is_in_E == 1)
                        (* iter)->f += min;
                    else
                        (* iter)->f -= min;
                }
            }
        }while (p[0] != nullptr);
        K /= 2;
    }
    max = 0;
    Edge* e = G->v[s]->head;
    while (e != nullptr) {
        max += e->f;
        e = e->next;
    }
    
    return max;
}

//思考题26-6 未解决

int main(int argc, const char * argv[]) {
    ifstream in("/program/算法导论/practice/practice/input.txt");
    if(in.is_open()){
        int V,E;
        in>>V>>E;
        LinkGraph* G = new LinkGraph(V);
        for (int i = 0; i < E; i++) {
            int s,e,v;
            in>>s>>e>>v;
            G->AddSingleEdge(s, e, v);
        }
        cout<<GenericPushRelabel(G, 1, 4)<<endl;
        
       
    }
    return 0;
}
