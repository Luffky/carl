//
//  main.cpp
//  单源最短路径
//
//  Created by 伏开宇 on 2017/4/24.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include <fstream>
#include <queue>
#include <math.h>
using namespace std;
ifstream in("/program/文件流/cin.txt");
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
class Heap2{
public:
    Vertex** data;
    int heap_size;
    int length;
    Heap2(Vertex** vertex, int n){
        this->length = n;
        heap_size = n;
        data = new Vertex*[n + 1];
        for(int i = 1; i <= n; i++){//存储相关指针，便于交换
            data[i] = vertex[i];
            data[i]->key = i;
        }
    }
    void MaxHeapify(int i){
        int l = 2 * i;//左儿子下标
        int r = 2 * i + 1;//右儿子下标
        int largest = i;
        if(l <= heap_size and data[largest]->d1 < data[l]->d1){
            largest = l;
        }
        if(r <= heap_size and data[largest]->d1 < data[r]->d1){
            largest = r;
        }
        if(largest != i){
            Vertex* vertex = data[largest];
            data[largest] = data[i];
            data[i] = vertex;
            data[i]->key = i;
            data[largest]->key = largest;
            MaxHeapify(largest);
        }
    }
    void BuildHealp(){
        for(int i = heap_size / 2; i > 0; i--){
            MaxHeapify(i);
        }
    }
    
    Vertex* ExtracMax(){
        if(heap_size < 1)
            return nullptr;
        Vertex* vertex = data[1];
        data[1] = data[heap_size];
        data[1]->key = 1;
        heap_size--;
        MaxHeapify(1);
        return vertex;
    }
    
    void HeapIncrease(int i, double key){
        if(key <= data[i]->d1){
            cout<<"新值比原值小"<<endl;
            return;
        }
        data[i]->d1 = key;
        while(i > 1 and data[i]->d1 > data[i / 2]->d1){
            Vertex* vertex = data[i];
            data[i] = data[i / 2];
            data[i / 2] = vertex;
            data[i]->key = i;
            data[i / 2]->key = i / 2;
            i = i / 2;
        }
    }
    
