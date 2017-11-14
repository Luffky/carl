//
//  main.cpp
//  Exercise1
//
//  Created by 伏开宇 on 2017/3/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
using namespace std;
//2.3-7练习
int Function(int *a, int x, int n){
    MergeSort(a, 0, n-1);
 
    for(int i = 0; i<n; i++){
        int key = a[i];
        if(BinarySearchIteration(a, x-key, n-1) !=-1)
            return i+10*BinarySearchIteration(a, x-key, n-1);
    }
    return -1;
}

int main(int argc, const char * argv[]) {
    int a[6] = {5,1,2,4,7,6};
    cout<<Function(a, 12, 6);
    return 0;
}
