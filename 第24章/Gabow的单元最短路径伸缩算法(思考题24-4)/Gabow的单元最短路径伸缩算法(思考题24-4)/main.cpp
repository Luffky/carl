//
//  main.cpp
//  Gabow的单元最短路径伸缩算法(思考题24-4)
//
//  Created by 伏开宇 on 2017/4/29.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include <math.h>
#include <fstream>
using namespace std;
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
//练习24.3-8 权重函数限定的修改Dijkastra算法
int maxOfW(LinkGraph* G){
    int max = INT32_MIN;
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(edge->value > max)
                max = edge->value;
            edge = edge->next;
        }
    }
    int k = ceil(log2(max + 1));
    return k;
}
int Wi(int w, int i, int k){
    int wi = floor(w / pow(2, k - i));
    return wi;
}
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
void Dijkastra2(LinkGraph* G, int s, int w, int i, int k, int* st){
    G->InitializeSingle(s);
    Element** el = new Element*[G->NumOfVertex + 1];
    ChainedHash* hash = new ChainedHash(G->NumOfEdge * w + 1);//这里的hash表槽位数量有一点问题
    for(int i = 1; i <= G->NumOfVertex; i++){
        el[i] = new Element(G->v[i]);
        hash->ChainedHashInsert(el[i]);
    }
    int index = hash->ExtractMin();
    while (index != 0) {
        Vertex* v = G->v[index];
        Edge* edge = v->head;
        while (edge != nullptr) {
            int wi = Wi(edge->value, i, k) + 2 * st[edge->start] - 2 * st[edge->end];
            if(G->v[edge->start]->d != INT32_MAX and G->v[edge->end]->d > G->v[edge->start]->d + wi){
                hash->ChainedHashDecrease(el[edge->end], G->v[edge->start]->d + wi);
                G->v[edge->end]->d =  G->v[edge->start]->d + wi;
                G->v[edge->end]->p = G->v[edge->start];
            }
            edge = edge->next;
        }
        index = hash->ExtractMin();
    }
}

void GabowFlexibleAlgorithm(LinkGraph* G, int s){
    int k = maxOfW(G);//最高位数
    int* st = new int[G->NumOfVertex + 1];
    for(int i = 1; i <= G->NumOfVertex; i++){
        st[i] = 0;
    }
    for (int i = 1; i <= k; i++) {
        Dijkastra2(G, s, 1, i, k, st);
        for(int i = 1; i <= G->NumOfVertex; i++){
            cout<<G->v[i]->d<<": ";
            PrintPath(G, s, i);
            cout<<endl;
        }
        for (int j = 1; j <= G->NumOfVertex; j++) {
            st[j] = 2 * st[j] + G->v[j]->d;
        }
    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        cout<<i<<": "<<st[i]<<endl;
    }
}
//思考题24-6
void merge(Edge** a, int p , int q, int r){
    int n1 = q - p + 1;
    int n2= r - q;
    Edge** left = new Edge*[n1 + 1];
    Edge** right = new Edge*[n2 + 1];
    for (int i = 0; i < n1; i++) {
        left[i] = a[p + i];
    }
    for (int j = 0; j < n2; j++){
        right[j] = a[q + 1 + j];
    }
    int L = 0;
    int R = 0;
    left[n1] = new Edge(0, 0, INT32_MAX);
    right[n2] = new Edge(0, 0, INT32_MAX);
    for (int i = p; i <= r ; i++) {
        if(left[L]->value <= right[R]->value){
            a[i] = left[L++];
        }
        else
            a[i] = right[R++];
    }
}
void mergesort(Edge** a, int p ,int r){
    if(p < r){
        int q = (p + r) / 2;
        mergesort(a, p, q);
        mergesort(a, q + 1, r);
        merge(a, p , q , r);
    }
}
bool Bellman_FordBitonic(LinkGraph* G, int s){
    G->InitializeSingle(s);
    Edge** edges = new Edge*[G->NumOfEdge];
    int n = 0;
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            edges[n++] = edge;
            edge = edge->next;
        }
    }
    mergesort(edges, 0, n - 1);
    for(int i = 0; i < 3; i++){
        for (int j = 0; j < G->NumOfEdge; j++) {
            G->Relax(edges[j]->start, edges[j]->end, edges[j]->value);
        }
        for (int j = G->NumOfEdge - 1; j >= 0; j--) {
            G->Relax(edges[j]->start, edges[j]->end, edges[j]->value);
        }
    }
    int flag = 0;
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(G->v[edge->end]->d > G->v[edge->start]->d + edge->value){
                flag = 1;
            }
            edge = edge->next;
        }
    }
    if(flag == 0)
        return true;
    else
        return false;
}
int main(int argc, const char * argv[]) {
    int V ;
    int E ;
    ifstream  in("/program/文件流/cin.txt");
    if(in.is_open()){
        in>>V>>E;
        LinkGraph* G = new LinkGraph(V);
        for(int i = 0; i < E; i++){
            int s, e, v;
            in>>s>>e>>v;
            G->AddSingleEdge(s, e, v);
        }
        Bellman_FordBitonic(G, 1);
        
    }
    cout<<endl;
    in.close();
    return 0;
    return 0;
}
