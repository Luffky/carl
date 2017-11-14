//
//  main.cpp
//  双调欧几里得问题(思考题15-3)
//
//  Created by 伏开宇 on 2017/3/26.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;
class Point{
public:
    double x;
    double y;
    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
    void Copy(Point* p){
        x = p->x;
        y = p->y;
    }
};
void Merge(Point**m ,int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    Point** left = new Point*[n1 + 1];
    Point** right = new Point*[n2 + 1];
    for(int i = 0 ; i < n1; i++){
        left[i] = new Point(0, 0);
        left[i]->Copy(m[p + i]);
    }
    for(int i = 0 ; i < n2; i++){
        right[i] = new Point(0, 0);
        right[i]->Copy(m[q + i + 1]);
    }
    left[n1] = new Point(INT32_MAX, 0);
    right[n2] = new Point(INT32_MAX, 0);
    int L = 0;
    int R = 0;
    for (int i = p; i <= r; i++) {
        if(left[L]->x <= right[R]->x)
            m[i]->Copy(left[L++]);
        else
            m[i]->Copy(right[R++]);
    }
}
void MergeSort(Point** m, int p, int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(m, p, q);
        MergeSort(m, q + 1, r);
        Merge(m, p, q, r);
    }
}
double Distance(Point* a, Point* b){
    double t = sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
    return t;
}
void Print(int** r, int i ,int j){
    if(i < j){
        int k = r[i][j];
        cout<<k;
        if(k > 0)
            Print(r, i, k);
    }
    else{
        int k = r[j][i];
        if(k > 0){
            Print(r, k, j);
            cout<<k<<" ";
        }
        
    }
}
void Euclidean(Point** p, int n){
    MergeSort(p, 0, n - 1);
    double** b = new double*[n];
    int** r = new int*[n];
    for(int i = 0 ; i < n; i++){
        b[i] = new double[n];
        r[i] = new int[n];
        b[i][i] = 0;
    }
    for(int i = 0 ; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(j == i + 1 and i != 0){
                b[i][j] = INT32_MAX;
                for(int k = 0; k < i; k++){
                    if(b[i][j] > b[k][i] + Distance(p[k], p[j])){
                        b[i][j] = b[k][i] + Distance(p[k], p[j]);
                        r[i][j] = k;
                    }
                }
            }
            else{
                b[i][j] = b[i][j - 1] + Distance(p[j - 1], p[j]);
                r[i][j] = j - 1;
            }
        }
    }
    b[n - 1][n - 1] = b[n - 2][n - 1] + Distance(p[n - 2], p[n - 1]);
    r[n - 1][n - 1] = n - 2;
    cout<<b[n - 1][n - 1]<<endl;
    //打印路径
    cout<<n - 1;
    cout<<n - 2;
    int k = r[n - 2][n - 1];
    Print(r, k, n - 2);
    cout<<k;
    cout<<endl;
}


int main(int argc, const char * argv[]) {
    int n = 4;
    Point** p = new Point*[n];
    for(int i = 0 ; i < n; i++){
        int j,k;
        cin>>j>>k;
        p[i] = new Point(j, k);
    }
    Euclidean(p, n);
    return 0;
}
