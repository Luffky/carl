//
//  main.cpp
//  SEQUENCESTASTICTREE
//
//  Created by 伏开宇 on 2017/3/20.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
using namespace std;
#define N 20
//顺序查找树寻找逆序对 O(nlgn) 14.1-7练习
int NumOfInv(int* a, int n){
    RBTree *b = new RBTree();
    RBTreeNode **c = new RBTreeNode*[n + 1];
    int inv = 0;
    for(int i = 1 ; i <= n; i++){
        c[i] = new RBTreeNode(a[i - 1], -1);
        b->RBTreeInsert(c[i]);
        inv += i - b->Rank(c[i]);
    }
    return inv;
}

void Initial(RBTreeNode **a){
    cout<<"请输入"<<N<<"个整数"<<endl;
    for(int i = 0 ; i < N; i ++){
        int j;
        cin>>j;
        a[i] = new RBTreeNode(j, -1);
    }
}

int main(int argc, const char * argv[]) {
    RBTreeNode** a = new RBTreeNode*[N];
    Initial(a);
    RBTree *b = new RBTree();
    for(int i = 0 ; i < N; i++){
        b->RBTreeInsert(a[i]);
    }
    b->InorderTreeWalk(b->root);
    cout<<endl;
    b->Enumerate(53,76);
    cout<<endl;
    
    return 0;
}
