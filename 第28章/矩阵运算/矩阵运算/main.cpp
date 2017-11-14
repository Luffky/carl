//
//  main.cpp
//  矩阵运算
//
//  Created by 伏开宇 on 2017/5/24.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;
//28.1 求解线性方程组
//正向替换和反向替换
double* Lup_Solve(double** L, double** U, int* pai, double* b, int n){
    double* x = new double[n + 1];
    double* y = new double[n + 1];
    for (int i = 1; i <= n; i++) { //正向替换
        double sum = 0;
        for (int j = 1; j <= i - 1; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = b[pai[i]] - sum;
    }
    for (int i = n; i >= 1; i--) {
        double sum = 0;
        for (int j = i + 1; j <= n; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }
    return x;
}
//计算LU分解
double*** Lu_Decomposition(double** A, int n){
    double** L = new double*[n + 1];
    double** U = new double*[n + 1];
    for (int i = 1; i <= n; i++) {
        L[i] = new double[n + 1];
        U[i] = new double[n + 1];
        for (int j = 1; j <= n; j++) {
            if(i == j)
                L[i][j] = 1;
            else
                L[i][j] = 0;
            U[i][j] = 0;
        }
    }
    for (int k = 1; k <= n; k++) {
        U[k][k] = A[k][k]; //选取主元
        for (int i = k + 1; i <= n; i++) {
            L[i][k] = A[i][k] / U[k][k]; //填充下三角矩阵
            U[k][i] = A[k][i];  //填充上三角矩阵
        }
        for (int i = k + 1; i <= n; i++) {
            for (int j = k + 1; j <= n; j++) {
                A[i][j] = A[i][j] - L[i][k] * U[k][j]; //计算舒尔补中的元素，不用除以aij 因为之前已经做过并存在L矩阵中
            }
        }
    }
    double*** ret = new double**[2];
    ret[0] = L;
    ret[1] = U;
    return ret;
}
//计算LUP分解
struct ret{
    double** L;
    double** U;
    int* pai;
    ret(double** L, double** U, int* pai){
        this->L = L;
        this->U = U;
        this->pai = pai;
    }
};
ret Lup_Decomposition(double** A, int n){
    int* pai = new int[n + 1];
    double** L = new double*[n + 1];
    double** U = new double*[n + 1];
    for (int i = 1; i <= n ; i++) {
        pai[i] = i;
    }
    for (int k = 1; k <= n; k++) {
        double p = 0;
        int k1 = 0;
        for (int i = k; i <= n; i++) {
            if(fabs(A[i][k]) > p){
                p = fabs(A[i][k]);
                k1 = i;
            }
        }
        if(p == 0){
            cout<<"该矩阵是奇异矩阵，发生错误"<<endl;
            exit(-1);
        }
        int temp = pai[k];
        pai[k] = pai[k1];
        pai[k1] = temp;
        for (int i = 1; i <= n; i++) {
            double temp = A[k][i];
            A[k][i] = A[k1][i];
            A[k1][i] = temp;
        }
        
        for (int i = k + 1; i <= n; i++) {
            A[i][k] = A[i][k] / A[k][k];
            for (int j = k + 1; j <= n; j++) {
                A[i][j] = A[i][j] - A[i][k] * A[k][j];
            }
        }
        
    }
    for (int i = 1; i <= n; i++) {
        L[i] = new double[n + 1];
        U[i] = new double[n + 1];
        for (int j = 1; j <= n; j++) {
            if(i < j){
                L[i][j] = 0;
                U[i][j] = A[i][j];
            }
            else if(i == j){
                L[i][j] = 1;
                U[i][j] = A[i][j];
            }
            else{
                L[i][j] = A[i][j];
                U[i][j] = 0;
            }
        }
    }
    ret temp(L, U, pai);
    return temp;
}
//28.2矩阵求逆
//28.3对称正定矩阵
int main(int argc, const char * argv[]) {
    ifstream in("/program/文件流/cin.txt");
    if(in.is_open()){
        int n;
        in>>n;
        double** A = new double*[n + 1];
        double** L = new double*[n + 1];
        double** U = new double*[n + 1];
        double* b = new double[n + 1];
        int* pai = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            A[i] = new double[n + 1];
            for (int j = 1; j <= n; j++) {
                in>>A[i][j];
            }
        }
        for (int i = 1; i <= n; i++) {
            in>>b[i];
        }
        ret temp = Lup_Decomposition(A, n);
        L = temp.L;
        U = temp.U;
        pai = temp.pai;
        double* x = Lup_Solve(L, U, pai, b, n);
        for (int i = 1; i <= n; i++) {
            cout<<x[i]<<endl;
        }
    }
    
    return 0;
}
