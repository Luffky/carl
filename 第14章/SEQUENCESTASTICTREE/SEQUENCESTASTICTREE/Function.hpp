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
//树节点
class RBTreeNode{
public:
    int key;
    int color; //0代表红，1代表黑，-1代表未初始化
    int size; //子树规模
    int bh; //结点黑高
    RBTreeNode *p;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode(int x, int c){
        key = x;
        color = c;
        bh = 1;
        if(x == -1)
            size = 0;
        else
            size = 1;
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
//树
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
    //后继
    RBTreeNode *RBTreeMinimum(RBTreeNode *x);
    //最小值
    RBTreeNode *RBTreeSuccessor(RBTreeNode *x);
    //左旋
    void LeftRotate(RBTreeNode *x);
    //右旋
    void RightRotate(RBTreeNode *x);
    //插入
    void RBTreeInsert(RBTreeNode *z);
    //维持红黑树性质
    void RBInsertFixup(RBTreeNode *x);
    //删除
    void RBTreeDelete(RBTreeNode *z);
    //维持红黑树性质
    void RBDeleteFixup(RBTreeNode *x);
    //找到黑高为某数的最大和最小节点
    RBTreeNode *LocateMaxNodeOfBh(int b);
    RBTreeNode *LocateMinNodeOfBh(int b);
    //红黑树的连接 思考题13-2
    void RBJoin(RBTreeNode *x, RBTree *t2,int flag);
    //顺序统计数查找
    RBTreeNode* Select(RBTreeNode* t,int i);
    //顺序统计查找非递归
    RBTreeNode* IteSelect(int i);
    //确定一个元素的秩
    int Rank(RBTreeNode* t);
    //根据key确定秩
    int KeyRank(RBTreeNode* t, int k);
    //枚举树中a<=k<=b的数据
    void Enumerate(int a, int b);
    
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
#endif /* Function_hpp */
