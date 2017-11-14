//
//  Function.hpp
//  TREE
//
//  Created by 伏开宇 on 2017/3/14.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp
using namespace std;
#include <stdio.h>
//树节点
class TreeNode{
public:
    int key;
    int value; //树堆优先级
    TreeNode *p;
    TreeNode *left;
    TreeNode *right;
    int hx; //结点高度
    TreeNode(int x){
        value = 0;
        hx = 0;
        key = x;
        p = nullptr;
        left = nullptr;
        right = nullptr;
    }
    void Copy(TreeNode *x){
        key = x->key;
    }
};

class Node{
public:
    int key;
    TreeNode *t;
    Node * next;
    Node * prev;
    Node(TreeNode *m, int i){
        t = m;
        key = i;
        next = nullptr;
        prev = nullptr;
    }
    
};
class ListNode1{
public:
    Node *Sentinel;
    int n;
    ListNode1(){
        n = 0;
        Sentinel = new Node((TreeNode *)nullptr, INT32_MAX);
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
    
    void ListDelete(Node *x){
        x->prev->next = x->next;
        x->next->prev = x->prev;
        n--;
    }
    TreeNode* ListPop(){
        if(n > 0){
            Node *temp = Sentinel->next;
            ListDelete(temp);
            return temp->t;
        }
        else{
            cout<<"链表空"<<endl;
            exit(0);
        }
    }
    
    TreeNode* GetTOP(){
        if(n > 0){
            return Sentinel->next->t;
        }
        else{
            cout<<"链表空"<<endl;
            exit(0);
        }
    }
    
};
class ListStack{
public:
    ListNode1 *l;
    ListStack(){
        l = new ListNode1();
    }
    int IsEmpty(){
        if(l->n == 0)
            return 1;
        else
            return 0;
    }
    
    void push(TreeNode *x){
        Node * temp = new Node(x, l->n);
        l->ListInsert(temp);
    }
    TreeNode* pop(){
        if(IsEmpty() == 0){
            TreeNode *x = l->ListPop();
            return x;
        }
        else{
            cout<<"栈空"<<endl;
            exit(0);
        }
        
    }
    
    TreeNode* GetTop(){
        if(IsEmpty() == 0){
            TreeNode *x = l->GetTOP();
            return x;
        }
        else{
            cout<<"栈空"<<endl;
            exit(0);
        }
    }
};
#endif /* Function_hpp */
