//
//  Graph.cpp
//  最小生成树
//
//  Created by 伏开宇 on 2017/4/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include "Graph.hpp"
using namespace std;
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
void Function::BFS(LinkGraph* G, int s){
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
//深搜*******************************************************************
void Function::DFS_Visit(LinkGraph* G, int i, int* time){
    G->v[i]->color = 1; //结点u发现
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
            }
            else{
                if(G->v[edge->end]->d > u->d)
                    edge->type = 3;//是正向边
                else
                    edge->type = 4;//是交叉边
            }
        }
        if(G->v[edge->end]->color == 0){
            G->v[edge->end]->p = u;
            G->v[edge->end]->key = edge->value;
            DFS_Visit(G, edge->end, time);
        }
        edge = edge->next;
    }
    G->v[i]->color = 2; //结点u结束
    (*time) ++;
    //u->f = *time;
}
void Function::DFS(LinkGraph* G){
    int n = G->NumOfVertex;
    int time = 0;
    int k = 0; //联通分支号练习22.3-11
    for(int i = 1; i<= n; i++){
        if(G->v[i]->color == 0){
            k++;
            Function::DFS_Visit(G, i, &time);
        }
    }
}
//拓补排序****************************************************************
void Function::DFS_VisitTopo(LinkGraph* G, int i, int* time, ListNode1* l){
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
    //u->f = *time;
    Node* x = new Node(i);
    l->ListInsert(x);
}
ListNode1* Function::TopologicalSort(LinkGraph* G){
    ListNode1* l = new ListNode1;
    int n = G->NumOfVertex;
    int time = 0;
    //int* r = new int[n];
    for(int i = 1; i<= n; i++){
        if(G->v[i]->color == 0){
            DFS_VisitTopo(G, i, &time, l);
        }
    }
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while(edge != nullptr){
            if(edge->type == 2){
                cout<<"该图存在反向边，无法进行拓补排序"<<endl;
                return nullptr;
            }
            edge = edge->next;
        }
    }
    return l;
}




