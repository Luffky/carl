//
//  main.cpp
//  RANDOMLIZED-SELECT
//
//  Created by 伏开宇 on 2017/3/12.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//
int Partition(int *a, int p, int q){
    int key = a[q];
    int i = p - 1;
    for (int j = p; j < q; j++) {
        if(a[j] <= key){
            i++;
            int temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
    a[q] = a[i + 1];
    a[i + 1] = key;
    return i + 1;
}

int RandomlizedPartition(int *a, int p, int q){
    int r = arc4random_uniform(q - p + 1) + p;
    int temp = a[r];
    a[r] = a[q];
    a[q] = temp;
    return Partition(a, p, q);
}
//递归版本
int RandomlizedSelect(int *a, int p, int q, int i){
    if(p == q)
        return a[p];
    int r = RandomlizedPartition(a, p, q);
    
    
    if (r - p + 1 == i)
        return a[r];
    else if(r - p + 1 > i)
        return RandomlizedSelect(a, p, r - 1, i);
    else
        return RandomlizedSelect(a, r + 1, q, i - r + p - 1);
}
//迭代版本 9.2-3
int RandomlizedSelect1(int *a, int p, int q, int i){
    if(p == q)
        return a[p];
    int r = RandomlizedPartition(a, p, q);
    while (r - p + 1 != i){
        if(r - p + 1 > i){
            q = r - 1;
        }
        else{
            i = i - r + p - 1;
            p = r + 1;
        }
        if(p == q)
            return a[p];
        r = RandomlizedPartition(a, p, q);
    }
    return a[r];
}

void view(int *a){
    for(int i = 0; i < 100; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
}


int main(int argc, const char * argv[]) {
    int a[100],b[100];
    for (int i = 0; i < 100; i++) {
        a[i] = arc4random_uniform(300);
    }
    for (int i = 0; i < 100; i++) {
        b[i] = a[i];
    }
    view(a);
    cout<<endl;
    cout<<endl;
    cout<<RandomlizedSelect(a, 0, 99, 99);
    cout<<endl;
    cout<<RandomlizedSelect1(a, 0, 99, 99);
    cout<<endl;
    
    return 0;
}
