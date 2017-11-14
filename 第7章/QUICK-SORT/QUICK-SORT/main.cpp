//
//  main.cpp
//  QUICK-SORT
//
//  Created by 伏开宇 on 2017/3/8.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;

class vector{
public:
    int t;
    int q;
};

//插入排序
void InsertSort(int *a,int n){
    int key;
    for(int i = 1; i < n; i++){
        key = a[i];
        int j = i - 1;
        while(a[j] > key and j >= 0){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}





//快速排序思考题7-3
vector Partition1(int *a, int p, int r){
    int key = a[r];
    int i = p - 1;
    int t;
    for(int j = p; j < r; j++){
        if(a[j] < key){
            i++;
            int temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
        
    }
    int temp = a[r];
    a[r] = a[i+1];
    a[i+1] = temp;
    for(t = i + 2; t <= r and a[t] == key; t++){
    }
    for(int j = r; j > t; j--){
        if(a[j] == key){
            a[j] = a[t];
            a[t++] = key;
        }
    }
    vector result = {i, t};
    return result;
}

vector RandomPartition1(int *a, int p, int r){
    int k = arc4random_uniform(r-p+1)+p;
    
    int temp = a[r];
    a[r] = a[k];
    a[k] = temp;
    return Partition1(a, p, r);
}

void QuickSort2(int *a, int p, int r){
    if(p < r){
        vector v;
        v = RandomPartition1(a, p, r);
        QuickSort2(a, p, v.t);
        QuickSort2(a, v.q, r);
    }
}
///////////////////////////


//快速排序
int Partition(int *a, int p, int r){
    int key = a[r];
    int i = p - 1;
    for(int j = p; j < r; j++){
        if(a[j] <= key){
            i++;
            int temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
        
    }
    int temp = a[r];
    a[r] = a[i+1];
    a[i+1] = temp;
    return i + 1;
}

int RandomPartition(int *a, int p, int r){
    int k = arc4random_uniform(r-p+1)+p;
    
    int temp = a[r];
    a[r] = a[k];
    a[k] = temp;
    return Partition(a, p, r);
}


void QuickSort(int *a, int p, int r){
    if(p < r){
        int q = RandomPartition(a, p, r);
        QuickSort(a, p, q - 1);
        QuickSort(a, q +  1, r);
    }
}
//尾递归版快速排序 思考题7-4
void TailQuickSort(int *a, int p, int r){
    while(p < r){
        int q = RandomPartition(a, p, r);
        if(q - p > r - q){
            QuickSort(a, q + 1, r);
            r = q - 1;
        }
        else{
            QuickSort(a, p, q - 1);
            p = q + 1;
        }
    }
}

//插入快速混合排序7.4-5 练习
void QuickSort1(int *a, int p, int r){
    if(r-p+1>5){
        int q = Partition(a, p, r);
        QuickSort1(a, p, q - 1);
        QuickSort1(a, q+  1, r);
    }
}

///////////////////////////////////////////////
//思考题7-1
int HoarePartition(int *a, int p, int r){
    int x = a[p];
    int i = p - 1;
    int j = r + 1;
    while(true){
        do{
            j--;
        }while(a[j] > x);
        do{
            i++;
        }while(a[i] < x);
        if(i < j){
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        else{
            return j;
        }
    }
}

void HoareQuickSort(int *a, int p, int r){
    if(p < r){
        int q = HoarePartition(a, p, r);
        HoareQuickSort(a, p, q);
        HoareQuickSort(a, q+1, r);
    }
}





int main(int argc, const char * argv[]) {
    int n = 10;
    int * a = new int[n];
    for(int i = 0; i < n; i++){
        a[i] = arc4random_uniform(50);
    }
    
    for(int i = 0 ; i < n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    QuickSort2(a, 0, n-1);
    //InsertSort(a, n);
    for(int i = 0 ; i < n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    
    
    return 0;
}
