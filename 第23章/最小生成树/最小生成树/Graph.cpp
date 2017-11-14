//
//  Graph.cpp
//  最小生成树
//
//  Created by 伏开宇 on 2017/4/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include "Graph.hpp"
//简化多重图
LinkGraph* Simplify(LinkGraph* l){
    int** check = new int*[l->NumOfVertex + 1];
    for(int i = 0 ; i <= l->NumOfVertex; i++){ //记录是否重复边,初始化检测矩阵
        check[i] = new int[l->NumOfVertex];
        for(int j = 0 ; j <= l->NumOfVertex; j++)
            check[i][j] = 0;
    }
    LinkGraph* NewGraph = new LinkGraph(l->NumOfVertex);
    for(int i = 1; i <= l->NumOfVertex; i++){
        Edge* edge = l->v[i]->head;
        while(edge != nullptr){
            if(edge->end != edge->start and check[edge->start][edge->end] == 0){
                NewGraph->AddSingleEdge(edge->start, edge->end, edge->value);
                check[edge->start][edge->end] = 1;
                //check[edge->end][edge->start] = 1;
            }
            edge = edge->next;
        }
    }
    return NewGraph;
}
//返回关联矩阵
int** RelatedMatrix(LinkGraph* l){
    int** RM = new int*[l->NumOfVertex + 1];
    for(int i = 1 ; i <= l->NumOfVertex + 1; i++){
        RM[i] = new int[l->NumOfEdge + 1];
        for(int j = 1; j <= l->NumOfEdge; j++)
            RM[i] = 0;
    }
    int e = 1;
    for(int i = 1; i <= l->NumOfVertex; i++){
        Edge* edge = l->v[i]->head;
        while(edge != nullptr){
            RM[i][e] = -1;
            RM[edge->end][e++] = 1;
        }
    }
    return RM;
}
//广搜*******************************************************************
//输出s到v最短路径上的所有顶点
void PrintPath(LinkGraph* G, int s, int v, Vertex** p){
    if (v == s) {
        cout<<s;
    }
    else if (p[v] == nullptr){
        cout<<"没有从"<<s<<"到"<<v<<"路径存在";
    }
    else{
        PrintPath(G, s, p[v]->key, p);
        cout<<"→"<<v;
    }
}
//广度优先搜索
void BFS(LinkGraph* G, int s){
    int n = G->NumOfVertex;
    int* d = new int[n + 1];
    int* color = new int[n + 1];
    Vertex** p = new Vertex*[n + 1];
    for(int i = 1 ; i <= n; i++){
        color[i] = 0;//0代表white，1代表gray，2代表black
        d[i] = INT32_MAX;
        p[i] = nullptr;
    }
    d[s] = 0;
    p[s] = nullptr;
    color[s] = 1;
    ListQueue* queue = new ListQueue();
    queue->enqueue(s);
    while(!queue->IsEmpty()){
        int u = queue->dequeue();
        Edge* edge = G->v[u]->head;
        while(edge != nullptr){
            int v = edge->end;
            if(color[v] == 0){
                color[v] = 1;
                d[v] = d[u] + 1;
                p[v] = G->v[u];
                queue->enqueue(v);
            }
            edge = edge->next;
        }
        color[u] = 2;
    }
    for(int i  = 1; i <= n; i++){
        PrintPath(G, s, i, p);
        cout<<endl;
    }
}
//广度优先搜索，邻接矩阵练习22.2-3
void PrintPath(int s, int v, int* p){
    if(v == s)
        cout<<s;
    else if(p[v] == -1)
        cout<<s<<"和"<<v<<"之间不连通";
    else{
        PrintPath(s, p[v], p);
        cout<<"→"<<v;
    }
}
void BFS(MatrixGraph* G, int s){
    int n = G->n;
    int* d = new int[n + 1];
    int* color = new int[n + 1];
    int* p = new int[n + 1];
    for(int i = 1 ; i <= n; i++){
        color[i] = 0;//0代表white，1代表gray，2代表black
        d[i] = INT32_MAX;
        p[i] = -1;
    }
    d[s] = 0;
    p[s] = -1;
    color[s] = 1;
    ListQueue* queue = new ListQueue();
    queue->enqueue(s);
    while(!queue->IsEmpty()){
        int u = queue->dequeue();
        for(int i = 1; i <= n; i++){
            if(G->M[u][i] != 0 and color[i] == 0){
                color[i] = 1;
                d[i] = d[u] + 1;
                p[i] = u;
                queue->enqueue(i);
            }
        }
        color[u] = 2;
    }
    for(int i = 1; i <= n; i++){
        PrintPath(s, i, p);
        cout<<endl;
    }
}
//深搜*******************************************************************
void Function::DFS_Visit(LinkGraph* G, int i, int* time, int k, int max, Vertex** p){
    G->v[i]->color = 1; //结点u发现
    G->v[i]->cc = k;//赋予连通分支号
    (*time) ++;
    Vertex* u = G->v[i];
    u->d = *time;
    Edge* edge = u->head;
    while(edge != nullptr){
        if(edge->type == -1){ //第一次搜索到某边，练习22.3-9
            if(G->v[edge->end]->color == 0){
                edge->type = 1;
            }
            else if(G->v[edge->end]->color == 1 and u->p != G->v[edge->end]){
                edge->type = 2;//是反向边
                p[0] = u;
                p[1] = G->v[edge->end];
            }
            else{
                if(G->v[edge->end]->d > u->d)
                    edge->type = 3;//是正向边
                else
                    edge->type = 4;//是交叉边
            }
        }
        if(G->v[edge->end]->color == 0 and edge->value <= max){
            G->v[edge->end]->p = u;
            G->v[edge->end]->key = edge->value;
            DFS_Visit(G, edge->end, time, k, max, p);
        }
        edge = edge->next;
    }
    G->v[i]->color = 2; //结点u结束
    (*time) ++;
    u->f = *time;
}
void DFS_Visit(LinkGraph* G, int i, int* time, int k, ForestNode** f){
    G->v[i]->color = 1; //结点u发现
    G->v[i]->cc = k;//赋予连通分支号
    (*time) ++;
    Vertex* u = G->v[i];
    u->d = *time;
    Edge* edge = u->head;
    while(edge != nullptr){
        if(edge->type == -1){ //第一次搜索到某边，练习22.3-9
            if(G->v[edge->end]->color == 0){
                edge->type = 1;//是树边
                f[edge->end] = new ForestNode(edge->end);
                f[edge->end]->MakeSet();
                ForestNode::Union(f[edge->end], f[edge->start]);
            }
            else if(G->v[edge->end]->color == 1)
                edge->type = 2;//是反向边
            else{
                if(G->v[edge->end]->d > u->d)
                    edge->type = 3;//是正向边
                else
                    edge->type = 4;//是交叉边
            }
        }
        if(G->v[edge->end]->color == 0){
            G->v[edge->end]->p = u;
            DFS_Visit(G, edge->end, time, k, f);
        }
        edge = edge->next;
    }
    G->v[i]->color = 2; //结点u结束
    (*time) ++;
    u->f = *time;
}
void DFS(LinkGraph* G){
    int n = G->NumOfVertex;
    int time = 0;
    int k = 0; //联通分支号练习22.3-11
    for(int i = 1; i<= n; i++){
        if(G->v[i]->color == 0){
            k++;
            Function::DFS_Visit(G, i, &time, k);
        }
    }
}
//拓补排序****************************************************************
void DFS_VisitTopo(LinkGraph* G, int i, int* time, ListNode1* l){
    G->v[i]->color = 1; //结点u发现
    (*time) ++;
    Vertex* u = G->v[i];
    u->d = *time;
    Edge* edge = u->head;
    while(edge != nullptr){
        if(edge->type == -1){ //第一次搜索到某边，练习22.3-9
            if(G->v[edge->end]->color == 0)
                edge->type = 1;//是树边
            else if(G->v[edge->end]->color == 1)
                edge->type = 2;//是反向边
            else{
                if(G->v[edge->end]->d > u->d)
                    edge->type = 3;//是正向边
                else
                    edge->type = 4;//是交叉边
            }
        }
        if(G->v[edge->end]->color == 0){
            G->v[edge->end]->p = u;
            DFS_VisitTopo(G, edge->end, time, l);
        }
        edge = edge->next;
    }
    u->color = 2; //结点u结束
    (*time) ++;
    u->f = *time;
    Node* x = new Node(i);
    l->ListInsert(x);
}
ListNode1* TopologicalSort(LinkGraph* G){
    ListNode1* l = new ListNode1;
    int n = G->NumOfVertex;
    int time = 0;
    //int* r = new int[n];
    for(int i = 1; i<= n; i++){
        if(G->v[i]->color == 0){
            DFS_VisitTopo(G, i, &time, l);
        }
    }
    //    for (int i = 1; i <= G->NumOfVertex; i++) {
    //        Edge* edge = G->v[i]->head;
    //        while(edge != nullptr){
    //            if(edge->type == 2){
    //                cout<<"该图存在反向边，无法进行拓补排序"<<endl;
    //                return nullptr;
    //            }
    //            edge = edge->next;
    //        }
    //    }
    return l;
}
//计算两点间通路数目 练习22.4-2
//非线性
void route(LinkGraph* G, int s, int t, int* num){
    Edge* edge = G->v[s]->head;
    while(edge != nullptr){
        if(edge->end == t)
            (*num)++;
        else
            route(G, edge->end, t, num);
        edge = edge->next;
    }
}
//线性
int Path_num(LinkGraph* G, int s, int t){
    ListNode1* l = TopologicalSort(G);
    Node* node = l->Sentinel->next;
    int* num = new int[G->NumOfVertex];
    for(int i = 1 ; i <= G->NumOfVertex; i++){
        num[i] = 0;
    }
    num[s] = 1;
    while(node != l->Sentinel){
        if(num[node->key] >= num[s]){
            Edge* edge = G->v[node->key]->head;
            while(edge != nullptr){
                num[edge->end] += num[node->key];
                edge = edge->next;
            }
        }
        node = node->next;
    }
    return num[t];
}
//O(V)确定一个无向图有无回路，直接DFS，因为对于一个无回路无向图（森林），|E| < |V| + 1,所以一旦遇到|V|条边，表示是个有回路图，直接退出函数即可 练习22.4-3
bool Asym(LinkGraph* G){
    ListStack* s = new ListStack();
    int n = G->NumOfVertex;
    Edge** vector = new Edge*[n + 1];
    for(int i = 1; i <= n; i++){
        vector[i] = G->v[i]->head;
    }
    int time = 0;
    int flag = 0;
    for(int i = 1; i <= n and flag == 0; i++){
        if(G->v[i]->color == 0){
            s->push(i);
            while(!s->IsEmpty()){
                int j = s->l->Sentinel->next->key;
                Vertex* u = G->v[j];
                if(G->v[j]->color == 0){
                    time++;
                    u->color = 1;
                    u->d = time;
                }
                Edge* edge = vector[j];
                while(edge != nullptr and G->v[edge->end]->color != 0){
                    if(edge->type == -1){ //第一次搜索到某边
                        if(G->v[edge->end]->color == 0)
                            edge->type = 1;//是树边
                        else if(G->v[edge->end]->color == 1){
                            edge->type = 2;//是反向边
                            flag = 1;
                            break;
                        }
                    }
                    edge = edge->next;
                }
                if(flag == 1)
                    break;
                if(edge != nullptr){
                    if(edge->type == -1){ //第一次搜索到某边
                        if(G->v[edge->end]->color == 0)
                            edge->type = 1;//是树边
                        else if(G->v[edge->end]->color == 1){
                            edge->type = 2;//是反向边
                            flag = 1;
                            break;
                        }
                    }
                    s->push(edge->end);
                    G->v[edge->end]->p = u;
                    vector[j] = edge->next;
                }
                else{
                    s->pop();
                    G->v[j]->color = 2;
                    time++;
                    u->f = time;
                }
            }
        }
    }
    if(flag == 0)
        return true;
    else
        return false;
}
//强联通分支***************************************************************
//练习22.5-5 找到强联通分支，生成分支图
LinkGraph* StronglyConnectedComponents(LinkGraph* G){
    ListNode1* l = TopologicalSort(G);
    LinkGraph* GT = G->Reverse();
    int time = 0;
    Node* temp = l->Sentinel->next;
    int Count = 0;
    ForestNode** node = new ForestNode*[G->NumOfVertex + 1];
    while(temp != l->Sentinel){
        int i = temp->key;
        if(GT->v[i]->color == 0){
            Count++;
            node[i] = new ForestNode(i);
            node[i]->MakeSet();
            DFS_Visit(GT, i, &time, Count, node);
            cout<<endl;
        }
        temp = temp->next;
    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        G->v[i]->cc = GT->v[i]->cc;
    }
    LinkGraph* Gscc = new LinkGraph(Count);
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while(edge != nullptr){
            int m = ForestNode::FindSet(node[edge->start])->key;
            int n = ForestNode::FindSet(node[edge->end])->key;
            if(m != n)
                Gscc->AddSingleEdge(GT->v[m]->cc, GT->v[n]->cc);
            edge = edge->next;
        }
    }
    ListNode1** SCC = new ListNode1*[Gscc->NumOfVertex + 1];
    for(int i = 1; i <= Gscc->NumOfVertex; i++){
        SCC[i] = new ListNode1;
    }
    for (int i = 1; i <= G->NumOfVertex; i++) {//根据G中结点的分支号生成SCC集合
        Node* node = new Node(i);
        SCC[G->v[i]->cc]->ListInsert(node);
    }
    for(int i = 1; i <= Gscc->NumOfVertex; i++){
        Node* node = SCC[i]->Sentinel->next;
        cout<<"SCC "<<i<<": ";
        while(node != SCC[i]->Sentinel){
            cout<<node->key<<" ";
            node = node->next;
        }
        cout<<endl;
    }
    
    cout<<endl;
    Gscc = Simplify(Gscc);
    Gscc->Print();
    cout<<endl;
    return Gscc;
}
//练习22.5-6 找到最小同分支图
LinkGraph* MinSCC(LinkGraph* G, LinkGraph* Gscc){
    LinkGraph* G2 = new LinkGraph(G->NumOfVertex);
    ListNode1** SCC = new ListNode1*[Gscc->NumOfVertex + 1];//SCC集合
    for(int i = 1; i <= Gscc->NumOfVertex; i++){
        SCC[i] = new ListNode1;
    }
    for (int i = 1; i <= G->NumOfVertex; i++) {//根据G中结点的分支号生成SCC集合
        Node* node = new Node(i);
        SCC[G->v[i]->cc]->ListInsert(node);
    }
    for (int i = 1; i <= Gscc->NumOfVertex; i++){ //为同一个SCC集合的每个结点生成一个单向环
        Node* temp = SCC[i]->Sentinel->next;
        if(temp->next != SCC[i]->Sentinel){
            while(temp->next != SCC[i]->Sentinel){
                G2->AddSingleEdge(temp->key, temp->next->key);
                temp = temp->next;
            }
            G2->AddSingleEdge(temp->key, temp->next->next->key);
        }
    }
    for (int i = 1; i <= Gscc->NumOfVertex; i++){//根据Gscc中的边，为不同的强联通分支生成一条对应的边
        Edge* edge = Gscc->v[i]->head;
        while(edge != nullptr){
            G2->AddSingleEdge(SCC[edge->start]->Sentinel->next->key, SCC[edge->end]->Sentinel->next->key);
            edge = edge->next;
        }
    }
    G2->Print();
    return G2;
}
//练习22.5-7 判断半连通图
bool SemiconnectedComponents(LinkGraph* G){
    ListNode1* l = TopologicalSort(G);
    LinkGraph* GT = G->Reverse();
    int time = 0;
    Node* temp = l->Sentinel->next;
    int Count = 0;
    ForestNode** node = new ForestNode*[G->NumOfVertex + 1];
    while(temp != l->Sentinel){
        int i = temp->key;
        if(GT->v[i]->color == 0){
            Count++;
            node[i] = new ForestNode(i);
            node[i]->MakeSet();
            DFS_Visit(GT, i, &time, Count, node);
            cout<<endl;
        }
        temp = temp->next;
    }
    LinkGraph* Gscc = new LinkGraph(Count);
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while(edge != nullptr){
            int m = ForestNode::FindSet(node[edge->start])->key;
            int n = ForestNode::FindSet(node[edge->end])->key;
            if(m != n)
                Gscc->AddSingleEdge(GT->v[m]->cc, GT->v[n]->cc);
            edge = edge->next;
        }
    }
    cout<<endl;
    Gscc = Simplify(Gscc);
    Gscc->Print();
    ListNode1* list;
    list = TopologicalSort(Gscc); //对分支图拓补排序
    Node* head = list->Sentinel->next;
    int flag = 0;
    while(head->next != list->Sentinel){
        Edge* edge = Gscc->v[head->key]->head;
        flag = 0;
        while(edge != nullptr){
            if(edge->end == head->next->key){
                flag = 1;
                break;
            }
            edge = edge->next;
        }
        if(flag == 0)
            break;
        head = head->next;
    }
    if(flag == 0)
        return false;
    else
        return true;
    
}
