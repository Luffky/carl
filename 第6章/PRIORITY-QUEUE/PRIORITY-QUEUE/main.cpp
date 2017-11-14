//
//  main.cpp
//  PRIORITY-QUEUE
//
//  Created by 伏开宇 on 2017/3/6.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "HEAPSORT.hpp"
using namespace std;
//合并排序
void Merge(int *a, int p, int q, int r){
    int * left = new int[q-p+1];
    int * right = new int[r-q];
    for(int i = 0; i<q-p+1; i++){
        left[i] = a[p+i];
    }
    for(int i = 0; i<r-q; i++){
        right[i] = a[q+1+i];
    }
    int j = 0;
    int k = 0;
    for(int i = p; i<r+1; i++){
        if(j < q - p + 1 && k < r - q){
            if(left[j] > right[k])
                a[i] = left[j++];
            else
                a[i] = right[k++];
        }
        else if(j >= q - p + 1)
            a[i] = right[k++];
        else if(k >= r - q)
            a[i] = left[j++];
    }
}
void MergeSort(int *a, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        MergeSort(a, p, q);
        MergeSort(a, q+1, r);
        Merge(a,p,q,r);
    }
}

//k路已排序链表合并
void MergeKqueue(int a[][21], int b[], int n, int k){
    Type * data = new Type[k];
    for(int i = 0; i < k; i++){
        data[i].SetNum(a[i][0]);
        data[i].SetData(i);
    }
    Heap * h = new Heap(data,k,k);
    h->BuildMaxHeap();
    int *l = new int[k];
    for(int i = 0; i < k; i++){
        l[i] = 1;
    }
    for(int i = 0; i < n; i++){
        b[i] = h->HeapMaximum().GetNum();
        int queue = h->HeapMaximum().GetData();
        if(a[queue][l[queue]] != -1){
            h->SetNum(0, a[queue][l[queue]++]);
            h->MaxHeapify(0); //O(lgk)
        }
        else
            h->ExtractMax(); //O(lgk)
    } //O(n*lgk)

}


int main(int argc, const char * argv[]) {
    int k = 5;
    int n = 0;
    Type (*a)[21] = new Type[k][21];
    for(int i = 0; i < 1; i++){
        int temp = 20;
        n += temp;
        for(int j = 0; j < temp; j++){
            a[i][j].SetNum(arc4random_uniform(100));
        }
      
        for(int j = 0; j < temp ; j++)
            cout<<a[i][j].GetNum()<<" ";
        cout<<endl;
    }
    DxHeap * h = new DxHeap(a[0],20,20,3);
    h->IncreaseKey(5, 100);
    h->BuildMaxHeap();
    cout<<a[0][0].GetNum()<<endl;
    Type temp = h->ExtractMax();
    h->MaxHeapInsert(temp);
    cout<<a[0][0].GetNum()<<endl;
    
//    int b[200];
//    MergeKqueue(a, b, n, k);
//    for(int i = 0; i<n; i++){
//        cout<<b[i]<<" ";
//    }
//    cout<<endl;
    
    
    
    
   
    
    
//    Type * a = new Type[20];
//    Heap * h = new Heap(a,20,0);
//    h->BuildMaxHeap();
//    cout<<h->HeapMaximum().GetNum()<<endl;
//    for(int i = 0; i<10; i++){
//        Type b;
//        b.SetData(arc4random_uniform(200));
//        h->Insert(b);
//    }
//    for(int i = 0; i<h->GetHeapSize(); i++){
//        cout<<a[i].GetNum()<<" "<<a[i].GetData()<<endl;
//    }
//    h->HeapDelete(3);
//    
//    for(int i = 0; i<h->GetHeapSize(); i++){
//        cout<<a[i].GetNum()<<" "<<a[i].GetData()<<endl;
//    }
//    for(int i = 0; i<10; i++){
//        cout<<h->Delete().GetData()<<endl;
//    }
//    Type * a = new Type[20];
//    for (int i = 0; i < 10; i++) {
//        a[i].SetNum(arc4random_uniform(20));
//    }
//    for (int i = 0; i<20; i++) {
//        cout<<a[i].GetNum()<<" ";
//    }
//    cout<<endl;
//    Heap * h = new Heap(a,20,10);
//    h->BuildMaxHeap();
//    
//    cout<<h->HeapMaximum().GetNum()<<endl;
//    for (int i = 0; i<h->GetHeapSize(); i++) {
//        cout<<a[i].GetNum()<<" ";
//    }
//    cout<<endl;
//    
//    cout<<h->ExtractMax().GetNum()<<endl;
//    for (int i = 0; i<h->GetHeapSize(); i++) {
//        cout<<a[i].GetNum()<<" ";
//    }
//    cout<<endl;
//    
//    h->IncreaseKey(5, 30);
//    for (int i = 0; i<h->GetHeapSize(); i++) {
//        cout<<a[i].GetNum()<<" ";
//    }
//    cout<<endl;
//    
//    Type b;
//    b.SetNum(40);
//    
//    h->MaxHeapInsert(b);
//    
//    for (int i = 0; i<h->GetHeapSize(); i++) {
//        cout<<a[i].GetNum()<<" ";
//    }
    
//    h->HeapSort();
//    
//    for (int i = 0; i<10; i++) {
//        cout<<a[i].GetNum()<<" ";
//    }
    cout<<endl;
    return 0;
}
