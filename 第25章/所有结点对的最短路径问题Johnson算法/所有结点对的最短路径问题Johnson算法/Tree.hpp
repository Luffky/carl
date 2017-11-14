//
//  Tree.hpp
//  所有结点对的最短路径问题Johnson算法
//
//  Created by 伏开宇 on 2017/5/5.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Tree_hpp
#define Tree_hpp
#include <iostream>
#include <stdio.h>
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
    //删除
    void RBTreeDelete(RBTreeNode *z);
    //维持红黑树性质
    void RBDeleteFixup(RBTreeNode *x);
    
};
#endif /* Tree_hpp */
