//
//  main.cpp
//  最长回文子序列(思考题15-2)
//
//  Created by 伏开宇 on 2017/3/26.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//最长回文子序列
void PrintLongest(string p, int i, int j, int** seq){
    if(i == j)
        cout<<p[i];
    else if(i < j){
        if(seq[i][j] == 1){
            cout<<p[i];
            PrintLongest(p, i + 1, j - 1, seq);
            cout<<p[j];
        }
        else if(seq[i][j] == 0){
            PrintLongest(p, i, j - 1, seq);
        }
        else{
            PrintLongest(p, i + 1, j, seq);
        }
    }
}
void Longest(string p, int n){
    int** lps = new int*[n];
    int** seq = new int*[n];
    for(int i = 0 ; i < n; i++){
        lps[i] = new int[n];
        seq[i] = new int[n];
        lps[i][i] = 1;
        seq[i][i] = p[i];
    }
    for(int l = 2; l <= n; l++){
        for(int i = 0; i < n + 1 - l; i++){
            if(p[i] == p[i + l - 1]){
                lps[i][i + l - 1] = lps[i + 1][i + l - 2] + 2;
                seq[i][i + l - 1] = 1;
            }
            else if(lps[i + 1][i + l - 1] >= lps[i][i + l - 2]){
                lps[i][i + l - 1] = lps[i + 1][i + l - 1];
                seq[i][i + l - 1] = 2;
            }
            else{
                lps[i][i + l - 1] = lps[i][i + l - 2];
                seq[i][i + l - 1] = 0;
            }
            
        }
    }
    PrintLongest(p, 0, n - 1, seq);
    cout<<endl;
}
//备忘录法
int Lookup(int** seq, int** lps, int i, int j, string p){
    if(lps[i][j] > 0)
        return lps[i][j];
    else{
        if(p[i] == p[j]){
            lps[i][j] = Lookup(seq, lps, i + 1, j - 1, p)+ 2;
            seq[i][j] = 1;
        }
        else{
            int t = Lookup(seq, lps, i, j - 1, p);
            int r = Lookup(seq, lps, i + 1, j, p);
            if(t >= r){
                lps[i][j] = t;
                seq[i][j] = 0;
            }
            else{
                lps[i][j] = r;
                seq[i][j] = 2;
            }
        }
        return lps[i][j];
    }
}
void momoized(string p, int n){
    int** lps = new int*[n];
    int** seq = new int*[n];
    for(int i = 0; i < n; i++){
        lps[i] = new int[n];
        seq[i] = new int[n];
        for(int j = 0 ; j < n; j++){
            seq[i][j] = 0;
            if(i == j)
                lps[i][j] = 1;
            else
                lps[i][j] = 0;
        }
    }
    
    Lookup(seq, lps, 0, n - 1, p);
    for(int i = 0 ; i < n; i++){
        for(int j = 0 ; j < n; j++)
            cout<<seq[i][j]<<" ";
        cout<<endl;
    }
    PrintLongest(p, 0, n - 1, seq);
    cout<<endl;
}
int main(int argc, const char * argv[]) {
    string s = "character";
    //Longest(s, 8);
    momoized(s, 8);
    return 0;
}
