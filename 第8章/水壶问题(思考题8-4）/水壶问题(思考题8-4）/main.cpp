//
//  main.cpp
//  水壶问题(思考题8-4）
//
//  Created by 伏开宇 on 2017/3/11.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
int RPartition(int *Red, int p, int r, int key){
    int i = p - 1;
    int place = 0;
    for (int j = p; j <= r; j++) {
        if(Red[j] < key){
            i++;
            int temp = Red[j];
            Red[j] = Red[i];
            Red[i] = temp;
        }
        else if(Red[j] == key){
            i++;
            int temp = Red[j];
            Red[j] = Red[i];
            Red[i] = temp;
            place = i;
        }
    }
    return place;
}

int BPartition(int *Blue, int p, int r, int key){
    int i = p - 1;
    for(int j = p; j <= r; j++){
        if(Blue[j] <= key){
            i++;
            int temp = Blue[j];
            Blue[j] = Blue[i];
            Blue[i] = temp;
        }
    }
    return i;
}

void QuickSort(int *Red, int *Blue, int p, int r){
    if(p < r){
        int k = arc4random_uniform(r - p + 1) + p;
        int l = RPartition(Red, p, r, Blue[k]);
        int q = BPartition(Blue, p, r, Red[l]);
        
        QuickSort(Red, Blue, p, q);
        QuickSort(Red, Blue, q + 1, r);
    }
}

void View(int *a){
    for(int i = 0; i < 100; i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    cout<<endl;
}



int main(int argc, const char * argv[]) {
    int n = 100;
    int *a = new int[n];
    int *b = new int[n];
    for(int i = 0; i < n; i++){
        a[i] = i;
        b[i] = i;
    }
    
    for(int i = 0; i < 1000; i++){
        int m = arc4random_uniform(100);
        int n = arc4random_uniform(100);
        int temp = a[m];
        a[m] = a[n];
        a[n] = temp;
    }
    
    for(int i = 0; i < 1000; i++){
        int m = arc4random_uniform(100);
        int n = arc4random_uniform(100);
        int temp = b[m];
        b[m] = b[n];
        b[n] = temp;
    }
    
    QuickSort(a, b, 0, 99);
    
    
    View(a);
    View(b);
    
    cout<<"a"<<endl;
    return 0;
}
