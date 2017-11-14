//
//  main.cpp
//  BUBBLE-SORT
//
//  Created by 伏开宇 on 2017/3/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//冒泡排序2-2 思考题
void BubbleSort(int *a, int n){
    for(int i = 0; i<n-1; i++){
        for(int j = n-1; j>i; j--){
            if(a[j] < a[j-1]){
                int temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
            }
        }
    }
}
int main(int argc, const char * argv[]) {
    int a[6] = {6,5,4,3,2,3};
    BubbleSort(a, 6);
    for(int i = 0; i<6; i++){
        cout<<a[i]<<" ";
    }
    
    cout<<endl;
    return 0;
}
