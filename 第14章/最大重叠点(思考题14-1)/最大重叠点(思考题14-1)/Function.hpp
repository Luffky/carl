//
//  Function.hpp
//  最大重叠点(思考题14-1)
//
//  Created by 伏开宇 on 2017/3/22.
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
