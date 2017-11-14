//
//  main.cpp
//  MIXED-MERGE-SORT
//
//  Created by 伏开宇 on 2017/3/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
#define Limit 5
using namespace std;

void InsertionSortUpper2(int * num, int p, int q){
    int key = 0;
    for(int j = p+1; j<q+1; j++){
        key = num[j];
        int i = j - 1;
        while(i > p-1 && num[i] > key){
            num[i+1] = num[i];
            i--;
        }
        num[i+1] = key;
    }
    
    for(int i = p ; i<q+1; i++){
        cout<<num[i]<<" ";
    }
    cout<<endl;
}

void MixedMergeSort(int *a, int p, int r){
    if(p < r && (r-p)> Limit){
        int q =(p+r)/2;
        MixedMergeSort(a, p, q);
        MixedMergeSort(a, q+1, r);
        Merge(a, p, q, r);
    }
    else
        InsertionSortUpper2(a, p, r);
    
    
}
int main(int argc, const char * argv[]) {
    int a[30] = {23,12,24,64,23,54,36,27,47,84,
                 14,23,76,83,79,34,56,26,73,45,
                 53,45,23,12,75,99,87,67,34,23};
    MixedMergeSort(a, 0, 29);
    for(int i = 0; i<30; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
    
    return 0;
}
