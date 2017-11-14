//
//  main.cpp
//  整齐打印(思考题15-4）
//
//  Created by 伏开宇 on 2017/3/27.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
void print(int* p, int i){
    if(p[i] != 0){
        print(p, p[i] - 1);
        for(int j = p[i]; j <= i; j++)
            cout<<j<<" ";
        cout<<endl;
     
    }
}
void PrintNeatly(int* l, int n,int m){
    int** extras = new int*[n];
    int** lc = new int*[n];
    int* c = new int[n + 1];
    int* p = new int[n + 1];
    for(int i = 0 ; i < n; i++){
        extras[i] = new int[n];
        lc[i] = new int[n];
        extras[i][i] = m - l[i];
        if(extras[i][i] < 0)
            lc[i][i] = INT32_MAX/2;
        else if(i == n - 1 and extras[i][i] >= 0)
            lc[i][i] = 0;
        else
            lc[i][i] = extras[i][i] * extras[i][i] * extras[i][i];
        for(int j = i + 1 ; j < n; j++){
            extras[i][j] = extras[i][j - 1] - 1 - l[j];
            if(extras[i][j] < 0)
                lc[i][j] = INT32_MAX/2;
            else if(j == n - 1 and extras[i][j] >= 0)
                lc[i][j] = 0;
            else
                lc[i][j] = extras[i][j] * extras[i][j] * extras[i][j];
        }
    }
    for(int i = 0 ; i <= n; i++){
        if(i == 0){
            c[i] = 0;
            p[i] = 0;
        }
        else{
            c[i] = INT32_MAX/2;
            for(int j = i - 1; j >= 0; j--){
                if(c[i] > c[j] + lc[j][i - 1]){
                    c[i] = c[j] + lc[j][i - 1];
                    p[i] = j + 1;
                }
            }
        }
    }
    for(int i = 0 ; i <= n;i++)
        cout<<c[i]<<" "<<p[i]<<" ";
    cout<<endl;
    print(p, n);
}
int main(int argc, const char * argv[]) {
    int n,m;
    n = 7;
    m = 10;
    int* l = new int[n];
    for(int i = 0 ; i < n; i++){
        int k;
        cin>>k;
        l[i] = k;
    }
    PrintNeatly(l, n, m);
    return 0;
}
