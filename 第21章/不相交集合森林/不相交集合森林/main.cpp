//
//  main.cpp
//  不相交集合森林
//
//  Created by 伏开宇 on 2017/4/10.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
class Node{
public:
    char key;
    Node* p;
    int rank;
    Node(char x){
        key = x;
        p = nullptr;
        rank = -1;
    }
    void MakeSet(){
        p = this;
        rank = 0;
    }
    static Node* FindSet(Node* x){
        if(x != x->p)
            x->p = FindSet(x->p);
        return x->p;
    }
    //FindSet 非递归方法 练习21.3-2
    static void FindSetNoRecursive(Node* x){
        Node* y = x;
        while(x != x->p)
            x = x->p;
        while(y != x){
            Node* z = y->p;
            y->p = x;
            y = z;
        }
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
            }
        }
    }
};
void Print(Node** a, int n){
    for(int i = 0 ; i < n ; i++){
        cout<<a[i]->p->key<<a[i]->rank<<endl;
    }
}

int main(int argc, const char * argv[]) {
    char a[16] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
    Node** n = new Node*[16];
    for(int i = 0 ; i < 16; i++){
        n[i] = new Node(a[i]);
        n[i]->MakeSet();
    }
    for(int i = 0 ; i < 15; i += 2){
        Node::Union(n[i], n[i + 1]);
    }
    for(int i = 0 ; i < 13; i += 4){
        Node::Union(n[i], n[i + 2]);
    }
    Node::Union(n[0], n[4]);
    Node::Union(n[10], n[12]);
    Node::Union(n[0], n[9]);
    Node* temp;
    temp = Node::FindSet(n[1]);
    temp = Node::FindSet(n[8]);
}
