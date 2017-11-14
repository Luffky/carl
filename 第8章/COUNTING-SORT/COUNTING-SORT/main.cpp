//
//  main.cpp
//  COUNTING-SORT
//
//  Created by 伏开宇 on 2017/3/9.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//计数排序 非比较排序

void CountingSort(int * a, int * b, int k, int n){
    int * c = new int[k];
    c[0] = -1;
    for(int i = 1; i < k; i++){
        c[i] = 0;
    }
    for(int i = 0; i < n; i++){
        c[a[i]] ++;
    }
    for(int i = 1; i <= k; i++){
        c[i] = c[i] + c[i-1];
    }
    for(int i = 0; i < n; i++){
        b[c[a[i]]--] = a[i];
    }
}
//8.2-4练习
void Counting(int * a, int * c, int k, int n){
    c[0] = -1;
    for(int i = 1; i < k; i++){
        c[i] = 0;
    }
    for(int i = 0; i < n; i++){
        c[a[i]] ++;
    }
    for(int i = 1; i <= k; i++){
        c[i] = c[i] + c[i-1];
    }
}

int CountringMain(int * c, int a, int b){
    return c[b] - c[a-1];
}
///////////////////////////////////////


int main(int argc, const char * argv[]) {
    int * a = new int[20];
    int * b = new int[20];
    for (int i = 0; i < 20; i++) {
        a[i] = arc4random_uniform(51);
    }
    for (int i = 0; i < 20; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
    CountingSort(a, b, 50, 20);
    
    for (int i = 0; i < 20; i++) {
        cout<<b[i]<<" ";
    }
    cout<<endl;
    return 0;
}
