//
//  BinHeap.hpp
//  二项堆
//
//  Created by 伏开宇 on 2017/4/5.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef BinHeap_hpp
#define BinHeap_hpp
#include <iostream>
#include <stdio.h>
using namespace std;
//二项树结点
class BintreeNode{
public:
    BintreeNode* p;
    int key;
    int degree;
    BintreeNode* child;
    BintreeNode* sibling;
    BintreeNode(int k){
        p = nullptr;
        key = k;
        degree = 0;
        child = nullptr;
        sibling = nullptr;
    }
};
//堆结构
class BinHeap{
public:
    BintreeNode* head;
    int n;
    BinHeap(){
        n = 0;
        head = nullptr;
    }
    BintreeNode* BinHeapMini(); //寻找最小关键字结点 O(lgn)
    void BinLink(BintreeNode* y, BintreeNode* z); //连接两个度数相同二项树根节点
    BintreeNode* BinHeapMerge(BinHeap* H);
    void BinHeapUnion(BinHeap* H);//合并两个二项堆 O(lgn)
    void BinHeapInsert(BintreeNode* x); //插入一个结点 O(lgn)
    void BinHeapInsert1(BintreeNode* x);//练习19.2-8
    BintreeNode* BinHeapExtractMin();//抽取具有最小关键字的结点
    void BinHeapDec(BintreeNode* x, int k);//减小关键字的值
    void BinHeapDelete(BintreeNode* x);//删除一个关键字
};
#endif /* BinHeap_hpp */
