//
//  main.cpp
//  所有结点对的最短路径问题Johnson算法
//
//  Created by 伏开宇 on 2017/5/4.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include <fstream>
#include <iomanip>
#include "Tree.hpp"
using namespace std;
class Heap1{
public:
    Vertex** data;
    int heap_size;
    int length;
    Heap1(Vertex** vertex, int n){
        this->length = n;
        heap_size = n;
        data = new Vertex*[n + 1];
        for(int i = 1; i <= n; i++){//存储相关指针，便于交换
            data[i] = vertex[i];
            data[i]->key = i;
        }
    }
    void MiniHeapify(int i){
        int l = 2 * i;//左儿子下标
        int r = 2 * i + 1;//右儿子下标
        int smallest = i;
        if(l <= heap_size and data[smallest]->d > data[l]->d){
            smallest = l;
        }
        if(r <= heap_size and data[smallest]->d > data[r]->d){
            smallest = r;
        }
        if(smallest != i){
            Vertex* vertex = data[smallest];
            data[smallest] = data[i];
            data[i] = vertex;
            data[i]->key = i;
            data[smallest]->key = smallest;
            MiniHeapify(smallest);
        }
    }
    void BuildHealp(){
        for(int i = heap_size / 2; i > 0; i--){
            MiniHeapify(i);
        }
    }
    
    Vertex* ExtracMin(){
        if(heap_size < 1)
            return nullptr;
        Vertex* vertex = data[1];
        data[1] = data[heap_size];
        data[1]->key = 1;
        heap_size--;
        MiniHeapify(1);
        return vertex;
    }
    
    void HeapDecrease(int i, int key){
        if(key >= data[i]->d){
            cout<<"新值比原值大"<<endl;
            return;
        }
        data[i]->d = key;
        while(i > 1 and data[i]->d < data[i / 2]->d){
            Vertex* vertex = data[i];
            data[i] = data[i / 2];
            data[i / 2] = vertex;
            data[i]->key = i;
            data[i / 2]->key = i / 2;
            i = i / 2;
        }
    }
    
