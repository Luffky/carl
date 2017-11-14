//
//  Btree.hpp
//  BTree
//
//  Created by 伏开宇 on 2017/4/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Btree_hpp
#define Btree_hpp
#include <stdio.h>
using namespace std;
class BtreeNode;
class Return{
public:
    BtreeNode* y;
    int i;
    Return(BtreeNode* x, int k){
        y = x;
        i = k;
    }
};
class BtreeNode{
public:
    int height;
    int n;
    int* key;
    bool leaf;
    BtreeNode** c;
    BtreeNode(int t){
        height = 0;
        n = 0;
        key = new int[2 * t - 1]; //最多拥有2*t - 1个关键字
        leaf = 1;
        c = new BtreeNode*[2 * t]; //最多拥有2*t个子女
    }
};
class Btree{
public:
    BtreeNode* root;
    int t; //度数
    void CreateBtree();//创建一个空根结点
    Btree(int t){
        this->t = t;
        root = nullptr;
        CreateBtree();
    }
    Return* Search(BtreeNode* x, int k);//搜索B树
    void BtreeSplitChild(BtreeNode* x, BtreeNode* y, int i);//分裂满结点
    void BtreeInsert(int k);//插入主程序
    void BtreeInsertNonfull(BtreeNode* x, int k);//插入辅助递归程序
    int FindMin(BtreeNode* x);//寻找最小关键字
    int FindMax(BtreeNode* x);//寻找最大关键字
    int FindPredessor(BtreeNode* x, int i);//寻找前驱
    int FindSuccessor(BtreeNode* x, int i);//寻找后继
    void BtreeDelete(BtreeNode* x, int k); //删除关键字
    void Merge(BtreeNode* x, BtreeNode* y, int k);//将关键字k和x的右兄弟y合并入x中
    BtreeNode* FindHeight(int h, int t);//寻找高度为h的最左最右结点
};

class Node{
public:
    BtreeNode* key;
    Node * next;
    Node * prev;
    Node(BtreeNode* a){
        key = a;
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
        Sentinel = new Node(nullptr);
        Sentinel->next = Sentinel;
        Sentinel->prev = Sentinel;
    }
    Node ListSeaarch(BtreeNode* k){
        Node *x = Sentinel->next;
        while(x != Sentinel and x->key != k)
            x = x->next;
        return *x;
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
    
    Node ListPop(){
        if(n > 0){
            Node *temp = Sentinel->next;
            ListDelete(temp);
            return *temp;
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
    
    void push(BtreeNode* x){
        Node * temp = new Node(x);
        l->ListInsert(temp);
    }
    
    BtreeNode* pop(){
        if(IsEmpty() == 0){
            BtreeNode* x = l->ListPop().key;
            return x;
        }
        else{
            cout<<"栈空"<<endl;
            exit(0);
        }
        
    }
};

#endif /* Btree_hpp */
