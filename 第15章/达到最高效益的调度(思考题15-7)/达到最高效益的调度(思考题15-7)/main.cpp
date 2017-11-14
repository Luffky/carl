//
//  main.cpp
//  达到最高效益的调度(思考题15-7)
//
//  Created by 伏开宇 on 2017/3/27.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
class work{
public:
    int t;
    int p;
    int d;
    work(int a, int b, int c){
        t = a;
        p = b;
        d = c;
    }
    void copy(work* w){
        t = w->t;
        p = w->p;
        d = w->d;
    }
};
void print(int** select, work** w, int i, int j){
    if(i != 0){
        if(select[i][j] == 1){
            print(select, w, i - 1, j - w[i]->t);
            cout<<i<<" ";
        }
        else
            print(select, w, i - 1, j);
    }
}
void MaxProfit(work** work, int n, int m){
    int** s = new int*[n + 1];
    int** select = new int*[n + 1];
    for(int i = 0 ; i < n + 1; i++){
        s[i] = new int[m + 1];
        select[i] = new int[m + 1];
        s[i][0] = 0;
        select[i][0] = 0;
    }
    for(int i = 0 ; i < n + 1; i++){
        if(i == 0){
            for(int j = 0; j <= m; j++){
                s[i][j] = 0;
                select[i][j] = 0;
            }
        }
        else{
            for(int j = 1; j <= work[i]->d ; j++){
                //不调度i
                s[i][j] = s[i-1][min(j, work[i-1]->d)];
                select[i][j] = 0;
                //调度i
                if(j > work[i]->t){
                    if(s[i][j] < s[i-1][min(j - work[i]->t, work[i-1]->d)] + work[i]->p){
                        s[i][j] = s[i-1][min(j - work[i]->t, work[i-1]->d)] + work[i]->p;
                        select[i][j] = 1;
                    }
                }
            }
        }
    }
    cout<<s[n][m]<<endl;
    print(select, work, n, m);
}

int main(int argc, const char * argv[]) {
    int n = 5;
    work** w = new work*[n + 1];
    w[0] = new work(0,0,0);
    for(int i = 1 ; i <= n; i++){
        int t,p,d;
        t = arc4random_uniform(10) + 1;
        p = arc4random_uniform(8) + 1;
        d = arc4random_uniform(10)+10;
        w[i] = new work(t, p, d);
    }
    for(int i = 0; i < n + 1; i++){
        for(int j = n  ; j > i; j--){
            if(w[j]->d < w[j - 1]->d){
                work* temp = new work(0,0,0);
                temp->copy(w[j]);
                w[j]->copy(w[j - 1]);
                w[j - 1]->copy(temp);
            }
        }
    }
    for(int i = 0; i <= n; i++){
        cout<<w[i]->d<<" "<<w[i]->t<<" "<<w[i]->p<<endl;
    }
    MaxProfit(w, n, w[n]->d);
    return 0;
}