    void Insert(Vertex* vertex){
        double key = vertex->d1;
        vertex->d1 = -1;
        heap_size++;
        length++;
        data[heap_size] = vertex;
        data[heap_size]->key = heap_size;
        HeapIncrease(heap_size, key);
    }
};
void PrintPath(LinkGraph* G, int s, int v){
    if (v == s) {
        cout<<s;
    }
    else if (G->v[v]->p == nullptr){
        cout<<"没有从"<<s<<"到"<<v<<"路径存在";
    }
    else{
        PrintPath(G, s, G->v[v]->p->num);
        cout<<"→"<<v;
    }
}
/*Bellman-Ford算法*************************************///算法复杂度O（VE）
void BFS(LinkGraph* G, int s){
    G->Initial();
    queue<int> Q;
    G->v[s]->color = 1;
    Q.push(s);
    while (!Q.empty()) {
        int t = Q.front();
        Q.pop();
        Edge* edge = G->v[t]->head;
        while (edge != nullptr) {
            if(G->v[edge->end]->color == 0){
                G->v[edge->end]->d = INT32_MIN;
                G->v[edge->end]->color = 1;
                Q.push(edge->end);
            }
            edge = edge->next;
        }
        G->v[t]->color = 2;
    }
}
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
//练习24.1-3 自动停止的改进bellman-ford算法
bool Bellman_Ford2(LinkGraph* G, int s){
    G->InitializeSingle(s);
    int flag = 0;//判断该次循环是否发生松弛
    for(int i = 0; i < G->NumOfVertex - 1; i++){
        flag = 0;
        for(int i = 1; i <= G->NumOfVertex; i++){
            Edge* edge = G->v[i]->head;
            while (edge != nullptr) {
                flag += G->Relax(edge->start, edge->end, edge->value);
                edge = edge->next;
            }
        }
        if(flag == 0)
            break;
    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(G->v[edge->end]->d > G->v[edge->start]->d + edge->value)
                return false;
            edge = edge->next;
        }
    }
    return true;
}
//练习24.1-6 判断权重为负的回路
void MinusCircle(LinkGraph* G){
    int u = 0;
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(G->v[edge->end]->d > G->v[edge->start]->d + edge->value){
                u = edge->start;//找到任意一个收到负权重回路影响的结点
                break;
            }
            edge = edge->next;
        }
    }
    int* mark = new int[G->NumOfVertex + 1];
    for(int i = 1; i <= G->NumOfVertex; i++){//标记每个结点
        mark[i] = 0;
    }
    if(u != 0){
        while(mark[u] != 1){//若第二次遇到同一标记则跳出循环
            mark[u] = 1;//第一次遇到此结点，标记。
            u = G->v[u]->p->num;
        }
        //此时u必为负权环中的一条边，以u为起点再次遍历其父结点，直到再次遇到他为止
        int v = u;
        do{
            cout<<u<<" ";
            u = G->v[u]->p->num;
        }while(u != v);
    }
}
/*DagShortestPaths算法*************************************///算法复杂度O（V+E）
void Dag_Shortest_Paths(LinkGraph* G, int s){
    ListNode1* TopoSort = Function::TopologicalSort(G);
    G->InitializeSingle(s);
    Node* node = TopoSort->Sentinel->next;
    while (node != TopoSort->Sentinel) {
        Edge* edge = G->v[node->key]->head;
        while (edge != nullptr) {
            G->Relax(edge->start, edge->end, edge->value);
            edge = edge->next;
        }
        node = node->next;
    }
    
}
//PERT图关键路径，练习24.2-3
void Dag_Shortest_Paths2(LinkGraph* G){
    ListNode1* TopoSort = Function::TopologicalSort(G);
    G->InitializeSingle(1);
    for (int i = 1; i <= G->NumOfVertex; i++) {
        if(G->v[i]->indegree == 0){
            G->v[i]->d = G->v[i]->d;
        }
    }
    Node* node = TopoSort->Sentinel->next;
    while (node != TopoSort->Sentinel) {
        Edge* edge = G->v[node->key]->head;
        while (edge != nullptr) {
            if(G->v[edge->start]->d != INT32_MAX and G->v[edge->end]->d > G->v[edge->start]->d + G->v[edge->end]->d){
                G->v[edge->end]->d = G->v[edge->start]->d + G->v[edge->end]->d;
                G->v[edge->end]->p = G->v[edge->start];
            }
            edge = edge->next;
        }
        node = node->next;
    }
    int index = 0;
    int largest = 0;
    for (int i = 1; i <= G->NumOfVertex; i++) {
        if(largest > G->v[i]->d){
            largest = G->v[i]->d;
            index = i;
        }
    }
    Vertex* v = G->v[index];
    while (v->p != nullptr) {
        cout<<v->num<<"←";
        v = v->p;
    }
    cout<<v->num<<endl;
}
//计算dag路径总数 练习24.2-4
int* CountRoute(LinkGraph* G, int s){
    int* Count = new int[G->NumOfVertex + 1];
    for (int i = 0; i <= G->NumOfVertex; i++) {
        Count[i] = 0;
    }
    Count[s] = 1;
    ListNode1* TopoSort = Function::TopologicalSort(G);
    Node* node = TopoSort->Sentinel->next;
    while (node != TopoSort->Sentinel) {
        Edge* edge = G->v[node->key]->head;
        while (edge != nullptr) {
            Count[edge->end] += Count[edge->start];
            edge = edge->next;
        }
        node = node->next;
    }
    return Count;
}
/*Dijkastra算法*************************************///算法复杂度O ((V+E) * lgV)
void Relax(Heap1* h, LinkGraph* G, int u, int v, int w){
    if(G->v[u]->d != INT32_MAX and G->v[v]->d > G->v[u]->d + w){
        h->HeapDecrease(G->v[v]->key, G->v[u]->d + w);
        G->v[v]->p = G->v[u];
    }
}
void Relax(Heap2* h, LinkGraph* G, int u, int v, double r){
    if(G->v[u]->d1 != -1 and G->v[v]->d1 < G->v[u]->d1 * r){
        h->HeapIncrease(G->v[v]->key, G->v[u]->d1 * r);
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
//练习24.3-4 判断dijkstra输出正确性
void Is_right(LinkGraph* G, int total, int i){
    Edge* edge = G->v[i]->head;
    if(total != G->v[i]->d){
        cout<<i<<"号结点的信息不匹配"<<endl;
    }
    while (edge != nullptr) {
        if(G->v[edge->end]->p == G->v[edge->start]){
            Is_right(G, total + edge->value, edge->end);
        }
        edge = edge->next;
    }
}
//练习24.3-6 寻找最可靠通信链路
void FindReliableRoute(LinkGraph* G, int s){
    G->InitializeSingle(s);
    Heap2* h = new Heap2(G->v, G->NumOfVertex);
    h->BuildHealp();
    while (h->heap_size != 0) {
        Vertex* u = h->ExtracMax();
        Edge* edge = u->head;
        while (edge != nullptr) {
            Relax(h, G, edge->start, edge->end, edge->r);
            edge = edge->next;
        }
    }
}
//练习24.3-8 权重函数限定的修改Dijkastra算法
int DivideHASH(int k, int Slot){
    return k % Slot;
}
class Element{
public:
    char data;
    int key;
    Vertex* v;
    Element * next;
    Element * prev;
    Element(Vertex* v){
        this->v = v;
        key = v->d;
        next = nullptr;
        prev = nullptr;
    }
};
class ChainedHash{
public:
    Element **a;
    int m;
    int min;
    ChainedHash(int n){
        a = new Element*[n + 1];
        for(int i = 0 ; i <= n; i ++){
            a[i] = nullptr;
        }
        m = n;
        min = 0;
    }
    void ChainedHashInsert(Element *x){
        int index = DivideHASH(x->key, m + 1);
        if(x->key == INT32_MAX){
            index = m;
        }
        x->prev = nullptr;
        x->next = nullptr;
        if(a[index] == nullptr){
            a[index] = x;
        }
        else{
            x->next = a[index];
            a[index]->prev = x;
            a[index] = x;
        }
    }
    
    void ChainedHashDelete(Element *x, int i){
        if(x->prev == nullptr){
            int index = DivideHASH(x->key, m);
            if(x->key == INT32_MAX)
                index = m;
            a[index] = x->next;
            if(x->next != nullptr)
                x->next->prev = nullptr;
        }
        else{
            if(x->next != nullptr){
                x->next->prev = x->prev;
                x->prev->next = x->next;
            }
            else
                x->prev->next = nullptr;
        }
        if(i == 0)
            free(x);
    }
    int ExtractMin(){
        while (min <= m and a[min] == nullptr) {
            min++;
        }
        if(min > m)
            return 0;
        int index = a[min]->v->num;
        ChainedHashDelete(a[min], 0);
        return index;
    }
    
    void ChainedHashDecrease(Element* x, int key){
        if(key >= x->key){
            cout<<"新值比原值大"<<endl;
            return;
        }
        ChainedHashDelete(x, 1);
        x->key = key;
        ChainedHashInsert(x);
    }
    
    void Print(){
        for(int i = 0; i <= m; i++){
            Element* temp = a[i];
            cout<<i<<": ";
            while (temp != nullptr) {
                cout<<temp->key<<" ";
                temp = temp->next;
            }
            cout<<endl;
        }
    }
};
void Dijkastra2(LinkGraph* G, int s, int w){
    G->InitializeSingle(s);
    Element** el = new Element*[G->NumOfVertex + 1];
    ChainedHash* hash = new ChainedHash((G->NumOfVertex - 1) * w + 1);
    for(int i = 1; i <= G->NumOfVertex; i++){
        el[i] = new Element(G->v[i]);
        hash->ChainedHashInsert(el[i]);
    }
    int index = hash->ExtractMin();
    while (index != 0) {
        Vertex* v = G->v[index];
        Edge* edge = v->head;
        while (edge != nullptr) {
            if(G->v[edge->start]->d != INT32_MAX and G->v[edge->end]->d > G->v[edge->start]->d + edge->value){
                hash->ChainedHashDecrease(el[edge->end], G->v[edge->start]->d + edge->value);
                G->v[edge->end]->d =  G->v[edge->start]->d + edge->value;
                G->v[edge->end]->p = G->v[edge->start];
            }
            edge = edge->next;
        }
        hash->Print();
        index = hash->ExtractMin();
    }
}
//练习24.3-9, 对上个练习的算法进行改进使其运行时间为O（V + E）暂时未解决，使用平衡树存储v.d结点
//
//
//
//
////////////////////////////////
/*差分约束和最短路径*************************************///
void MatrixToShortesRoute(){
    int M;//维度
    int N;//约束条件
    in>>M>>N;
    LinkGraph* G = new LinkGraph(M + 1);
    for(int j = 2; j <= M + 1; j++){
        G->AddSingleEdge(1, j, 0);
    }
    for (int i = 0; i < N; i++) {
        int s,e,v;
        in>>e>>s>>v;
        G->AddSingleEdge(s + 1, e + 1, v);
    }
    
    if(Bellman_Ford(G, 1)){
        for(int i = 2; i <= G->NumOfVertex; i++){
            cout<<G->v[i]->d<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"该差分约束系统没有可行解"<<endl;
    }
}
//练习24.4-5修改bellman算法使复杂度为O(MN)
bool Bellman_Ford3(LinkGraph* G, int s){
    for(int i = 1 ; i <= G->NumOfVertex; i++){
        G->v[i]->d = 0;
    }
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
void MatrixToShortesRoute2(){
    int M;//维度
    int N;//约束条件
    in>>M>>N;
    LinkGraph* G = new LinkGraph(M);
    for (int i = 0; i < N; i++) {
        int s,e,v;
        in>>e>>s>>v;
        G->AddSingleEdge(s, e, v);
    }
    
    if(Bellman_Ford3(G, 1)){
        for(int i = 1; i <= G->NumOfVertex; i++){
            cout<<G->v[i]->d<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"该差分约束系统没有可行解"<<endl;
    }
}
//练习24.4-6 修改bellman算法约束 xi = xj + b系统
void MatrixToShortesRoute3(){
    int M;//维度
    int N;//约束条件
    in>>M>>N;
    LinkGraph* G = new LinkGraph(M);
    for (int i = 0; i < N; i++) {
        int s,e,v;
        in>>e>>s>>v;
        G->AddSingleEdge(s, e, v);
        G->AddSingleEdge(e, s, v);
    }
    
    if(Bellman_Ford3(G, 1)){
        for(int i = 1; i <= G->NumOfVertex; i++){
            cout<<G->v[i]->d<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"该差分约束系统没有可行解"<<endl;
    }
}
//练习24.4-10 修改bellman算法约束 xi <= b系统
void MatrixToShortesRoute4(){
    int M;//维度
    int N;//约束条件
    in>>M>>N;
    LinkGraph* G = new LinkGraph(M + 1);
    for (int i = 0; i < N; i++) {
        int s,e,v;
        in>>e>>s>>v;
        if(e != 0 and s != 0)
            G->AddSingleEdge(s, e, v);
        else if(e == 0){ //xi <= b
            G->AddSingleEdge(s, M + 1, v);
        }
        else{ // -xi <= b
            G->AddSingleEdge(M + 1, e, v);
        }
    }
    //G->Print();
    
    if(Bellman_Ford3(G, 1)){
        for(int i = 1; i <= G->NumOfVertex; i++){
            cout<<G->v[i]->d - G->v[G->NumOfVertex]->d<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"该差分约束系统没有可行解"<<endl;
    }
}
//练习24.4-11 修改bellman算法 使得b可以为实数
void MatrixToShortesRoute5(){
    int M;//维度
    int N;//约束条件
    in>>M>>N;
    LinkGraph* G = new LinkGraph(M + 1);
    for (int i = 0; i < N; i++) {
        int s,e;
        double v;
        in>>e>>s>>v;
        if(e != 0 and s != 0)
            G->AddSingleEdge(s, e, floor(v));
        else if(e == 0){ //xi <= b
            G->AddSingleEdge(s, M + 1, floor(v));
        }
        else{ // -xi <= b
            G->AddSingleEdge(M + 1, e, floor(v));
        }
    }
    //G->Print();
    
    if(Bellman_Ford3(G, 1)){
        for(int i = 1; i <= G->NumOfVertex; i++){
            cout<<G->v[i]->d - G->v[G->NumOfVertex]->d<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"该差分约束系统没有可行解"<<endl;
    }
}
int main(int argc, const char * argv[]) {
    int V ;
    int E ;
    if(in.is_open()){
        in>>V>>E;
        LinkGraph* G = new LinkGraph(V);
        for(int i = 0; i < E; i++){
            int s, e, v;
            in>>s>>e>>v;
            G->AddSingleEdge(s, e, v);
        }
        
    }
    cout<<endl;
    in.close();
    return 0;
}
