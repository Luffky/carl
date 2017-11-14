//
//  select.hpp
//  GREEDY-ALGORITHM
//
//  Created by 伏开宇 on 2017/3/28.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef select_hpp
#define select_hpp
#include <stdio.h>
#include <iostream>
using namespace std;

//线性查找第i顺序统计量 第九章第三节
int n = 100;
struct middle{
public:
    int value;
    int num;
};
void view(middle *a, int n){
    for(int i = 0;i < n; i++){
        cout<<a[i].value<<" "<<a[i].num<<" ";
    }
    cout<<endl;
    cout<<endl;
}



void view(int *a){
    for(int i = 0; i < n; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    cout<<endl;
}

middle InsertSort(int *a, int p, int q){
    for (int i = p + 1; i <= q; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= p and a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    middle temp = {a[(p + q) / 2], (p + q) / 2};
    return temp;
}

middle InsertSort(middle *a, int p, int q){
    for (int i = p + 1; i <= q; i++) {
        middle key = a[i];
        int j = i - 1;
        while (j >= p and a[j].value > key.value) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
    middle temp = a[(p + q) / 2];
    return temp;
}

middle Select(middle * a, int p , int q){
    middle * Middle = new middle[(q - p + 1)/5 + 1];
    int k = 0;
    for (int i = p; i <= q; i += 5) {
        if(i + 4 <= q){
            Middle[k] = InsertSort(a, i, i + 4);
        }
        else
            Middle[k] = InsertSort(a, i, q);
        k++;
    }
    //view(Middle, (q - p + 1)/5 + 1);
    if (k == 1) {
        return Middle[0];
    }
    else
        return Select(Middle, 0, k - 1);
}

middle Select(int * a, int p , int q){
    middle * Middle = new middle[(q - p + 1)/5 + 1];
    int k = 0;
    for (int i = p; i <= q; i += 5) {
        if(i + 4 <= q){
            Middle[k] = InsertSort(a, i, i + 4);
        }
        else
            Middle[k] = InsertSort(a, i, q);
        k++;
    }
    
    return Select(Middle, 0, k - 1);
}

int Partition(int *a, int p, int r){
    int key = a[r];
    int i = p - 1;
    for(int j = p; j < r; j ++){
        if(a[j] <= key){
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
        
    }
    a[r] = a[i + 1];
    a[i + 1] = key;
    return i + 1;
}

int SelectOut(int *a, int p, int q, int i){
    middle temp = Select(a, p, q);
    int temp1 = a[q];
    a[q] = temp.value;
    a[temp.num] = temp1;
    int r = Partition(a, p, q);
    if(r == i - 1)
        return a[r];
    else if(r < i - 1)
        return SelectOut(a, r + 1, q, i);
    else
        return SelectOut(a, p, r - 1, i);
}

class Node1{
public:
    int r;
    int p;
    string name;
    Node1(int p, int r, string s){
        this->r = r;
        this->p = p;
        name.assign(s);
    }
};
//最小优先队列
class Heap{
public:
    Node1** a;
    int heap_size;
    int length;
    Heap(Node1** b, int l){
        a = b;
        length = l;
    }
    void MinHeapify(int i);
    void BuildHeap();
    Node1* HeapMinimum();
    Node1* HeapExtractMin();
    void HeapInsert(Node1* a);
    void DecreaseKey(int i, int k);
};
void Heap::MinHeapify(int i){
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int smallest = i;
    if(l < heap_size and a[smallest]->p > a[l]->p){
        smallest = l;
    }
    if(r < heap_size and a[smallest]->p > a[r]->p){
        smallest = r;
    }
    if(smallest != i){
        Node1* temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;
        MinHeapify(smallest);
    }
}
void Heap::BuildHeap(){
    heap_size = length;
    for(int i = heap_size / 2 - 1; i >= 0; i--){
        MinHeapify(i);
    }
}
Node1* Heap::HeapMinimum(){
    return a[0];
}
Node1* Heap::HeapExtractMin(){
    if(heap_size < 1)
        exit(0);
    Node1* temp = a[0];
    heap_size--;
    a[0] = a[heap_size];
    MinHeapify(0);
    return temp;
}
void Heap::DecreaseKey(int i, int k){
    if(k > a[i]->p){
        cout<<"减小关键字大于原关键字，减小失败"<<endl;
        return;
    }
    a[i]->p = k;
    int p = (i - 1) / 2;
    while(1){
        if(a[i]->p < a[p]->p){
            Node1* temp = a[p];
            a[p] = a[i];
            a[i] = temp;
        }
        i = p;
        if(i == 0)
            break;
        p = (p - 1) / 2;
    }
}
void Heap::HeapInsert(Node1* b){
    if(heap_size == length){
        cout<<"堆已满"<<endl;
        return;
    }
    a[heap_size++] = b;
    int k = b->p;
    b->p = INT32_MAX;
    DecreaseKey(heap_size - 1, k);
}
#endif /* select_hpp */
