//
//  main.cpp
//  SELECTION-SORT
//
//  Created by 伏开宇 on 2017/3/2.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//升序选择排列2.2-2练习题
void SelectionSort(int * a, int n){
    for(int i = 0; i<n-1; i++){
        int min = i;
        for(int j = i+1; j<n; j++){
            if(a[min] > a[j])
                min = j;
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}



int main(int argc, const char * argv[]) {
    int n;
    int *a = new int [n];
    cin>>n;
    for(int i = 0; i<n; i++)
        cin>>a[i];
    cout<<endl;
    SelectionSort(a, n);
    for(int i = 0; i<n; i++)
        cout<<a[i]<<" ";
    
    cout<<endl;
    return 0;
}
