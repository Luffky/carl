//
//  main.cpp
//  小型顺序统计量(思考题9-3）
//
//  Created by 伏开宇 on 2017/3/13.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
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

int SelectExOut(int *a, int p ,int q,int i){
    if(i < (p - q) / 2){
        int **b = new int* [2];
        int n = q - p + 1;
        int j = 0;
        b[0] = new int[n / 2 + 1];
        b[1] = new int[n / 2 + 1];
        for(int i = p; i < q; i += 2){
            if(a[i] < a[i + 1]){
                b[0][j] = a[i];
                b[1][j++] = a[i + 1];
            }
            else{
                b[0][j] = a[i + 1];
                b[1][j++] = a[i];
            }
            if(i + 2 == q){
                b[0][j] = a[i + 2];
                b[1][j++] = a[i + 2];
            }
        }
        return SelectExOut(b[0], 0, j, i);
        
    }
    else
        return SelectOut(a, p, q, i);
}
int main(int argc, const char * argv[]) {
    
    return 0;
}
