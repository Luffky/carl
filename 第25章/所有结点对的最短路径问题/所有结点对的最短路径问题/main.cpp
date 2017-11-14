//
//  main.cpp
//  所有结点对的最短路径问题
//
//  Created by 伏开宇 on 2017/5/2.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;
void PrintPath(int** p, int i, int j){
    if(i == j)
        cout<<i<<"→";
    else if(p[i][j] == -1)
        cout<<"不存在从"<<i<<"到"<<j<<"的最短路径"<<endl;
    else{
        PrintPath(p, i, p[i][j]);
        cout<<j<<"→";
    }
}
//25.1最短路径和矩阵乘法
int** ExtendShortestPath(int** L, int** G, int n){
    int** L2 = new int*[n + 1];
    for (int i = 1; i <= n; i++) {
        L2[i] = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            L2[i][j] = INF;
            for (int k = 1; k <= n; k++) {
                if(L[i][k] != 100000000 and G[k][j] != 100000000 and L[i][k] + G[k][j] < L2[i][j])
                    L2[i][j] = L[i][k] + G[k][j];
            }
        }
    }
    free(L);
    return L2;
}
//练习25.1-7可以计算前驱矩阵
int** ExtendShortestPath(int** L, int** G, int n, int** P, int l){
    int** L2 = new int*[n + 1];
    for (int i = 1; i <= n; i++) {
        L2[i] = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            L2[i][j] = INF;
            for (int k = 1; k <= n; k++) {
                if(L[i][k] != 100000000 and G[k][j] != 100000000 and L[i][k] + G[k][j] < L2[i][j]){
                    L2[i][j] = L[i][k] + G[k][j];
                    if(L[i][j] != L2[i][j])
                        P[i][j] = k;//更新前驱
                    else if(L2[i][j] == G[i][k] and l == 2)
                        P[i][j] = i;
                }
            }
        }
    }
    free(L);
    return L2;
}
int** SlowAllPath(MatrixGraph* G){
    int n = G->n;
    int** Li = new int*[n + 1];
    int** P = new int*[n + 1];
    for (int i = 1; i <= n; i++) {
        Li[i] = new int[n + 1];
        P[i] = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            Li[i][j] = G->M[i][j];
            P[i][j] = -1;
        }
    }
    int flag = 0;
    //练习25.1-10找出最小权重为复制的环路
    for (int i = 2; i <= n - 1; i++) {
        Li = ExtendShortestPath(Li, G->M, n);
        if(flag == 0){
            for (int j = 1; j <= n; j++) {
                if(Li[j][j] < 0){
                    cout<<"there is a minimum negative circle whose length is "<< i <<endl;
                    flag = 1;
                    break;
                }
            }
        }
    }
    
    
    return Li;
}
//练习25.1-9判断是否有负回路
int** FasterAllPath(MatrixGraph* G){
    int n = G->n;
    int** Li = new int*[n + 1];
    int** check = new int*[n + 1];
    for (int i = 1; i <= n; i++) {
        Li[i] = new int[n + 1];
        check[i] = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            Li[i][j] = G->M[i][j];
        }
    }
    for (int i = 1; i < n - 1; i *= 2) {
        Li = ExtendShortestPath(Li, Li, n);
    }
    check = ExtendShortestPath(Li, Li, n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n ; j++) {
            if(check[i][j] != Li[i][j]){
                cout<<"there is a negative circle in this graph"<<endl;
                return nullptr;
            }
        }
    }
    
    return Li;
}
//练习25.1-6计算前驱矩阵
int** FindParent(int** L, int** W, int n){
    int** P = new int*[n + 1];
    for (int i = 1; i <= n; i++) {
        P[i] = new int[n];
        for (int j = 1; j <= n; j++) {
            if(i == j)
                P[i][j] = -1;
            else if(L[i][j] == 100000000)
                P[i][j] = -1;
            else{
                for (int k = 1; k <= n; k++) {
                    if(k != j and L[i][j] - W[k][j] == L[i][k])
                        P[i][j] = k;
                }
            }
        }
    }
    return P;
}
//25.2 Floyd-Warshall算法
int** FloydWarshall(MatrixGraph* G, int*** p){
    int n = G->n;
    int*** D = new int**[n + 1];
    for (int i = 0; i <= n; i++) {
        D[i] = new int*[n + 1];
        for(int j = 1 ; j <= n; j++) {
            D[i][j] = new int[n + 1];
            if(i == 0){
                for (int k = 1; k <= n; k++) {
                    D[i][j][k] = G->M[j][k];
                    if(j == k or G->M[j][k] == 100000000)
                        p[i][j][k] = -1;
                    else
                        p[i][j][k] = j;
                }
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if(D[k - 1][i][j] <= D[k - 1][i][k] + D[k - 1][k][j]){
                    D[k][i][j] = D[k - 1][i][j];
                    p[k][i][j] = p[k - 1][i][j];
                }
                else{
                    D[k][i][j] = D[k - 1][i][k] + D[k - 1][k][j];
                    p[k][i][j] = p[k - 1][k][j];
                }
            }
        }
    }
    return D[n];
}
//有向图的传递闭包
bool** TransitiveClosure(MatrixGraph* G){
    int n = G->n;
    bool*** D = new bool**[n + 1];
    for (int k = 0; k <= n; k++) {
        D[k] = new bool*[n + 1];
        for (int i = 1; i <= n; i++) {
            D[k][i] = new bool[n + 1];
            if(k == 0){
                for (int j = 1; j <= n; j++) {
                    if(G->M[i][j] != 100000000)
                    D[k][i][j] = 1;
                    else
                        D[k][i][j] = 0;
                }
            }
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                D[k][i][j] = D[k - 1][i][j] | (D[k - 1][i][k] & D[k - 1][k][j]);
            }
        }
    }
    return D[n];
}
//练习25.2-2,使用25.1来计算闭包
bool** TransitiveClosure1(bool** L, bool** w, int n){
    bool** L2 = new bool*[n + 1];
    for (int i = 1; i <= n; i++) {
        L2[i] = new bool[n + 1];
        for (int j = 1; j <= n; j++) {
            L2[i][j] = 0;
            for (int k = 1; k <= n; k++) {
                L2[i][j] = L2[i][j] | (L[i][k] & w[k][j]);
            }
        }
    }
    free(L);
    return L2;
}
bool** SlowAllPath2(MatrixGraph* G){
    int n = G->n;
    bool** Li = new bool*[n + 1];
    bool** w = new bool*[n + 1];
    for (int i = 1; i <= n; i++) {
        Li[i] = new bool[n + 1];
        w[i] = new bool[n + 1];
        for (int j = 1; j <= n; j++) {
            if(G->M[i][j] != 100000000){
                w[i][j] = 1;
                Li[i][j] = 1;
            }
        }
    }
    for (int i = 2; i <= n - 1; i++) {
        Li = TransitiveClosure1(Li, w, n);
    }
    return Li;
}
//练习25.2-4 改进空间的Floyd-Warshall算法,练习25.2-7使用fi代替pi
int** FloydWarshallModified(MatrixGraph* G, int** fi){
    int n = G->n;
    int** D = new int*[n + 1];
    for (int i = 1; i <= n; i++) {
        D[i] = new int[n];
        for (int j = 1; j <= n; j++) {
            D[i][j] = G->M[i][j];
            fi[i][j] = 0;
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if(D[i][j] > D[i][k] + D[k][j]){
                    D[i][j] = D[i][k] + D[k][j];
                    fi[i][j] = k;
                }
            }
        }
    }
    return D;
}
void PrintPathModified(int** p, int i, int j){
    if(p[i][j] == 0){
        cout<<"→"<<j;
    }
    else{
        PrintPathModified(p, i, p[i][j]);
        PrintPathModified(p, p[i][j], j);
    }
}
//练习25.2-5:正确，只是可能会增加前驱树的边数，但不会增加路径长度
//练习25.2-6:只需要在最后检查对角线元素是否有负值即可
//练习25.2-8 O（VE)时间计算传递闭包,使用练习题24.3-8技术,另外，将矩阵转换为邻接表再使用V次BFS也可以 V*（V + E） = VE
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
        //hash->Print();
        index = hash->ExtractMin();
    }
}
int** TransitiveClosure2(MatrixGraph* G){
    int n = G->n;
    int** T = new int*[n + 1];
    LinkGraph* G1 = new LinkGraph(n);
    for (int i = 1; i <= n; i++) {
        T[i] = new int[n + 1];
        for (int j = 1; j <= n; j++) {
            T[i][j] = 0;
            if(G->M[i][j] != 0 and G->M[i][j] != 100000000)
                G1->AddSingleEdge(i, j);
        }
    }
    for (int i = 1; i <= n; i++) {
        Dijkastra2(G1, i, 1);
        for (int j = 1; j <= n; j++) {
            if(G1->v[j]->d < INT32_MAX)
                T[i][j] = 1;
        }
    }
    return T;
}
//练习25.2-9先求得强联通分支图，因为每个分支图是强连通的，所以针对每个分支里的所有点对T[i][j]均为1，然后对于整个分支图，若有S1->S2,那么对于任意一个u属于S1，v属于S2都有T[u][v]为1
int main(int argc, const char * argv[]) {
    fstream in("/program/文件流/cin.txt");
    if(in.is_open()){
        int V,E;
        in>>V>>E;
        MatrixGraph* G =new MatrixGraph(V);
        for (int i = 1; i <= E; i++) {
            int s,t,v;
            in>>s>>t>>v;
            G->AddSingleEdge(s, t, v);
        }
        int** p = new int*[V + 1];
        for (int i = 0; i <= V; i++) {
            p[i] = new int[V + 1];
        }
        int** T = TransitiveClosure2(G);
        for (int i = 1; i <= V ; i++) {
            for (int j = 1; j <= V; j++) {
                cout<<T[i][j]<<" ";
            }
            cout<<endl;
        }
        
    }
    in.close();
    return 0;
}
