//
//  Function.hpp
//  REDBLACK-TREE
//
//  Created by 伏开宇 on 2017/3/20.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
class RBTreeNode{
public:
    int key;
    int color; //0代表红，1代表黑，-1代表未初始化
    RBTreeNode *p;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode(int x, int c){
        key = x;
        color = c;
        p = nullptr;
        left = nullptr;
        right = nullptr;
    }
    void SetColor(int i){
        color = i;
    }
    void Copy(RBTreeNode *x){
        key = x->key;
    }
};

//链表栈
class Node{
public:
    int key;
    RBTreeNode *r;
    Node * next;
    Node * prev;
    Node(RBTreeNode *m, int i){
        r = m;
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
        Sentinel = new Node((RBTreeNode *)nullptr, INT32_MAX);
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
    
    RBTreeNode* RBListPop(){
        if(n > 0){
            Node *temp = Sentinel->next;
            ListDelete(temp);
            return temp->r;
        }
        else{
            cout<<"链表空"<<endl;
            exit(0);
        }
    }
    
    RBTreeNode* RBGetTOP(){
        if(n > 0){
            return Sentinel->next->r;
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
    RBTreeNode* RBpop(){
        if(IsEmpty() == 0){
            RBTreeNode *x = l->RBListPop();
            return x;
        }
        else{
            cout<<"栈空"<<endl;
            exit(0);
        }
        
    }
    
    RBTreeNode* RBGetTop(){
        if(IsEmpty() == 0){
            RBTreeNode *x = l->RBGetTOP();
            return x;
        }
        else{
            cout<<"栈空"<<endl;
            exit(0);
        }
    }
};
class RBTree{
public:
    RBTreeNode *root;
    static RBTreeNode *nil;
    int bh; //黑高度
    int n;
    RBTree();
    RBTree(RBTreeNode *x);
    void SetRoot(RBTreeNode *x);
    int GetBh(RBTreeNode *x);
    //中序遍历
    void InorderTreeWalk(RBTreeNode *x);
    //后继和最小值
    RBTreeNode *RBTreeMinimum(RBTreeNode *x);
    RBTreeNode *RBTreeSuccessor(RBTreeNode *x);
    //左旋
    void LeftRotate(RBTreeNode *x);
    //右旋
    void RightRotate(RBTreeNode *x);
    //插入
    void RBTreeInsert(RBTreeNode *z);
    //维持红黑树性质
    void RBInsertFixup(RBTreeNode *x);
    /*//无父指针操作 13.3-6练习
     void RBTreeInsert1(RBTreeNode *z){
     ListStack s;
     s.push(nil);
     n++;
     RBTreeNode *y = nil;
     RBTreeNode *x = root;
     while(x != nil){
     y = x;
     s.push(x);
     if(x->key < z->key)
     x = x->right;
     else
     x = x->left;
     }
     z->p = y;
     if(y == nil)
     SetRoot(z);
     else{
     if(y->key < z->key)
     y->right = z;
     else
     y->left = z;
     z->left = nil;
     z->right = nil;
     z->color = 0;
     RBInsertFixup1(z, &s);
     }
     }
     //未完成...
     void RBInsertFixup1(RBTreeNode *x, ListStack *s){
     while(s->RBGetTop()->color == 0){//如果x的父亲是红色，则迭代
     RBTreeNode *father = s->RBpop();
     RBTreeNode *gfather = s->RBpop();
     if(father == gfather->left){ //如果x的父亲是左孩子
     RBTreeNode *y = gfather->right; //x的叔叔
     if(y->color == 0){  //x的叔叔如果是红色
     y->color = 1;
     father->color = 1;  //将x的父亲和叔叔都置为黑色
     x = gfather;
     x->color = 0; //x的爷爷置为红色，以其爷爷为当前节点再次迭代
     }
     else{//x的叔叔如果是黑色
     if(x == father->left){ //如果x是左孩子
     RightRotate(father); //右旋
     x->color = 1;//父亲置为黑色
     gfather->color = 0;//爷爷置为红色
     RightRotate(gfather);//右旋爷爷
     x = father;
     }
     else{//如果x是右孩子
     LeftRotate(father); //左旋
     x->color = 1;//父亲置为黑色
     gfather->color = 0;//爷爷置为红色
     RightRotate(gfather);//右旋爷爷
     x = father;
     }
     }
     }
     else{ //x的父亲是右孩子
     RBTreeNode *y = x->p->p->left; //x的叔叔
     if(y->color == 0){ //同上
     y->color = 1;
     x->p->color = 1;  //将x的父亲和叔叔都置为黑色
     x = x->p->p;
     x->color = 0; //x的爷爷置为红色，以其爷爷为当前节点再次迭代
     }
     else{
     if(x == x->p->left){ //如果x是左孩子
     x = x->p; //当前节点变为x的父亲
     RightRotate(x); //右旋
     x->p->color = 1;//父亲置为黑色
     x->p->p->color = 0;//爷爷置为红色
     LeftRotate(x->p->p);//左旋爷爷
     }
     else{//如果x是右孩子
     x = x->p; //当前节点变为x的父亲
     LeftRotate(x); //左旋
     x->p->color = 1;//父亲置为黑色
     x->p->p->color = 0;//爷爷置为红色
     LeftRotate(x->p->p);//左旋爷爷
     }
     }
     
     }
     }
     root->color = 1;
     }*/
    //删除
    void RBTreeDelete(RBTreeNode *z);
    //维持红黑树性质
    void RBDeleteFixup(RBTreeNode *x);
    //找到黑高为某数的最大最小节点
    RBTreeNode *LocateMaxNodeOfBh(int b);
    RBTreeNode *LocateMinNodeOfBh(int b);
    //红黑树的连接 思考题13-2
    void RBJoin(RBTreeNode *x, RBTree *t2,int flag);
    
};
#endif /* Function_hpp */
