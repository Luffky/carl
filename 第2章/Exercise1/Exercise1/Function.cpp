//
//  main.cpp
//  MERGE-SORT
//
//  Created by 伏开宇 on 2017/3/2.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
#define INFTY 2147483647;
#include "Function.hpp"

//合并排序
//合并子程序
void Merge(int * a, int p, int q, int r){
    int n1, n2;
    n1 = q - p + 1;
    n2 = r - q;
    int * left = new int [n1+1];
    int * right = new int [n2+1];
    for(int i = 0; i<n1; i++){
        left[i] = a[p+i];
    }
    for(int i = 0; i<n2; i++){
        right[i] = a[q+1+i];
    }
    left[n1] = INFTY;
    right[n2] = INFTY;
    int k = 0;
    int l = 0;
    for(int i = p; i<r+1; i++){
        if(left[k] < right[l]){
            a[i] = left[k];
            k++;
        }
        else{
            a[i] = right[l];
            l++;
        }
    }
    
}

//合并子程序改 2.3-2练习题
void Merge2(int *a, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int *left = new int[n1];
    int *right = new int[n2];
    for(int i = 0; i<n1; i++){
        left[i] = a[p+i];
    }
    for(int i = 0; i<n2; i++){
        right[i] = a[q+1+i];
    }
    int i = 0;
    int j = 0;
    for(int k = p; k<r+1; k++){
        if(i < n1 && j < n2){
            if(left[i] < right[j]){
                a[k] = left[i];
                i++;
            }
            else{
                a[k] = right[j];
                j++;
            }
        }
        else if(i >= n1){
            a[k] = right[j];
            j++;
        }
        else if(j >= n2){
            a[k] = left[i];
            i++;
        }
    }
    
    
}

//合并主程序
void MergeSort(int * a, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        MergeSort(a, p, q);
        MergeSort(a, q+1, r);
        Merge2(a, p, q, r);
    }
}



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
int BinarySearchIteration(int *a, int n, int x){
    int low = 0;
    int high = x;
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

