//
//  main.cpp
//  最大重叠点(思考题14-1)
//
//  Created by 伏开宇 on 2017/3/22.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
using namespace std;
#define INFTY 9999999
#define N 10
class Int{
public:
    int low;
    int high;
    Int(int i ,int h){
        low = i;
        high = h;
    }
};
//端点对象
class bbb{
public:
    int x;  //端点坐标
    int i;  //端点类型
    int n;  //端点所在区间号
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
};
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
    //生成区间实例
    Int** interval = new Int*[N];
    for(int i = 0 ; i < N; i++){
        int j,k;
        cin>>j>>k;
        interval[i] = new Int(j, k);
    }
    //区间转化为端点对象
    bbb** point = new bbb*[2 * N];
    for(int i = 0 ; i < 2 * N; i = i + 2){
        point[i] = new bbb(interval[i / 2]->low, 0, i / 2);
        point[i + 1] = new bbb(interval[i / 2]->high, 1, i / 2);
    }
    //对端点进行排序
    MergeSort(point, 0, 2 * N - 1);
    //遍历2N端点，并且插入顺序统计树中
    RBTree* b = new RBTree();
    RBTreeNode** node = new RBTreeNode*[N];//N个区间对应N个结点
    int most = 0;
    int value = -1;
    for(int i = 0 ; i < 2 * N; i++){ //遍历端点
        if(point[i]->i == 0){ //若该端点是起点
            node[point[i]->n] = new RBTreeNode(point[i]->x, -1);//为该拥有该端点的区间生成一个红黑树结点
            b->RBTreeInsert(node[point[i]->n]);
            int rank = b->Rank(node[point[i]->n]);
            if(rank > most){
                most = rank;
                value = point[i]->x;
            }
        }
        else{//若该端点是终点
            b->RBTreeDelete(node[point[i]->n]);
        }
    }
    cout<<most<<" "<<value<<endl;
    
    
    
    return 0;
}
