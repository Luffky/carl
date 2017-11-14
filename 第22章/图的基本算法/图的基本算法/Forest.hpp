//
//  Forest.hpp
//  图的基本算法
//
//  Created by 伏开宇 on 2017/4/17.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Forest_hpp
#define Forest_hpp

#include <stdio.h>
class ForestNode{
public:
    int key;
    ForestNode* p;
    int rank;
    ForestNode(int x){
        key = x;
        p = nullptr;
        rank = -1;
    }
    void MakeSet(){
        p = this;
        rank = 0;
    }
    static ForestNode* FindSet(ForestNode* x){
        if(x != x->p)
            x->p = FindSet(x->p);
        return x->p;
    }
    static void Union(ForestNode* x, ForestNode* y){
        ForestNode* r1 = FindSet(x);
        ForestNode* r2 = FindSet(y);
        if(r1->rank < r2->rank){
            r1->p = r2;
        }
        else{
            r2->p = r1;
            if(r1->rank == r2->rank){
                r1->rank++;
            }
        }
    }
};
#endif /* Forest_hpp */
