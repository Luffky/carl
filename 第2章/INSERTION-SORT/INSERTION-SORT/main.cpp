//
//  main.cpp
//  INSERTION-SORT
//
//  Created by 伏开宇 on 2017/3/2.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//插入排序升序排列
void InsertionSortUpper(int * num, int n){
    int key = 0;
    for(int j = 1; j<n; j++){
        key = num[j];
        int i = j - 1;
        while(i > -1 && num[i] > key){
            num[i+1] = num[i];
            i--;
        }
        num[i+1] = key;
    }
    
    for(int i = 0 ; i<n; i++){
        cout<<num[i]<<" ";
    }
    cout<<endl;
}

//降序排列 2.1-2练习题
void InsertSortLower(int * num, int n){
    int key = 0;
    for(int j = 1; j<n; j++){
        key = num[j];
        int i = j - 1;
        while(i > -1 && num[i] < key){
            num[i+1] = num[i];
            i--;
        }
        num[i+1] = key;
    }
    
    for(int i = 0 ; i<n; i++){
        cout<<num[i]<<" ";
    }
    cout<<endl;
}

//2.1-3练习题
int Search(int * num, int n, int v){
    for(int i = 0; i<n; i++){
        if(v == num[i])
            return i;
    }
    return -1;
}


//2.1-4练习题
void BinaryAdd(int * a, int * b, int * c, int n){
    int carry = 0;
    for(int i = 0 ; i<n; i++){
        c[i] = (a[i] + b[i] + carry) % 2;
        carry = (a[i] + b[i] + carry) / 2;
    }
    c[n] = carry;
}


//插入排序递归方法2.3-4练习题
void Sort(int *a, int n){
    int key = a[n-1];
    int i = n-2;
    while(i > -1 and a[i] > key){
        a[i+1] = a[i];
        i--;
    }
    a[i+1] = key;
}

void InsertSortRecurrence(int *a, int n){
    if(n > 2)
        InsertSortRecurrence(a, n-1);
    Sort(a, n);
}

int main(int argc, const char * argv[]) {
    int n;
    cin>>n;
    int *num = new int [n];
    for(int i = 0; i<n; i++){
        cin >> num[i];
    }
    /*int *num1 = new int [n];
    for(int i = 0; i<n; i++){
        cin >> num1[i];
    }
    int *num2 = new int [n+1];
    BinaryAdd(num, num1, num2, n);
    */
    
    
    
    //InsertSortLower(num, n);
    //InsertionSortUpper(num, n);
    //cout<<Search(num, n, 31)<<endl;
    InsertSortRecurrence(num, n);
    for(int i = 0 ;i<n; i++){
        cout<<num[i]<<" ";
    }
    return 0;
}