    void Insert(Vertex* vertex){
        int key = vertex->d;
        vertex->d = INT32_MAX;
        heap_size++;
        length++;
        data[heap_size] = vertex;
        data[heap_size]->key = heap_size;
        HeapDecrease(heap_size, key);
    }
};
bool Bellman_Ford(LinkGraph* G, int s){
    G->InitializeSingle(s);
    for(int i = 0; i < G->NumOfVertex - 1; i++){
        for(int i = 1; i <= G->NumOfVertex; i++){
            Edge* edge = G->v[i]->head;
            while (edge != nullptr) {
                G->Relax(edge->start, edge->end, edge->value);
                edge = edge->next;
            }
        }
    }
    int flag = 0;
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(G->v[edge->end]->d > G->v[edge->start]->d + edge->value){
                flag = 1;
                //G->v[edge->end]->d = INT32_MIN; //练习24.1-4改进，对路径上存在负权重环路额结点将.d域设为-无穷
                //BFS(G, edge->end);
            }
            edge = edge->next;
        }
    }
    if(flag == 0)
        return true;
    else
        return false;
}
void Relax(Heap1* h, LinkGraph* G, int u, int v, int w){
    if(G->v[u]->d != INT32_MAX and G->v[v]->d > G->v[u]->d + w){
        h->HeapDecrease(G->v[v]->key, G->v[u]->d + w);
        G->v[v]->p = G->v[u];
    }
}
void Dijkastra(LinkGraph* G, int s){
    G->InitializeSingle(s);
    Heap1* h = new Heap1(G->v, G->NumOfVertex);
    h->BuildHealp();
    while (h->heap_size != 0) {
        Vertex* u = h->ExtracMin();
        Edge* edge = u->head;
        while (edge != nullptr) {
            Relax(h, G, edge->start, edge->end, edge->value);
            edge = edge->next;
        }
    }
}
int** Johnson(LinkGraph* G){//使用斐波那契堆能取得更好地运行时间，但是需要修改图的顶点结构使其包含斐波那契堆对应结点的句柄
    int n = G->NumOfVertex;
    int* h = new int[n + 1];
    LinkGraph* G1 = new LinkGraph(n + 2);
    for (int i = 1; i <= n; i++) { //添加一个多余的顶点 n + 1
        G1->AddSingleEdge(n + 1, i, 0); //添加多余的边 n + 1 - i
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            G1->AddSingleEdge(edge->start, edge->end, edge->value);
            edge = edge->next;
        }
    }
    if(Bellman_Ford(G1, n + 1) == false){
        cout<<"there is a negative-weight cycle int the graph"<<endl;
        return nullptr;
    }
    else{
        for (int i = 1; i <= n + 1; i++) {//使用bellman——ford算法计算出从n + 1到所有其他顶点的最短路径长度作为每个顶点的h值
            h[i] = G1->v[i]->d;
        }
        for (int i = 1; i <= n + 1; i++) {//改变每条边的权值，在不改变最短路径路线的情况下，使所有权值均为正值
            Edge* edge = G1->v[i]->head;
            while (edge != nullptr) {
                edge->value = edge->value + h[edge->start] - h[edge->end];
                edge = edge->next;
            }
        }
        int** D = new int*[n + 1];
        for (int i = 1; i <= n; i++) {//对每一个顶点使用djkastra算法
            D[i] = new int[n + 1];
            Dijkastra(G1, i);
            for (int j = 1; j <= n; j++) {
                D[i][j] = G1->v[j]->d  + h[j] - h[i];//将得到的最短路径进行调整，得到原最短路径长度
            }
        }
        return D;
    }
}
//练习25.3-2 为了在用bellman-ford计算结点h时不会遇到无穷相加的问题
//练习25.3-3 W(U,V) = W~(U,V)
//练习25-3-4 因为这样会对边数小的路径有利
//练习25-3-5 W^（c) = W(c) + h(i0) - h(ik), 环路中i0 = ik 所以W^(c) = W(c) = 0;又在W^图中，所有的权都为非负，而环路中所有边的权和为0，所以环路中所有边的权均为0
//练习25-3-6 略
//思考题25-1 动态图的传递闭包
//a
void DynamicTransitiveClosure(LinkGraph* G, bool** GC,int s, int e, int v){
    G->AddSingleEdge(s, e, v);
    for (int i = 1; i <= G->NumOfVertex; i++) {
        for (int j = 1; j <= G->NumOfVertex; j++) {
            if(GC[i][s] == 1 and GC[e][j])
                GC[i][j] = 1;
        }
    }
}
//c
class Transitive{//单个结点的传递闭包
public:
    Transitive** T;
    int i;
    RBTree* Toi;
    RBTree* Ito;
    Transitive(int i, Transitive** T){
        this->i = i;
        Toi = new RBTree();
        Ito = new RBTree();
        RBTreeNode* temp = new RBTreeNode(i, -1);
        RBTreeNode* temp1 = new RBTreeNode(i, -1);
        Toi->RBTreeInsert(temp);
        Ito->RBTreeInsert(temp1);
        this->T = T;
    }
    void Print(){
        Ito->InorderTreeWalk(Ito->root);
    }
    void PreotorderTreeWalkprint(RBTreeNode *x, int v){
        if(x != Toi->nil){
            RBTreeNode* z = new RBTreeNode(v, -1);
            T[x->key]->Ito->RBTreeInsert(z);
            PreotorderTreeWalkprint(x->left, v);
            PreotorderTreeWalkprint(x->right, v);
        }
    }
    void PreotorderTreeWalkprint1(RBTreeNode *x){
        if(x != Ito->nil){
            RBTreeNode* z = new RBTreeNode(x->key, -1);
            Ito->RBTreeInsert(z);
            PreotorderTreeWalkprint1(x->left);
            PreotorderTreeWalkprint1(x->right);
        }
    }
    void insert(int v){
        PreotorderTreeWalkprint(Toi->root, v);
        PreotorderTreeWalkprint1(T[v]->Ito->root);
    }
};
void DynamicTransitiveClosureModified(MatrixGraph* G, Transitive** GC, int s, int e, int v){
    if(G->M[s][e] == 100000000){
        G->AddSingleEdge(s, e, v);
        GC[s]->insert(e);
    }
    else
        return;
}

//思考题25-2 E = V^(1+e)
//a d叉堆的insret extractmin decrease的运行渐进时间为 logd（n） dlogd（n） logd（n），若d=0（n^a） 则为 1/a n^a/a 1/a
//b 令d=n^e ,使用dijkstra算法则最终运行时间为(v^(1 + e) / e + v^(1 + e)/e) = O（E/e) = O(E)
//c 运行b中算法v次即可 O（EV）
//d 使用johanson算法中的方法，先将其化为非负权图即可

int main(int argc, const char * argv[]) {
    ifstream in("/program/文件流/cin.txt");
    if(in.is_open()){
        int V,E;
        in>>V>>E;
        LinkGraph* G = new LinkGraph(V);
        MatrixGraph* G1 = new MatrixGraph(V);
        Transitive** GC = new Transitive*[V + 1];
        for (int i = 1; i <= V; i++) {
            GC[i] = new Transitive(i, GC);
        }
        for (int i = 1; i <= E; i++) {
            int s,e,v;
            in>>s>>e>>v;
            DynamicTransitiveClosureModified(G1, GC, s, e, v);
            for (int i = 1; i <= V; i++) {
                GC[i]->Print();
                cout<<endl;
            }
            cout<<endl;
        }
        
    }
    return 0;
}
