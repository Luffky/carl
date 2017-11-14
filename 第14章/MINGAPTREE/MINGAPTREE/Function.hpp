//
//  Function.hpp
//  MINGAPTREE
//
//  Created by 伏开宇 on 2017/3/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
#include <iostream>
using namespace std;
//gap树节点
class GapTreeNode{
public:
    int key;
    int mingap;
    int max;
    int min;
    int color; //0代表红，1代表黑，-1代表未初始化
    GapTreeNode *p;
    GapTreeNode *left;
    GapTreeNode *right;
    GapTreeNode(int x, int c){
        key = x;
        mingap = INT32_MAX;
        if(x != -1){
            max = x;
            min = x;
        }
        else{
            max = INT32_MIN/2;
            min = INT32_MAX;
        }
        color = c;
        p = nullptr;
        left = nullptr;
        right = nullptr;
    }
    void SetColor(int i){
        color = i;
    }
    void Copy(GapTreeNode *x){
        key = x->key;
    }
};
//树
class GapTree{
public:
    GapTreeNode *root;
    static GapTreeNode *nil;
    int bh; //黑高度
    int n;
    GapTree();
    GapTree(GapTreeNode *x);
    void SetRoot(GapTreeNode *x);
    //找最小gap
    int Mingap();
    //中序遍历
    void InorderTreeWalk(GapTreeNode *x);
    //最小值
    GapTreeNode *GapTreeMinimum(GapTreeNode *x);
    //后继
    GapTreeNode *GapTreeSuccessor(GapTreeNode *x);
    //左旋
    void LeftRotate(GapTreeNode *x);
    //右旋
    void RightRotate(GapTreeNode *x);
    //插入
    void GapTreeInsert(GapTreeNode *z);
    //维持红黑树性质
    void GapInsertFixup(GapTreeNode *x);
    //删除
    void GapTreeDelete(GapTreeNode *z);
    //维持红黑树性质
    void GapDeleteFixup(GapTreeNode *x);
};
#endif /* Function_hpp */
