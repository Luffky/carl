//
//  main.cpp
//  平均排序(思考题8-5)
//
//  Created by 伏开宇 on 2017/3/11.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <stdint.h>
using namespace std;
#define COUNT(a, b, k, s) (((b) - (a)) / (k) + ((((s) - (a) % (k)) + (k)) % (k) < ((b) - (a)) % (k) ? 1 : 0))
#define FIRST(index, k, s) ((index) + (s) - (index) % (k) + ((index) % (k) <= (s) ? 0 : (k)))
//思考题8-5
void Merge(int *A, int p, int q, int r, int k, int s) {
    int i, j, l;
    
    int n1 = COUNT(p, q, k, s);
    int n2 = COUNT(q, r, k, s);
    
    int L[n1];
    int R[n2];
    
    for (i = FIRST(p, k, s), j = 0; i < q; j++, i += k) L[j] = A[i];
    for (i = FIRST(q, k, s), j = 0; i < r; j++, i += k) R[j] = A[i];
    
    for(i = 0, j = 0, l = FIRST(p, k, s); l < r; l += k) {
        if (i == n1) {
            A[l] = R[j++];
        } else if (j == n2) {
            A[l] = L[i++];
        } else if (L[i] <= R[j]) {
            A[l] = L[i++];
        } else {
            A[l] = R[j++];
        }
    }
}

void MergeSort(int *a, int p, int q, int k, int i){
    if(COUNT(p, q, k, i) > 1){
        int r = (p+q)/2;
        MergeSort(a, p, r, k, i);
        MergeSort(a, r, q, k, i);
        Merge(a, p, r, q, k, i);
    }
}
void Ksort(int * a, int k, int n){
    for(int i = 0; i < k; i++){
        MergeSort(a, 0, n, k, i);
    }
}



struct Data{
public:
    int a;
    int no;
};

struct Heap{
public:
    Data * a;
    int heap_size;
    int heap_length;
};




void Minize(Heap h, int i){
    int smallest = i;
    if(2 * i + 1 < h.heap_size && h.a[i].a > h.a[2 * i + 1].a)
        smallest = 2 * i + 1;
    if(2 * i + 2 < h.heap_size && h.a[smallest].a > h.a[2 * i + 2].a)
        smallest = 2 * i + 2;
    if(i != smallest){
        Data temp = h.a[i];
        h.a[i] = h.a[smallest];
        h.a[smallest] = temp;
        Minize(h, smallest);
    }
}
void BuildHeap(Heap h){
    for(int i = h.heap_size / 2 - 1; i >= 0; i--){
        Minize(h, i);
    }
}
void HeapPop(Heap h, int *a){
    int k = h.heap_size;
    for (int i = 0; i < h.heap_length; i++) {
        a[i] = h.a[0].a;
        if (h.a[0].no + k < h.heap_length) {
            h.a[0] = h.a[h.a[0].no + k];
            Minize(h, 0);
        }
        else{
            h.heap_size --;
            h.a[0] = h.a[h.heap_size];
            Minize(h, 0);
        }
    }
}



int main(int argc, const char * argv[]) {
    int a[100];
    for(int i = 0; i < 100; i ++){
        a[i] = arc4random_uniform(500);
    }
    
    int k = 5;
    Ksort(a, k, 100);//k排序
    
    Data b[100];
    for (int i = 0; i < 100; i++) {
        b[i].a = a[i];
        b[i].no = i;
        cout<<b[i].a<<" ";
    }
    cout<<endl;
    
    int c[100];
    Heap h = {b, k, 100};
    BuildHeap(h);
    HeapPop(h, c);
    for (int i = 0; i < 100; i++) {
        cout<<c[i]<<" ";
    }
    cout<<endl;
    return 0;
}
