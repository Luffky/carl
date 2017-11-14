//
//  Queue.hpp
//  图的基本算法
//
//  Created by 伏开宇 on 2017/4/13.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
using namespace std;
#ifndef Queue_hpp
#define Queue_hpp
#include <stdio.h>
#include "edge.hpp"
//链表队列
class Node{
public:
    int key;
    Node* Pointer;
    Node * next;
    Node * prev;
    Edge * edge;
    Node(int a){
        key = a;
        next = nullptr;
        prev = nullptr;
    }
    Node(int a, Node* P){
        Pointer = P;
        key = a;
        next = nullptr;
        prev = nullptr;
    }
    Node(Edge* edge){
        next = nullptr;
        prev = nullptr;
        this->edge = edge;
    }
};

class ListNode1{
public:
    Node *Sentinel;
    int n;
    ListNode1(){
        n = 0;
        Sentinel = new Node(INT32_MAX);
        Sentinel->next = Sentinel;
        Sentinel->prev = Sentinel;
    }
    void ListInsert(Node *x){
        Sentinel->next->prev = x;
        x->next = Sentinel->next;
        Sentinel->next = x;
        x->prev = Sentinel;
        n++;
    }
    void ListInsert(int y){
        Node* x = new Node(y);
        Sentinel->next->prev = x;
        x->next = Sentinel->next;
        Sentinel->next = x;
        x->prev = Sentinel;
        n++;
    }
    void ListInsert(Edge* y, int i){
        Node* x = new Node(y);
        x->key = i;
        Sentinel->next->prev = x;
        x->next = Sentinel->next;
        Sentinel->next = x;
        x->prev = Sentinel;
        n++;
    }
    void ListDelete(Node *x){
        x->prev->next = x->next;
        x->next->prev = x->prev;
        n--;
    }
    
    void Print(){
        Node* node = Sentinel->next;
        while(node != Sentinel){
            cout<<node->key<<" ";
            node = node->next;
        }
        cout<<endl;
    }
    Node ListPop(){
        if(n > 0){
            Node * temp = Sentinel->prev;
            ListDelete(temp);
            return *temp;
        }
        else{
            cout<<"链表空"<<endl;
            exit(0);
        }
    }
    
};

class ListQueue{
public:
    ListNode1 *l;
    ListQueue(){
        l = new ListNode1();
    }
    int IsEmpty(){
        if(l->n == 0)
            return 1;
        else
            return 0;
    }
    void enqueue(int x){
        Node *temp = new Node(x);
        l->ListInsert(temp);
    }
    int dequeue(){
        if(IsEmpty() == 0){
            return l->ListPop().key;
        }
        else{
            cout<<"队列空"<<endl;
            exit(0);
        }
    }
    void print(){
        l->Print();
        cout<<endl;
    }
    
};
#endif /* Queue_hpp */
