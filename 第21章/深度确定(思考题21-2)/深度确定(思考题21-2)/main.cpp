//
//  main.cpp
//  深度确定(思考题21-2)
//
//  Created by 伏开宇 on 2017/4/11.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
class Node{
public:
    char key;
    Node* p;
    int rank;
    int d;
    Node(char x){
        d = -1;
        key = x;
        p = nullptr;
        rank = -1;
    }
    void MakeSet(){
        p = this;
        d = 0;
        rank = 0;
    }
    static Node* FindSet(Node* x){
        if(x != x->p){
            x->p = FindSet(x->p);
        }
        return x->p;
    }
    static Node* FindRoot(Node* x){
        if(x->p != x->p->p){
            Node* y = x->p;
            x->p = FindRoot(y);
            x->d += y->d;
        }
        return x->p;
    }
    static int FindDepth(Node* x){//返回结点x的深度
        FindRoot(x);
        if(x == x->p)
            return x->d;
        else
            return x->d + x->p->d;
    }
    static void Union(Node* x, Node* y){
        Node* r1 = FindSet(x);
        Node* r2 = FindSet(y);
        if(r1->rank < r2->rank){
            r1->p = r2;
        }
        else{
            r2->p = r1;
            if(r1->rank == r2->rank){
                r1->rank++;
            }
        }
    }
    static void Graft(Node*x, Node* y){
        Node* r = Node::FindRoot(x);
        Node* v = Node::FindRoot(y);
        int z = Node::FindDepth(y);
        if(r->rank > v->rank){
            v->p = r;
            r->d = r->d + z + 1;
            v->d = v->d - r->d;
        }
        else{
            r->p = v;
            r->d = r->d + z + 1 - v->d;
            if(r->rank == v->rank)
                v->rank++;
        }
    }
};
void Print(Node** a, int n){
    for(int i = 0 ; i < n ; i++){
        cout<<a[i]->p->key<<a[i]->rank<<endl;
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
