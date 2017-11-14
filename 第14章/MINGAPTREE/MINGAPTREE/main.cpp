//
//  main.cpp
//  MINGAPTREE
//
//  Created by 伏开宇 on 2017/3/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
#define N 6
void Initial(GapTreeNode **a){
    cout<<"请输入"<<N<<"个整数"<<endl;
    for(int i = 0 ; i < N; i ++){
        int j;
        cin>>j;
        a[i] = new GapTreeNode(j, -1);
    }
}
int main(int argc, const char * argv[]) {
    GapTreeNode** a = new GapTreeNode*[N];
    GapTree* b = new GapTree();
    Initial(a);
    for(int i = 0 ; i < N; i++){
        b->GapTreeInsert(a[i]);
    }
    b->GapTreeDelete(a[3]);
    b->InorderTreeWalk(b->root);
    cout<<b->Mingap()<<endl;
    return 0;
}
