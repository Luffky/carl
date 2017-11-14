//
//  Graph.hpp
//  最小生成树
//
//  Created by 伏开宇 on 2017/4/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include "Forest.hpp"
#include <iostream>
#include "Queue.hpp"
#include <iomanip>
using namespace std;
#define INF 100000000;
//邻接表
class Vertex{//点数据结构
public:
    char name;//顶点名称
    int key; //顶点关键值
    int num;//顶点编号
    //int d; //DFS发现时间戳
    //int f; //DFS结束时间戳
    Vertex* p;//父节点
    int color;//遍历颜色
    int d;//最短路径权重上限
    double d1;//最大可靠性估计值
    double d2;//最短路径权重上限，double型
    int indegree;//出度和入度
    int outdegree;
    int e = 0; //最大流超额流
    int h = 0; //最大流结点高度
    int capacity = 0;//结点容量
    Edge* head;
    Vertex(int k, char n = 'n'){
        name = n;
        key = 0;
        num = k;
        head = nullptr;
        d = 0;
        //f = 0;
        color = 0;
        p = nullptr;
        indegree = 0;
        outdegree = 0;
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
        for(int i = 0 ; i <= n; i++){
            v[i] = new Vertex(i);
        }
        NumOfEdge = 0;
    }
    ~LinkGraph(){
        delete v;
    }
    void Initial(){
        for(int i = 1; i <= NumOfVertex; i++){
            //v[i]->d = 0;
            //v[i]->f = 0;
            v[i]->color = 0;
            //v[i]->p = nullptr;
        }
    }
    void AddVertice(){
        Vertex** newv = new Vertex*[NumOfVertex + 2];
        newv[NumOfVertex + 1] = new Vertex(NumOfVertex + 1);
        copy(v, v + NumOfVertex + 1, newv);
        delete v;
        v = newv;
        NumOfVertex++;
    }
    void AddSingleEdge(int s, int e, int k = 1, double r = 0.0, int flag = 0, int E = 1){
        NumOfEdge++;
        Edge* edge = new Edge(s, e, k, flag, E);
        edge->r = r;
        v[s]->outdegree++;
        v[e]->indegree++;
        edge->next = v[s]->head;
        v[s]->head = edge;
    }
    void AddDoubleEdge(int s, int e, int k = 1){
        AddSingleEdge(s, e, k, 0);
        AddSingleEdge(e, s, k, 1);//代表和前一条为同一条边，某些情况不予考虑该边
        NumOfEdge--;
    }
    void DeleteSingleEdge(int s, int e){
        Edge* edge = v[s]->head;
        v[s]->outdegree--;
        v[e]->indegree--;
        if(edge != nullptr){
            if(edge->end == e){
                v[s]->head = edge->next;
                NumOfEdge--;
            }
            else{
                while(edge->next != nullptr){
                    if(edge->next->end == e){
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
                cout<<" →"<<edge->end<<":"<<edge->f;
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
    void InitializeSingle(int s){//初始化结点
        for(int i = 1; i <= NumOfVertex; i++){
            v[i]->d = INT32_MAX;
            v[i]->p = nullptr;
            v[i]->d1 = -1.0;
            v[i]->d2 = 1000000000.0;
        }
        v[s]->d = 0;
        v[s]->d1 = 1.0;
        v[s]->d2 = 0.0;
    }
    int Relax(int u, int v, int w){//松弛过程
        if(this->v[u]->d != INT32_MAX and this->v[v]->d > this->v[u]->d + w){
            this->v[v]->d = this->v[u]->d + w;
            this->v[v]->p = this->v[u];
            return 1;
        }
        return 0;
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
            for(int j = 0; j < n + 1; j++){
                if(i == j)
                    M[i][j] = 0;
                else
                    M[i][j] = INF
            }
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
                cout.setf(ios::left);
                cout<<setw(15)<<M[i][j]<<" ";
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
};
class Function{
public:
    static void DFS_Visit(LinkGraph* G, int i, int* time);
    static void DFS(LinkGraph* G);
    static void BFS(LinkGraph* G, int s);
    static ListNode1* TopologicalSort(LinkGraph* G);
    static void DFS_VisitTopo(LinkGraph* G, int i, int* time, ListNode1* l);
};


