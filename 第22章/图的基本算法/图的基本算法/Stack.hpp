//
//  Stack.hpp
//  图的基本算法
//
//  Created by 伏开宇 on 2017/4/15.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
#include "Queue.hpp"
using namespace std;
#ifndef Stack_hpp
#define Stack_hpp
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
    
    void push(int x){
        Node * temp = new Node(x);
        l->ListInsert(temp);
    }
    
    int pop(){
        if(IsEmpty() == 0){
            int x = l->ListPop().key;
            return x;
        }
        else{
            cout<<"栈空"<<endl;
            exit(0);
        }
        
    }
};

#include <stdio.h>

#endif /* Stack_hpp */
