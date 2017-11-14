//
//  main.cpp
//  在棋盘上移动(思考题15-6)
//
//  Created by 伏开宇 on 2017/3/27.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
#define N 3
//棋盘权值
int chessboard[N][N][3] = {{{-1,1,2},{2,5,3},{7,2,-1}},
                           {{-1,1,2},{4,3,7},{4,2,-1}},
                           {{-1,1,2},{2,7,3},{4,2,-1}}};
class point{
public:
    int x;
    int y;
    point(int x, int y){
        this->x = x;
        this->y = y;
    }
    void copy(point* p){
        x = p->x;
        y = p->y;
    }
};
//得到两点之间的权值
int GetValue(point* a, point* b){
    int x1 = a->x;
    int x2 = b->x;
    int y1 = a->y;
    int y2 = b->y;
    if(y1 + 1 == y2){
        if(x1 - x2 == 0){
            return chessboard[y1][x1][1];
        }
        else if(x1 - x2 == 1){
            return chessboard[y1][x1][0];
        }
        else if(x1 - x2 == -1){
            return chessboard[y1][x1][2];
        }
        else{
            cout<<"移动错误"<<endl;
            exit(0);
        }
    }
    else{
        cout<<"移动错误"<<endl;
        exit(0);
    }
}
//打印走法
void Print(int** w, int i, int j){
    if(w[i][j] != -1){
        Print(w, i - 1, w[i][j]);
        cout<<i<<" "<<j<<endl;
    }
    else
        cout<<i<<" "<<j<<endl;
    
}
void ProfitableMove(int n){
    int** d = new int*[n];
    int** w = new int*[n];
    for(int i = 0 ; i < n; i++){
        d[i] = new int[n];
        w[i] = new int[n];
        if(i == 0){
            for(int j = 0 ; j < n; j++){
                d[i][j] = 0;
                w[i][j] = -1;
            }
        }
        else{
            for(int j = 0 ; j < n; j++){
                d[i][j] = INT32_MIN;
                point* temp = new point(j, i);
                point* a = new point(j - 1, i - 1);
                point* b = new point(j, i - 1);
                point* c = new point(j + 1, i - 1);
                int left = GetValue(a, temp);
                int right = GetValue(c, temp);
                int mid = GetValue(b, temp);
                if(j > 0){
                    d[i][j] = d[i - 1][j - 1] + left;
                    w[i][j] = j - 1;
                }
                if(d[i - 1][j] + mid > d[i][j]){
                    d[i][j] = d[i - 1][j] + mid;
                    w[i][j] = j;
                }
                if(j < n - 1 and d[i - 1][j + 1] + right > d[i][j]){
                    d[i][j] = d[i - 1][j + 1] + right;
                    w[i][j] = j + 1;
                }
            }
        }
    }
    int k = d[n - 1][0];
    int l = 0;
    for(int i = 1; i < n; i++){
        if(k < d[n - 1][i]){
            k = d[n - 1][i];
            l = i;
        }
    }
    cout<<k<<endl;
    Print(w, n - 1, l);
}
int main(int argc, const char * argv[]) {
    ProfitableMove(N);
    return 0;
}
