//
//  Graph.hpp
//  最小生成树
//
//  Created by 伏开宇 on 2017/4/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
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
    int bcc;//双联通分支号
    int is_Bridge;
    int IsDouble;
    int Uneffective;//瓶颈树中，无效的边
    Edge(int s, int e, int v, int flag = 0){
        next = nullptr;
        value = v;
        start = s;
        end = e;
        bcc = -1;
        type = -1;
        is_Bridge = 0;
        IsDouble = flag;//若为1则代表是无向图的逆边
        Uneffective = 0;
    }
};
class Vertex{//点数据结构
public:
    char name;
    int key; //关键值
    int num;//顶点编号
    int d; //DFS发现时间戳
    int f; //DFS结束时间戳
    Vertex* p;
    int color;//遍历颜色
    int cc;//联通分支编号
    int indegree;//出度和入度
    int outdegree;
    int L;//备用
    int Is_Articulation;//是否是挂接点
    Edge* head;
    Vertex(int k, char n = 'n'){
        name = n;
        key = k;
        num = k;
        head = nullptr;
        d = 0;
        f = 0;
        color = 0;
        cc = 0;
        p = nullptr;
        Is_Articulation = 0;
        indegree = 0;
        outdegree = 0;
        L = 0;
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
            v[i]->L = arc4random_uniform(n) + 1;
        }
        NumOfEdge = 0;
    }
    ~LinkGraph(){
        delete v;
    }
    void Initial(){
        for(int i = 1; i <= NumOfVertex; i++){
            v[i]->d = 0;
            v[i]->f = 0;
            v[i]->color = 0;
            v[i]->cc = 0;
            v[i]->p = nullptr;
            v[i]->Is_Articulation = 0;
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
    void AddSingleEdge(int s, int e, int k = 1, int flag = 0){
        NumOfEdge++;
        Edge* edge = new Edge(s, e, k, flag);
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
                cout<<" →"<<edge->end<<":"<<edge->value;
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
class Function{
public:
    static void DFS_Visit(LinkGraph* G, int i, int* time, int k = 0, int max = INT32_MAX, Vertex** p = nullptr);
};


