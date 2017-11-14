//
//  Function.hpp
//  Josephus排列(思考题14-2)
//
//  Created by 伏开宇 on 2017/3/22.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp
#include <iostream>
#include <stdio.h>
//单链表节点
class Node1{
public:
    int key;
    Node1 * next;
    Node1(int a){
        key = a;
        next = nullptr;
    }
};
//环形单链表 有哑元 10.2-5练习
class OnewayListNode{
public:
    Node1 * Sentinel;
    int n;
    OnewayListNode(){
        Sentinel = new Node1(INT32_MAX);
        Sentinel->next = Sentinel;
        n = 0;
    }
    void Delete(){
        Node1 *x = Sentinel->next;
        Node1 *y;
        while(x != Sentinel){
            y = x->next;
            free(x);
            x = y;
        }
    }
    
    Node1* ListSearch(int k){
        Node1 *x = Sentinel->next;
        while(x != Sentinel and x->key != k){
            x = x->next;
        }
        if(x != Sentinel)
            return x;
        else
            return nullptr;
    }
    
    void ListInsert(int k){
        Node1 *node = new Node1(k);
        node->next = Sentinel->next;
        Sentinel->next = node;
    }
    
    void ListDelete(int k){
        Node1 *node = Sentinel;
        while(node->next != Sentinel){
            if(node->next->key == k){
                Node1 *temp = node->next;
                node->next = node->next->next;
                free(temp);
            }
            else
                node = node->next;
        }
        
    }
    
    void ListReverse(){
        Node1 *prev = Sentinel;
        Node1 *node = Sentinel->next;
        Node1 *next = node->next;
        while(node != Sentinel){
            node->next = prev;
            prev = node;
            node = next;
            next = node->next;
        }
        node->next = prev;
    }
};
//树节点
class RBTreeNode{
public:
    int key;
    int color; //0代表红，1代表黑，-1代表未初始化
    int size; //子树规模
    RBTreeNode *p;
    RBTreeNode *left;
    RBTreeNode *right;
    RBTreeNode(int x, int c){
        key = x;
        color = c;
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
//顺序统计树
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
#endif /* Function_hpp */
