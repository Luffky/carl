//
//  Function.hpp
//  INTERVALTREE
//
//  Created by 伏开宇 on 2017/3/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
//区间域
class Int{
public:
    int low;
    int high;
    Int(int l, int h){
        low = l;
        high = h;
    }
    void copy(Int* a){
        low = a->low;
        high = a->high;
    }
};
//区间树节点
class IntervalTreeNode{
public:
    int key;
    Int* interval;
    int Max;
    int color; //0代表红，1代表黑，-1代表未初始化
    IntervalTreeNode *p;
    IntervalTreeNode *left;
    IntervalTreeNode *right;
    IntervalTreeNode(Int* x, int c){
        key = x->low;
        interval = new Int(x->low, x->high);
        Max = x->high;
        color = c;
        if(key == INT32_MIN){
            left = this;
            right = this;
        }
        p = nullptr;
        left = nullptr;
        right = nullptr;
    }
    void SetColor(int i){
        color = i;
    }
    void Copy(IntervalTreeNode *x){
        key = x->key;
        interval->copy(x->interval);
        Max = max(interval->high, max(left->Max, right->Max));
        
    }
    
};
//树
class IntervalTree{
public:
    IntervalTreeNode *root;
    static IntervalTreeNode *nil;
    int bh; //黑高度
    int n;
    IntervalTree();
    IntervalTree(IntervalTreeNode *x);
    void SetRoot(IntervalTreeNode *x);
    //判断重叠
    bool Overlap(IntervalTreeNode*t, Int* i);
    bool ExactOverlap(IntervalTreeNode*t, Int* i);
    IntervalTreeNode* IntervalSearch(Int* i);
    //查找有最小左端点的值
    IntervalTreeNode* IntervalMiniLowSearch(IntervalTreeNode*t, Int* i);
    //查找所有重叠区间
    void IntervalSearchAll(IntervalTreeNode* t, Int* i, int* n);
    //精确查找
    IntervalTreeNode* IntervalExactSearch(Int* i);
    //中序遍历
    void InorderTreeWalk(IntervalTreeNode *x);
    //最小值
    IntervalTreeNode *IntervalTreeMinimum(IntervalTreeNode *x);
    //后继
    IntervalTreeNode *IntervalTreeSuccessor(IntervalTreeNode *x);
    //左旋
    void LeftRotate(IntervalTreeNode *x);
    //右旋
    void RightRotate(IntervalTreeNode *x);
    //插入
    void IntervalTreeInsert(IntervalTreeNode *z);
    //维持红黑树性质
    void IntervalInsertFixup(IntervalTreeNode *x);
    //删除
    void IntervalTreeDelete(IntervalTreeNode *z);
    //维持红黑树性质
    void IntervalDeleteFixup(IntervalTreeNode *x);
    
};

#endif /* Function_hpp */
