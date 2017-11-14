//
//  main.cpp
//  INTERVALTREE
//
//  Created by 伏开宇 on 2017/3/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
#define N 5
#define INFTY 99999999
void Initial(IntervalTreeNode **a){
    cout<<"请输入"<<N<<"个整数"<<endl;
    for(int i = 0 ; i < N; i ++){
        int j;
        int k;
        cin>>j>>k;
        Int* temp = new Int(j,k);
        a[i] = new IntervalTreeNode(temp, -1);
    }
}
//重叠矩形问题14.3-7练习
class Rectangle{
public:
    int x1;
    int x2;
    int y1;
    int y2;
    Rectangle(int a, int b, int c, int d){
        x1 = a;
        x2 = b;
        y1 = c;
        y2 = d;
    }
};//矩形对象
class bbb{
public:
    int x;
    int i;
    int n;
    bbb(int a, int b, int c){
        x = a;
        i = b;
        n = c;
    }
    void copy(bbb* a){
        x = a->x;
        i = a->i;
        n = a->n;
    }
};//矩形竖边对象
void Merge(bbb** a, int p, int q, int r){
    int n1, n2;
    n1 = q - p + 1;
    n2 = r - q;
    bbb** left = new bbb* [n1+1];
    bbb** right = new bbb* [n2+1];
    for(int i = 0; i<n1; i++){
        left[i] = new bbb(a[p+i]->x, a[p+i]->i, a[p+i]->n);
    }
    for(int i = 0; i<n2; i++){
        right[i] = new bbb(a[q+1+i]->x, a[q+1+i]->i, a[q+1+i]->n);
    }
    left[n1] = new bbb(INFTY,0,0);
    right[n2] = new bbb(INFTY,0,0);
    int k = 0;
    int l = 0;
    for(int i = p; i<r+1; i++){
        if(left[k]->x < right[l]->x){
            a[i]->copy(left[k]);
            k++;
        }
        else if(left[k]->x == right[l]->x){
            left[k]->i <= right[l]->i ? a[i]->copy(left[k++]) : a[i]->copy(right[l++]);
        }
        else{
            a[i]->copy(right[l]);
            l++;
        }
    }
}
void MergeSort(bbb** a, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        MergeSort(a, p, q);
        MergeSort(a, q+1, r);
        Merge(a, p, q, r);
    }
}

int main(int argc, const char * argv[]) {
    Rectangle** temp = new Rectangle*[N];
    for(int i = 0; i < N; i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        temp[i] = new Rectangle(a,b,c,d);
    }
    bbb** temp1 = new bbb*[N * 2];
    int l = 0;
    for(int i = 0; i < 2 * N; i += 2){
        temp1[i] = new bbb(temp[l]->x1, 0, l);
        temp1[i + 1] = new bbb(temp[l]->x2, 1, l);
        l++;
    }
    int n = 0;
    IntervalTreeNode** temp3 = new IntervalTreeNode*[N];
    IntervalTree* b = new IntervalTree();
    MergeSort(temp1, 0, 2 * N - 1);
    for(int i = 0 ; i < 2 * N; i++){
        if(temp1[i]->i == 0){
            Int* temp2 = new Int(temp[temp1[i]->n]->y1, temp[temp1[i]->n]->y2);
            cout<<"("<<temp2->low<<","<<temp2->high<<")"<<endl;
            b->IntervalSearchAll(b->root, temp2, &n);
            cout<<endl;
            temp3[temp1[i]->n] = new IntervalTreeNode(temp2, -1);
            b->IntervalTreeInsert(temp3[temp1[i]->n]);
            
        }
        else{
            b->IntervalTreeDelete(temp3[temp1[i]->n]);
        }
            
    }
    cout<<"共有"<<n<<"对重叠矩形"<<endl;
    cout<<endl;
    return 0;
}
