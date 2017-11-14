//
//  main.cpp
//  有向欧拉回路
//
//  Created by 伏开宇 on 2017/4/18.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
using namespace std;
//思考题22-3
ListNode1* Visit(LinkGraph* G, Node* v, ListNode1* L){
    ListNode1* C = new ListNode1;
    int u = v->key;
    while(G->v[u]->outdegree){
        int w = G->v[u]->head->end;
        G->DeleteSingleEdge(u, w);
        Node* node = new Node(u);
        C->ListInsert(node);
        if(G->v[u]->outdegree > 0){
            Node* node1 = new Node(u, node);
            L->ListInsert(node1);
        }
        u = w;
    }
    return C;
}
ListNode1* EulerTour(LinkGraph* G){
    ListNode1* T = nullptr;
    ListNode1* L = new ListNode1;
    Node* node = new Node(1, nullptr);
    L->ListInsert(node);
    ListNode1* C;
    while(L->n != 0){
        node = L->Sentinel->next;
        L->ListDelete(node);
        C = Visit(G, node, L);
        if(node->Pointer == nullptr)
            T = C;
        else{
            if(C->n != 0){
                Node* temp = node->Pointer->prev;
                temp->next->prev = C->Sentinel->prev;
                C->Sentinel->prev->next = temp->next;
                temp->next = C->Sentinel->next;
                C->Sentinel->next->prev = temp;
            }
        }
//        L->Print();
//        for(Node* node = T->Sentinel->prev; node != T->Sentinel; node = node->prev)
//            cout<<node->key<<"→";
//        cout<<T->Sentinel->prev->key;
//        cout<<endl;
    }
    return T;
}
//思考题22-4 可达性
void CountingSort(Vertex** a, int * b, int k, int n){
    int * c = new int[k + 1];
    c[0] = -1;
    for(int i = 1; i <= k; i++){
        c[i] = 0;
    }
    for(int i = 1; i <= n; i++){
        c[a[i]->L] ++;
    }
    for(int i = 1; i <= k; i++){
        c[i] = c[i] + c[i-1];
    }
    for(int i = 1; i <= n; i++){
        b[c[a[i]->L]--] = i;
    }
}
void DFS_VisitMod(LinkGraph* G, int i, int* time, int min, int* R){
    G->v[i]->color = 1; //结点u发现
    R[i] = min;
    (*time) ++;
    Vertex* u = G->v[i];
    u->d = *time;
    Edge* edge = u->head;
    while(edge != nullptr){
        if(G->v[edge->end]->color == 0){
            G->v[edge->end]->p = u;
            DFS_VisitMod(G, edge->end, time, min, R);
        }
        edge = edge->next;
    }
    G->v[i]->color = 2; //结点u结束
    (*time) ++;
    u->f = *time;
}
int* Reachability(LinkGraph* G){
    LinkGraph* GT = G->Reverse();
    int n = G->NumOfVertex;
    int* b = new int[n];
    int time = 0;
    int* R = new int[n];
    CountingSort(G->v, b, n, n);
//    for(int i = 0; i < n; i++)
//        cout<<b[i]<<" ";
//    cout<<endl;
    for(int i = 0; i < n; i++){
        if(GT->v[b[i]]->color == 0)
           DFS_VisitMod(GT, b[i], &time, G->v[b[i]]->L, R);
    }
    return R;
}
int main(int argc, const char * argv[]) {
    int N = 8;
    int E = 14;
    LinkGraph* l1 = new LinkGraph(N);
    //MatrixGraph* m1 = new MatrixGraph(N);
    for(int i = 0 ; i < E; i++){
        int s,e;
        cin>>s>>e;
        l1->AddSingleEdge(s, e);
    }
    int* R = Reachability(l1);
    for(int i = 1; i <= N; i++){
        cout<<R[i]<<" ";
    }
    cout<<endl;
    return 0;
}
