//
//  main.cpp
//  图的基本算法
//
//  Created by 伏开宇 on 2017/4/12.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Queue.hpp"
#include "Stack.hpp"
#include "Forest.hpp"
using namespace std;
//邻接表
class Edge{//边数据结构
public:
    int start;
    int end;
    int value;
    Edge* next;
    int type;//边类型
    Edge(int s, int e, int v){
        next = nullptr;
        value = v;
        start = s;
        end = e;
        type = -1;
    }
};
class Vertex{//点数据结构
public:
    char name;
    int key;
    int d; //DFS发现时间戳
    int f; //DFS结束时间戳
    Vertex* p;
    int color;
    int cc;//联通分支编号
    Edge* head;
    Vertex(int k, char n = 'n'){
        name = n;
        key = k;
        head = nullptr;
        d = 0;
        f = 0;
        color = 0;
        cc = 0;
        p = nullptr;
    }
};
class LinkGraph{
public:
    int NumOfEdge;
    int NumOfVertex;
    Vertex** v;
    LinkGraph(int n){
        NumOfVertex = n;
        v = new Vertex*[n + 1];
        for(int i = 0 ; i <= n; i++)
            v[i] = new Vertex(i);
        NumOfEdge = 0;
    }
    ~LinkGraph(){
        delete v;
    }
    void AddSingleEdge(int s, int e, int k = 1){
        NumOfEdge++;
        Edge* edge = new Edge(s, e, k);
        edge->next = v[s]->head;
        v[s]->head = edge;
    }
    void AddDoubleEdge(int s, int e, int k = 1){
        AddSingleEdge(s, e, k);
        AddSingleEdge(e, s, k);
        NumOfEdge--;
    }
    void DeleteSingleEdge(int s, int e){
        Edge* edge = v[s]->head;
        if(edge != nullptr){
            if(edge->end == e){
                v[s]->head = edge->next;
                NumOfEdge--;
            }
            else{
                while(edge->next != nullptr){
                    if(edge->next->end == e){
                        delete edge->next;
                        edge->next = edge->next->next;
                        NumOfEdge--;
                        break;
                    }
                    edge = edge->next;
                }
            }
            
        }
    }
    void DeleteDoubleEdge(int s, int e){
        DeleteSingleEdge(s, e);
        DeleteSingleEdge(e, s);
        NumOfEdge++;
    }
    void Print(){
        for(int i = 1 ; i <= NumOfVertex; i++){
            Edge* edge = v[i]->head;
            cout<<i;
            while(edge != nullptr){
                cout<<"→"<<edge->end;
                edge = edge->next;
            }
            cout<<endl;
        }
    }
    int OutDegree(int s){//计算单个结点的出度，时间复杂度为结点出度
        int n = 0;
        Edge* edge = v[s]->head;
        while(edge != nullptr){
            n++;
            edge = edge->next;
        }
        return n;
    }
    int* inDegree(){//计算所有结点的入度,时间复杂度E
        int* r = new int[NumOfVertex + 1];
        for(int i = 0 ; i <= NumOfVertex; i++)
            r[i] = 0;
        for(int i = 1 ; i <= NumOfVertex; i++){
            Edge* edge = v[i]->head;
            while(edge != nullptr){
                r[edge->end]++;
                edge = edge->next;
            }
        }
        return r;
    }
    LinkGraph* Reverse(){//有向图的转置
        LinkGraph* l = new LinkGraph(NumOfVertex);
        for(int i = 1; i <= NumOfVertex; i++){
            Edge* edge = v[i]->head;
            while(edge != nullptr){
                l->AddSingleEdge(edge->end, edge->start, edge->value);
                edge = edge->next;
            }
        }
        return l;
    }
    LinkGraph* Square(){//有向图的平方图
        LinkGraph* l = new LinkGraph(NumOfVertex);
        for(int i = 1; i <= NumOfVertex; i++){
            Edge* edge = v[i]->head;
            while(edge != nullptr){
                Edge* edge2 = v[edge->end]->head;
                while(edge2 != nullptr){
                    l->AddSingleEdge(i, edge2->end, edge->value + edge2->value);
                    edge2 = edge2->next;
                }
                edge = edge->next;
            }
        }
        return l;
    }
    
};
//邻接矩阵
class MatrixGraph{
public:
    int n;
    int noe;
    int** M;
    MatrixGraph(int n){
        this->n = n;
        noe = 0;
        M = new int*[n + 1];
        for(int i = 0 ; i < n + 1; i++){
            M[i] = new int[n + 1];
            for(int j = 0; j < n + 1; j++)
                M[i][j] = 0;
        }
    }
    ~MatrixGraph(){
        delete M;
    }
    void AddSingleEdge(int s, int e, int k = 1){
        noe++;
        M[s][e] = k;
    }
    void AddDoubleEdge(int s, int e, int k = 1){
        noe++;
        M[s][e] = k;
        M[e][s] = k;
    }
    void DeleteSingleEdge(int s, int e){
        noe--;
        M[s][e] = 0;
    }
    void DeleteDoubleEdge(int s, int e){
        noe--;
        M[s][e] = 0;
        M[e][s] = 0;
    }
    void Print(){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                cout<<M[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    int OutDegree(int s){//单个结点出度
        int n = 0;
        for(int i = 1 ; i <= this->n; i++){
            if(M[s][i] != 0)
                n++;
        }
        return n;
    }
    int InDgree(int e){//单个结点入度
        int n = 0;
        for(int i = 1; i <= this->n; i++){
            if(M[i][e] != 0)
                n++;
        }
        return n;
    }
    MatrixGraph* Reverse(){//有向图的转置
        MatrixGraph* m = new MatrixGraph(n);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(M[i][j] != 0)
                    m->AddSingleEdge(j, i, M[i][j]);
            }
        }
        return m;
    }
    MatrixGraph* Square(){//有向图的平方图
        MatrixGraph* m = new MatrixGraph(n);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(M[i][j] != 0){
                    for(int k = 1; k <= n; k++){
                        if(M[j][k] != 0)
                            m->AddSingleEdge(i, k, M[i][j] + M[j][k]);
                    }
                }
            }
        }
        return m;
    }
    
    int UniversalSink(){//确定是否包含汇 复杂度O(V)
        int i = 1;
        int j = 1;
        while(j <= n and i <= n){
            if(M[i][j] == 0)
                j++;
            else
                i++;
        }
        if(i > n){
            cout<<"没有汇"<<endl;
            return -1;
        }
        else{
            for(int j = 1 ; j <= i - 1; j++){
                if(M[i][j] == 1){
                    cout<<"没有汇"<<endl;
                    return -1;
                }
            }
            for(int j = 1 ; j <= n; j++){
                if(j != i and M[j][i] == 0){
                    cout<<"没有汇"<<endl;
                    return -1;
                }
            }
            return i;
        }
            
    }
};
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
//摔跤手选拔 练习22.2-6
void Coloring(LinkGraph* G, int s, int* gnb, Vertex** p){
    int n = G->NumOfVertex;
    int* d = new int[n + 1];
    int* color = new int[n + 1];
    for(int i = 1 ; i <= n; i++){
        color[i] = 0;//0代表white，1代表gray，2代表black
        d[i] = INT32_MAX;
    }
    d[s] = 0;
    p[s] = nullptr;
    color[s] = 1;
    gnb[s] = 0;//0代表好选手
    ListQueue* queue = new ListQueue();
    queue->enqueue(s);
    while(!queue->IsEmpty()){
        int u = queue->dequeue();
        Edge* edge = G->v[u]->head;
        while(edge != nullptr){
            int v = edge->end;
            if(color[v] == 0){
                color[v] = 1;
                if(gnb[u] == 0)
                    gnb[v] = 1;
                d[v] = d[u] + 1;
                p[v] = G->v[u];
                queue->enqueue(v);
            }
            edge = edge->next;
        }
        color[u] = 2;
    }
    p[s] = G->v[s];
    for(int i = 1; i <= n; i++){
        if(p[i] == nullptr){
            Coloring(G, i, gnb, p);
        }
    }
}
void AssignBoxer(LinkGraph* G){
    int* gnb = new int[G->NumOfVertex + 1];
    for(int i = 1 ; i <= G->NumOfVertex; i++){
        gnb[i] = 0;
    }
    Vertex** p = new Vertex*[G->NumOfVertex + 1];
    for(int i = 1 ; i <= G->NumOfVertex; i++){
        p[i] = nullptr;
    }
    Coloring(G, 1, gnb, p);
//    for(int i = 1; i <= G->NumOfVertex; i++){
//        cout<<gnb[i]<<" ";
//    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while(edge != nullptr){
            if(gnb[i] == gnb[edge->end]){
                cout<<"不存在指定"<<endl;
                return;
            }
            edge = edge->next;
        }
    }
    cout<<endl;
    cout<<"策略如下"<<endl;
    for(int i = 1; i <= G->NumOfVertex; i++){
        if(gnb[i] == 0)
            cout<<i<<":好选手"<<endl;
        else
            cout<<i<<":坏选手"<<endl;
    }
}
//寻找树的直径 练习22.2-7
int FindDiameter(LinkGraph* G, int flag, int s){
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
    }
    int max = -1;
    int k = 0;
    for(int i = 1; i <= n; i++){
        if(max < d[i]){
            k = i;
            max = d[i];
        }
    }
    if(flag == 0){
        return FindDiameter(G, 1, k);
    }
    else{
        cout<<"最长距离为"<<max<<"路径为从"<<s<<"到"<<k<<endl;
        return max;
    }
    
}
//无向连通图双向遍历一次 练习22.2-8(未完成)
void Recursion(LinkGraph* G, int p, ListQueue* q, int* color){
    ListQueue* queue = new ListQueue();
    while(!q->IsEmpty()){
        int u = q->dequeue();
        Edge* edge  = G->v[u]->head;
        cout<<"→"<<u;
        while(edge != nullptr){
            int v = edge->end;
            if(color[v] == 0){
            
                color[v] = 1;
                queue->enqueue(v);
            }
            edge = edge->next;
        }
        Recursion(G, u, queue, color);
        cout<<"→"<<u;
        if(!q->IsEmpty())
            cout<<"→"<<p;
    }
   
}
void DoubleWalk(LinkGraph* G){
    int n = G->NumOfVertex;
    int* color = new int[n + 1];
    for(int i = 1 ; i <= n; i++){
        color[i] = 0;
    }
    ListQueue* queue = new ListQueue();
    queue->enqueue(1);
   
    Recursion(G, 1, queue, color);
  
}
//深搜*******************************************************************
void DFS_Visit(LinkGraph* G, int i, int* time, int k){
    G->v[i]->color = 1; //结点u发现
    G->v[i]->cc = k;//赋予连通分支号
    (*time) ++;
    Vertex* u = G->v[i];
    u->d = *time;
    Edge* edge = u->head;
    while(edge != nullptr){
        if(edge->type == -1){ //第一次搜索到某边，练习22.3-9
            if(G->v[edge->end]->color == 0){
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
            DFS_Visit(G, edge->end, time, k);
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
            DFS_Visit(G, i, &time, k);
        }
    }
}
//非递归DFS 练习22.3-6
void DFSIteration(LinkGraph* G){
    ListStack* s = new ListStack();
    int n = G->NumOfVertex;
    Edge** vector = new Edge*[n];
    for(int i = 1; i <= n; i++)
        vector[i] = nullptr;
    int time = 0;
    for(int i = 1; i <= n; i++){
        if(G->v[i]->color == 0){
            s->push(i);
            while(!s->IsEmpty()){
                int i = s->l->Sentinel->next->key;
                if(G->v[i]->color == 0){
                    G->v[i]->color = 1;
                    time++;
                    Vertex* u = G->v[i];
                    u->d = time;
                    int flag = 0;
                    Edge* edge = u->head;
                    while(edge != nullptr){
                        if(G->v[edge->end]->color == 0){
                            G->v[edge->end]->p = u;
                            flag = 1;
                            s->push(edge->end);
                        }
                        edge = edge->next;
                    }
                    if(flag == 0){
                        s->pop();
                        G->v[i]->color = 2;
                        time++;
                        u->f = time;
                    }
                }
                else if(G->v[i]->color == 1){
                    s->pop();
                    G->v[i]->color = 2;
                    time++;
                    G->v[i]->f = time;
                }
                else{
                    s->pop();
                }
            }
        }
            
    }
}
//练习22.3-6改进，用一个数组记录每个结点扫描到了哪条边
void DFSIteration1(LinkGraph* G){
    ListStack* s = new ListStack();
    int n = G->NumOfVertex;
    Edge** vector = new Edge*[n + 1];
    for(int i = 1; i <= n; i++){
        vector[i] = G->v[i]->head;
    }
    int time = 0;
    for(int i = 1; i <= n; i++){
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
                    edge = edge->next;
                }
                if(edge != nullptr){
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
}
//练习22.3-13判断单连通(不完善)
void DFS_Visit2(LinkGraph* G, int i, int* time, int* flag, int k){
    G->v[i]->color = 1; //结点u发现
    G->v[i]->cc = k;//赋予连通分支号
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
                if(G->v[edge->end]->d > u->d){
                    edge->type = 3;//是正向边
                    *flag = 1;
                }
                else{
                    edge->type = 4;//是交叉边
                    if(G->v[edge->end]->cc == u->cc) //如果是同一个树内结点的交叉边
                        *flag = 1;
                }
            }
        }
        if(G->v[edge->end]->color == 0){
            G->v[edge->end]->p = u;
            DFS_Visit(G, edge->end, time, k);
        }
        edge = edge->next;
    }
    G->v[i]->color = 2; //结点u结束
    (*time) ++;
    u->f = *time;
}
bool DFS2(LinkGraph* G, int k){
    int n = G->NumOfVertex;
    int time = 0;
    int flag = 0;
    int count = 0;
    for(int i = k; i<= n; i++){
        if(G->v[i]->color == 0){
            count++;
            DFS_Visit2(G, i, &time, &flag, count);
        }
        if(flag == 1){
            return false;
        }
    }
    for(int i = k - 1; i >= 1; i--){
        if(G->v[i]->color == 0){
            count++;
            DFS_Visit2(G, i, &time, &flag, count);
        }
        if(flag == 1){
            return false;
        }
    }
    return true;
}
bool SingleLink(LinkGraph* G){
    int n = G->NumOfVertex;
    for(int i = 1; i <= n; i++){
        bool flag = DFS2(G, i);
        for(int i = 1; i <= n; i++){
            G->v[i]->color = 0;
            G->v[i]->d = 0;
            G->v[i]->f = 0;
            G->v[i]->p = nullptr;
            G->v[i]->cc = 0;
            Edge* edge = G->v[i]->head;
            while(edge != nullptr){
                edge->type = -1;
                edge = edge->next;
            }
        }
        if(!flag)
            return false;
    }
    return true;
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
    int* r = new int[n];
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
//O(V)确定一个无向图有无回路，直接DFS，因为对于一个无回路无向图（森林），|E| < |V| + 1,所以一旦遇到|V|条边，表示是个有回路图，直接退出函数即可
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
//拓补排序另一种实现 练习22.4-5
void TopoSort(LinkGraph* G){
    ListQueue* queue = new ListQueue();
    int n = G->NumOfVertex;
    int* indegree = new int[n + 1];
    indegree = G->inDegree();
    for(int i = 1; i <= n; i++){
        if(indegree[i] == 0)
            queue->enqueue(i);
    }
    while(!queue->IsEmpty()){
        int u = queue->dequeue();
        cout<<u<<"→";
        Edge* edge = G->v[u]->head;
        while(edge != nullptr){
            indegree[edge->end]--;
            if(indegree[edge->end] == 0)
                queue->enqueue(edge->end);
            edge = edge->next;
        }
    }
    for(int i = 1; i <= n; i++){
        if(indegree[i] != 0){
            cout<<"有回路"<<endl;
            break;
        }
    }
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
        G->v[i]->cc = GT->v[i]->cc;//标记联通分支号
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
int main(int argc, const char * argv[]) {
    int N = 8;
    int E = 14;
    LinkGraph* l1 = new LinkGraph(N);
    MatrixGraph* m1 = new MatrixGraph(N);
    for(int i = 0 ; i < E; i++){
        int s,e;
        cin>>s>>e;
        l1->AddSingleEdge(s, e);
    }
    MinSCC(l1, StronglyConnectedComponents(l1));
    cout<<endl;
    return 0;
}
