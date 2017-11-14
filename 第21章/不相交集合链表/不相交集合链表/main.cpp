//
//  main.cpp
//  不相交集合链表
//
//  Created by 伏开宇 on 2017/4/10.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
class NodeChain;
class G;
class Node{
public:
    char key;
    Node* Next;
    G* g;
    NodeChain* Rep;
    Node(char k){
        key = k;
        g = nullptr;
        Rep = nullptr;
        Next = nullptr;
    }
};
class NodeChain{
public:
    int size;
    Node* head;
    Node* tail;
    NodeChain(Node* c){
        size = 1;
        head = c;
        tail = c;
        c->Rep = this;
    }
    static NodeChain* MakseSet(Node* a){
        NodeChain* c = new NodeChain(a);
        return c;
    }
    static NodeChain* Union(Node* a, Node* b){
        NodeChain* head;
        if(a->Rep->size <= b->Rep->size){
            head = b->Rep;
            NodeChain* temp = a->Rep;
            Node* c = temp->head;
            head->tail->Next = c;
            while(c != nullptr){
                c->Rep = head;
                c = c->Next;
            }
            head->size += temp->size;
            head->tail = temp->tail;
            delete temp;
        }
        else{
            head = a->Rep;
            NodeChain* temp = b->Rep;
            Node* c = temp->head;
            head->tail->Next = c;
            while(c != nullptr){
                c->Rep = head;
                c = c->Next;
            }
            head->size += temp->size;
            head->tail = temp->tail;
            delete temp;
        }
        return head;
    }
    //不使用tail指针Union，练习 21.2-5
    static NodeChain* Union1(Node* a, Node* b){
        NodeChain* head;
        if(a->Rep->size <= b->Rep->size){
            head = b->Rep;
            NodeChain* temp = a->Rep;
            Node* c = temp->head;
            Node* d = head->head;
            while(c != nullptr){
                Node* t = d->Next;
                Node* t1 = c->Next;
                d->Next = c;
                c->Next = t;
                c->Rep = head;
                d = t;
                c = t1;
            }
            head->size += temp->size;
            delete temp;
        }
        else{
            head = a->Rep;
            NodeChain* temp = b->Rep;
            Node* c = temp->head;
            Node* d = head->head;
            while(c != nullptr){
                Node* t = d->Next;
                Node* t1 = c->Next;
                d->Next = c;
                c->Next = t;
                c->Rep = head;
                d = t;
                c = t1;
            }
            head->size += temp->size;
            delete temp;
        }
        return head;
    }
    static NodeChain* FindSet(Node* x){
        return x->Rep;
    }
};
//确定无向图连通子图个数
class G{
public:
    char c;
    Node* x;
    G(char a){
        c = a;
        x = new Node(a);
        x->g = this;
    }
};
class E{
public:
    G* a;
    G* b;
    E(G* a, G* b){
        this->a = a;
        this->b = b;
    }
};
void ConnectedComponent(G** g, E** e, int n, int m){
    for(int i = 0 ; i < n; i++){
        NodeChain::MakseSet(g[i]->x);
    }
    for(int i = 0 ; i < m; i++){
        if(NodeChain::FindSet(e[i]->a->x) != NodeChain::FindSet(e[i]->b->x))
            NodeChain::Union(e[i]->a->x, e[i]->b->x);
    }
}
bool SameComponent(G* u, G* v){
    if(NodeChain::FindSet(u->x) == NodeChain::FindSet(v->x))
        return true;
    else
        return false;
}
int main(int argc, const char * argv[]) {
    char a[16] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
    Node** n = new Node*[16];
    for(int i = 0 ; i < 16; i++){
        n[i] = new Node(a[i]);
        NodeChain::MakseSet(n[i]);
    }
    for(int i = 0 ; i < 15; i += 2){
        NodeChain::Union(n[i], n[i + 1]);
    }
    for(int i = 0 ; i < 13; i += 4){
        NodeChain::Union(n[i], n[i + 2]);
    }
    NodeChain::Union(n[0], n[4]);
    NodeChain::Union(n[10], n[12]);
    NodeChain::Union(n[0], n[9]);
    NodeChain* temp;
    temp = NodeChain::FindSet(n[1]);
    temp = NodeChain::FindSet(n[8]);
    
    return 0;
}
