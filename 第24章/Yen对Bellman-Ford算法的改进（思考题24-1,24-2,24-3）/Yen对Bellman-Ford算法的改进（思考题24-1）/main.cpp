//
//  main.cpp
//  Yen对Bellman-Ford算法的改进（思考题24-1）
//
//  Created by 伏开宇 on 2017/4/28.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include <vector>
#include <math.h>
#include <algorithm> // std::move_backward
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
using namespace std;
ifstream in("/program/文件流/cin.txt");
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
bool ModifiedBellmanFord(LinkGraph* G, int s){
    G->InitializeSingle(s);
    //生成一个随机排列
    vector<int> v;
    for (int i = 1; i <= G->NumOfVertex; ++i) {
        v.push_back (i);
    }
    unsigned seed = chrono::system_clock::now ().time_since_epoch ().count ();
    shuffle(v.begin(), v.end(), default_random_engine (seed));//生成1-|V|随机排列
    for (int i = 0; i <= G->NumOfVertex / 2; i++) {
        for (int i = 0; i < G->NumOfVertex; i++) {
            Edge* edge = G->v[v[i]]->head;
            while (edge != nullptr) {
                if(edge->start < edge->end)
                    G->Relax(edge->start, edge->end, edge->value);
                edge = edge->next;
            }
        }
        for (int i = G->NumOfVertex - 1; i >= 0; i--) {
            Edge* edge = G->v[v[i]]->head;
            while (edge != nullptr) {
                if(edge->start > edge->end)
                    G->Relax(edge->start, edge->end, edge->value);
                edge = edge->next;
            }
        }
    }
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(G->v[edge->end]->d > G->v[edge->start]->d + edge->value)
                return false;
            edge = edge->next;
        }
    }
    return true;
    
}
//******************************************思考题24-2
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
void Merge(int* a, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int* left = new int[n1 + 1];
    int* right = new int[n2 + 1];
    for (int i = 0; i < n1; i++) {
        left[i] = a[p + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = a[q + i + 1];
    }
    int L = 0;
    int R = 0;
    left[n1] = INT32_MAX;
    right[n2] = INT32_MAX;
    for(int i = p; i <= r; i++){
        if(left[L] <= right[R])
            a[i] = left[L++];
        else
            a[i] = right[R++];
    }
}
void MergeSort(int* a, int p, int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(a, p, q);
        MergeSort(a, q + 1, r);
        Merge(a, p, q, r);
    }
}
bool Is_Inside(int* X, int* Y, int d){
    MergeSort(X, 0, d - 1);
    MergeSort(Y, 0, d - 1);
    for (int i = 0; i < d; i++) {
        if(X[i] >= Y[i])
            return false;
    }
    return true;
}
void Merge2(int** a, int p, int q, int r, int digit){
    int n1 = q - p + 1;
    int n2 = r - q;
    int** left = new int*[n1 + 1];
    int** right = new int*[n2 + 1];
    for (int i = 0; i < n1; i++) {
        left[i] = a[p + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = a[q + i + 1];
    }
    int L = 0;
    int R = 0;
    left[n1] = nullptr;
    right[n2] = nullptr;
    for(int i = p; i <= r; i++){
        if(left[L] != nullptr and right[R] != nullptr){
            if(left[L][digit] <= right[R][digit]){
                a[i] = left[L++];
            }
            else
                a[i] = right[R++];
        }
        else if(left[L] != nullptr){
            a[i] = left[L++];
        }
        else{
            a[i] = right[R++];
        }
    }
}
void MergeSort2(int** a, int p, int r, int digit){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort2(a, p, q, digit);
        MergeSort2(a, q + 1, r, digit);
        Merge2(a, p, q, r, digit);
    }
}
void FindLongestChain(int** B, int n, int d){
    for(int i = 0 ; i < n; i++)
        MergeSort(B[i], 0, d - 1);
    for(int i = d - 1; i >= 0; i--){
        MergeSort2(B, 0, n - 1, i);
    }
//    for (int i = 0;  i < n; i++) {
//        for (int j = 0; j < d; j ++) {
//            cout<<B[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    LinkGraph* G = new LinkGraph(n);//构造单源最长路径
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (Is_Inside(B[i], B[j], d)) {
                G->AddSingleEdge(i + 1, j + 1, -1);
            }
        }
    }
    int largest = 0;
    int start = 0;
    int end = 0;
    for (int s = 1; s <= G->NumOfVertex; s++) {
        Bellman_Ford(G, s);
        for (int i = 1; i <= G->NumOfVertex; i++) {
            if(G->v[i]->d < largest){
                largest = G->v[i]->d;
                start = s;
                end = i;
            }
        }
    }
    cout<<-largest + 1<<": ";
    Bellman_Ford(G, start);
    PrintPath(G, start, end);

}
//******************************************思考题24-3,浮点数无法达到精确度
int Relax(LinkGraph* G,int u, int v, double w){//松弛过程
    if(G->v[u]->d2 < 999999999.0 and G->v[v]->d2 > G->v[u]->d2 + w){
        G->v[v]->d2 = G->v[u]->d2 + w;
        G->v[v]->p = G->v[u];
        return 1;
    }
    return 0;
}
bool Bellman_Ford_current(LinkGraph* G){
    G->InitializeSingle(0);
    for (int i = 0; i <= G->NumOfVertex; i++) {
        for (int j = 0; j <= G->NumOfVertex; j++) {
            Edge* edge = G->v[j]->head;
            while (edge != nullptr) {
                Relax(G, edge->start, edge->end, edge->r);
                edge = edge->next;
            }
        }
    }
    for (int i = 0; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(G->v[edge->end]->d2 > G->v[edge->start]->d2 + edge->r)
                return false;
            edge = edge->next;
        }
    }
    return true;
}
void Print(LinkGraph* G){
    for(int i = 0 ; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        cout<<i;
        while(edge != nullptr){
            cout<<" →"<<edge->end<<":"<<edge->r;
            edge = edge->next;
        }
        cout<<endl;
    }
}
void CurrentTrade(){
    int n;
    in>>n;
    int** R = new int* [n + 1];
    for (int i = 1; i <= n; i++) {
        R[i] = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            in>>R[i][j];
        }
    }
    LinkGraph* G = new LinkGraph(n);
    for (int i = 0; i <= n; i++) {
        if(i == 0){
            for (int j = 1; j <= n; j++) {
                G->AddSingleEdge(i, j, 0, 0.0);
            }
        }
        else{
            for (int j = 1; j <= n; j++) {
                if(i != j)
                    G->AddSingleEdge(i, j, 0, -log(R[i][j]));
            }
        }
    }
    Print(G);
    cout<<Bellman_Ford_current(G)<<endl;
}
int main (int argc, char* argv[])
{
    int V ;
    int E ;
    CurrentTrade();
//    if(in.is_open()){
//        in>>V>>E;
//        LinkGraph* G = new LinkGraph(V);
//        for(int i = 0; i < E; i++){
//            int s, e, v;
//            in>>s>>e>>v;
//            G->AddSingleEdge(s, e, v);
//        }
//        ModifiedBellmanFord(G, 1);
//        for (int i = 1; i <= V; i++) {
//            cout<<G->v[i]->d<<" ";
//            PrintPath(G, 1, i);
//            cout<<endl;
//        }
//        
//    }
    cout<<endl;
    in.close();
    return 0;
}
