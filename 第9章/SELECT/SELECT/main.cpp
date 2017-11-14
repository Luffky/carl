//
//  main.cpp
//  SELECT
//
//  Created by 伏开宇 on 2017/3/12.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

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



//9.3-6练习
void Kth(int a[], int *b, int p, int q, int k){
    
    if(k == 1)
        return;
    else if(k % 2 == 0){
        int median = SelectOut(a, p, q, (p + q) / 2 + 1);
        cout<<median<<endl;
        Kth(a, b, p, (p + q) / 2 - 1, k / 2);
        Kth(a, b, (p + q) / 2 + 1, q, k / 2);
    }
    else{
        int bound1 = (q - p + 1) / k * (k / 2) + p;
        int bound2 = (q - p + 1) / k * (k / 2 + 1) + p;
        int left = SelectOut(a, p, q, bound1 + 1);
        int right = SelectOut(a, p, q, bound2 + 1);
        cout<<left<<" "<<right<<" "<<endl;
        Kth(a, b, p, bound1 - 1, k / 2);
        Kth(a, b, p, bound2 - 1, k / 2);
    }
}
//9.3-8练习
int Nine(int *a, int *b, int p, int q, int r, int s){
    int left = a[(q - p) / 2];
    int right = b[(s - r) / 2];
    if(left < right)
        return Nine(a, b, (q - p) / 2, q, r, (s - r) / 2);
    else if(right > left)
        return Nine(a, b, p, (q - p) / 2, (s - r) / 2, s);
    else
        return left;
}



int main(int argc, const char * argv[]) {
    int a[100];
    int b[100];

    for(int i = 0; i < n; i++){
        a[i] = arc4random_uniform(500);
        b[i] = a[i];
    }
    view(a);
    int k = 7;
    int * c = new int[k - 1];
    Kth(a, c, 0, n - 1, k);
    //cout<<SelectOut(a, 0, n - 1, 50)<<endl;
    InsertSort(a, 0, 99);
    
    cout<<endl;
    
   
    
    return 0;
}
