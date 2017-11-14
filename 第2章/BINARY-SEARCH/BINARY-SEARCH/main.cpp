//
//  main.cpp
//  BINARY-SEARCH
//
//  Created by 伏开宇 on 2017/3/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
using namespace std;
//二分查找 2.3-5 递归
int BinarySearchRecurrence(int *a, int n, int p, int q){
    if(p <= q){
        int mid = (p+q)/2;
        if(a[mid] == n)
            return mid;
        else if(a[mid] < n)
            return BinarySearchRecurrence(a, n, mid+1, q);
        else if(a[mid] > n)
            return BinarySearchRecurrence(a, n, p, mid-1);
        else
            return -1;
    }
    else
        return -1;
}

//二分查找 2.3.5 迭代
int BinarySearchIteration(int *a, int n, int length){
    int low = 0;
    int high = length;
    int mid = 0;
    while(low <= high){
        mid = (low + high)/2;
        if(a[mid] == n)
            return mid;
        else if(a[mid] < n)
            low = mid + 1;
        else if(a[mid] > n)
            high = mid - 1;
    }
    return -1;
}



int main(int argc, const char * argv[]) {
    //int num = 7;
    int a[8] = {1,5,6,8,9,19,20,89};
    cout<<BinarySearchIteration(a, 8, 7)<<endl;
    cout<<BinarySearchRecurrence(a, 70, 0, 7)<<endl;
    
    return 0;
}
