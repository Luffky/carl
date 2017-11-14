//
//  main.cpp
//  DYNAMICPROGRAMMING
//
//  Created by 伏开宇 on 2017/3/22.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
#define INF 99999999
/******************************************************************/
//装配线调度问题 15.1
//递减打印选择站
void PrintStationsLo(int** l, int lend, int n){
    int i = lend;
    cout<<i + 1<<" "<<n<<endl;
    for(int j = n - 1; j >= 1; j--){
        i = l[i][j];
        cout<<i + 1<<" "<<j<<endl;
   }
}
//递增顺序打印装配站(递归) 15.1-1练习
void PrintStationsUp(int** l, int n, int i, int j){
    if(j > 1){
        PrintStationsUp(l, n, l[i][j - 1], j - 1);
        cout<<i + 1<<" "<<j<<endl;
    }
    else
        cout<<i + 1<<" "<<j<<endl;
}
void FastestWay(int a[][6], int t[][5], int *e, int *x, int n){
    int** f = new int*[2]; //每一个装配站的最小到达时间,只使用四个项纪录，15.1-4练习
    int** l = new int*[2]; //每一个装配站的选择
    int fend = 0; //最终最小到达时间
    int lend = 0; //最后一个装配站的选择
    f[0] = new int[2];
    f[1] = new int[2];
    l[0] = new int[n];
    l[1] = new int[n];
    f[0][0] = e[0] + a[0][0];
    f[1][0] = e[1] + a[1][0];
    for(int i = 1; i < n; i++){
        f[0][1] = min(f[0][0] + a[0][i], f[1][0] + t[1][i - 1] + a[0][i]);
        l[0][i] = f[0][0] + a[0][i] <= f[1][0] + t[1][i - 1] + a[0][i] ? 0 : 1;
        f[1][1] = min(f[1][0] + a[1][i], f[0][0] + t[0][i - 1] + a[1][i]);
        l[1][i] = f[1][0] + a[1][i] <= f[0][0] + t[0][i - 1] + a[1][i] ? 1 : 0;
        f[0][0] = f[0][1];
        f[1][0] = f[1][1];
    }
    fend = min(f[0][0] + x[0], f[1][0] + x[1]);
    lend = f[0][0] + x[0] <= f[1][0] + x[1] ? 0 : 1;
    cout<<fend<<endl;
    PrintStationsUp(l, n, lend, n);
}
/******************************************************************/
//矩阵链乘法 15.2
class Matrix{
public:
    int rows;
    int columns;
    int** a;
    Matrix(int r, int c){
        a = new int*[r];
        for(int i = 0 ; i < r; i++){
            a[i] = new int[c];
        }
        
        rows = r;
        columns = c;
    }
};
Matrix* MatrixMultiply(Matrix* a, Matrix* b){
    Matrix* c = new Matrix(a->rows, b->columns);
    if(a->columns != b->rows){
        cout<<"行列不相同，无法相乘"<<endl;
        exit(0);
    }
    else{
        for(int i = 0 ; i < a->rows; i++){
            for(int j = 0 ; j < b->columns; j++){
                c->a[i][j] = 0;
                for(int k = 0 ; k < a->columns; k++)
                    c->a[i][j] += (a->a[i][k] + b->a[k][j]);
            }
        }
    }
    return c;
}
void PrintOptimalParens(int** s, int i, int j){
    if(i == j)
        cout<<"A"<<i + 1;
    else{
        cout<<"(";
        PrintOptimalParens(s, i, s[i][j]);
        PrintOptimalParens(s, s[i][j] + 1, j);
        cout<<")";
    }
}
//使用链乘法计算矩阵 15.2-2练习
Matrix* MatrixChainMultiply(Matrix** A, int** s, int i, int j){
    if(i == j){
        return A[i];
    }
    else if(j == i + 1){
        return MatrixMultiply(A[i], A[j]);
    }
    else{
        return MatrixMultiply(MatrixChainMultiply(A, s, i, s[i][j]), MatrixChainMultiply(A, s, s[i][j] + 1, j));
    }
}
void MatrixChainOrder(int *p, int**s, int n){
    int** m = new int*[n];
    for(int i = 0 ; i < n; i++){
        m[i] = new int[n];
        m[i][i] = 0;
    }
    for(int i = 1; i < n; i++){  //矩阵链长度从1到n - 1;
        for(int j = 0; j < n - i; j++){ //对于每个满足要求的首矩阵项
            int r = j + i; //该矩阵链的最后一个矩阵编号
            m[j][r] = INF;
            int temp = 0;
            for(int k = j; k < r; k++){ //k可以取得j<=k<r;
                temp = m[j][k] + m[k + 1][r] + p[j] * p[k + 1] * p[r + 1]; //计算当前取法的乘积次数
                if(temp < m[j][r]){ //与原次数进行比较
                    m[j][r] = temp;
                    s[j][r] = k;
                }
            }
        }
    }
    for(int i = 0 ; i < n; i ++ ){
        for(int k = 0 ; k < i; k++)
            cout<<"   ";
        for(int j = i; j < n; j++){
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    //PrintOptimalParens(s, 0, 5);
}
//备忘录版本（由顶向下）
int LookupChain(int* p, int i, int j, int** m){
    if(m[i][j] < INF)
        return m[i][j];
    else if(i == j)
        m[i][j] = 0;
    else{
        for(int k = i; k < j; k++){
            int q = LookupChain(p, i, k, m) + LookupChain(p, k + 1, j, m) + p[i] * p[k + 1] * p[j + 1];
            if(q < m[i][j])
                m[i][j] = q;
        }
    }
    return m[i][j];
}
int MemoizedMatrixChain(int* p, int n){
    int **m = new int*[n];
    for(int i = 0 ; i < n; i++){
        m[i] = new int[n];
        for(int j = 0 ; j < n; j++){
            m[i][j] = INF;
        }
    }
    return LookupChain(p, 0, n - 1, m);
}
/******************************************************************/
//最长公共子序列 15.4
void PrintLcs(int** b, string x, int i, int j){
    if(i == 0 or j == 0)
        return;
    else if(b[i][j] == 1){
        PrintLcs(b, x, i - 1, j - 1);
        cout<<x[i - 1]<<" ";
    }
    else if(b[i][j] == 0){
        PrintLcs(b, x, i - 1, j);
    }
    else{
        PrintLcs(b, x, i, j - 1);
    }
}
//不使用b数组记录每次的选择，打印Lcs 15.4-2练习
void PrintLcsWithoutB(int** c, string x, string y, int i, int j){
    if(i == 0 or j ==0)
        return;
    else {
        int temp = c[i][j];
        int temp1 = c[i - 1][j];
        if(x[i - 1] == y[j - 1]){
            PrintLcsWithoutB(c, x, y, i - 1, j - 1);
            cout<<x[i - 1]<<" ";
        }
        else if(temp == temp1){
            PrintLcsWithoutB(c, x, y, i - 1, j);
        }
        else{
            PrintLcsWithoutB(c, x, y, i, j - 1);
        }
    }
}
void LCS(string x, string y){
    int m = (int) x.length() + 1;
    int n = (int) y.length() + 1;
    int** c = new int*[m];
    int** b = new int*[m];
    for(int i = 0; i < m; i++){
        c[i] = new int[n];
        b[i] = new int[n];
        c[i][0] = 0;
    }
    for(int j = 0 ; j < n; j++){
        c[0][j] = 0;
    }
    for(int i = 1 ; i < m; i++){
        for(int j  = 1; j < n; j++){
            if(x[i - 1] == y[j - 1]){
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else if(c[i - 1][j] >= c[i][j - 1]){
                c[i][j] = c[i - 1][j];
                b[i][j] = 0;
            }
            else{
                c[i][j] = c[i][j - 1];
                b[i][j] = 2;
            }
        }
    }
    //PrintLcs(b, x, m - 1, n - 1);
    PrintLcsWithoutB(c, x, y, m - 1, n - 1);
}
//LCS备忘录版本 15.4-3
int LCSLookUp(int** c, string x, string y, int i, int j){
    if(c[i][j] > -1){
        return c[i][j];
    }
    if(x[i - 1] == y[j - 1])
        c[i][j] = LCSLookUp(c, x, y, i - 1, j - 1) + 1;
    else
        c[i][j] = max(LCSLookUp(c, x, y, i - 1, j), LCSLookUp(c, x, y, i, j - 1));
    return c[i][j];
}
void MomoizedLCS(string x, string y){
    int m = (int) x.length() + 1;
    int n = (int) y.length() + 1;
    int** c = new int*[m];
    for(int i = 0 ; i < m; i ++){
        c[i] = new int[n];
        for(int j = 0; j < n; j++){
            if(i == 0 or j == 0)
                c[i][j] = 0;
            else
                c[i][j] = -1;
        }
    }
    cout<<LCSLookUp(c, x, y, m - 1, n - 1)<<endl;
}
//LCS使用min(m, n) + O(1)空间计算LCS长度 练习15.4-4
void LCSOmn(string x, string y){
    int m = (int) x.length() + 1;
    int n = (int) y.length() + 1;
    int l = min(m, n) - 1;
    int k = max(m, n) - 1;
    int* c = new int[l];
    for(int i = 0 ; i < l; i++){
        c[i] = 0;
    }
    int temp = 0;
    for(int i = 1 ; i < k + 1; i++){
        for(int j = 1 ; j < l + 1; j++){
            if(j == 1){
                if(x[i - 1] == y[j - 1]){
                    temp = c[j - 1];
                    c[j - 1] = 1;
                }
                else
                    temp = c[j - 1];
            }
            else{
                if(x[i - 1] == y[j - 1]){
                    temp = c[j - 1];
                    c[j - 1] = temp + 1;
                }
                else{
                    temp = c[j - 1];
                    c[j - 1] = max(c[j - 2], c[j - 1]);
                }
            }
        }
    }
    cout<<c[l - 1]<<endl;
}
void Merge(int* a, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    int* left = new int[n1 + 1];
    int* right = new int[n2 + 1];
    for(int i = 0; i < n1; i++){
        left[i] = a[p + i];
    }
    for(int i = 0 ; i < n2; i++){
        right[i] = a[q + i + 1];
    }
    left[n1] = INT32_MAX;
    right[n2] = INT32_MAX;
    int L = 0;
    int R = 0;
    for(int i = p; i <= r; i++){
        if(left[L] <= right[R])
            a[i] = left[L++];
        else
            a[i] = right[R++];
    }
}
void MergeSort(int* a, int p, int r){
    if(p < r){
        int q = (p + r) / 2;
        MergeSort(a, p, q);
        MergeSort(a, q + 1, r);
        Merge(a, p , q, r);
    }
}
//输出最长单调子序列 15.4-5练习
void PrintLonest(int** b, int* a, int i, int j){
    if(i == 0 or j == 0)
        return;
    else if(b[i][j] == 1){
        PrintLonest(b, a, i - 1, j - 1);
        cout<<a[i - 1]<<" ";
    }
    else if(b[i][j] == 0)
        PrintLonest(b, a, i - 1, j);
    else
        PrintLonest(b, a, i, j - 1);
}
//寻找最长单调递增子序列O(n^2) 先将其排序，然后将排序后的数组与原数组查找最长公共子序列，即得到最长单调递增子序列
void Longest(int* a, int n){
    int* a1 = new int[n];
    for(int i = 0 ; i < n; i++)
        a1[i] = a[i];
    MergeSort(a1, 0, n - 1);
    int** c = new int*[n + 1];
    int** b = new int*[n + 1];
    for(int i = 0; i <= n; i++){
        c[i] = new int[n];
        b[i] = new int[n];
        c[i][0] = 0;
        c[0][i] = 0;
        b[i][0] = 0;
        b[0][i] = 0;
    }
    for(int i = 1 ; i < n + 1; i++){
        for(int j = 1 ; j < n + 1; j++){
            if(a[i - 1] == a1[j - 1]){
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else if(c[i - 1][j] >= c[i][j - 1]){
                c[i][j] = c[i - 1][j];
                b[i][j] = 0;
            }
            else{
                c[i][j] = c[i][j - 1];
                b[i][j] = 2;
            }
        }
    }

    PrintLonest(b, a, n, n);
    cout<<endl;
}
//寻找最长单调递增子序列O(nlgn)从左向右遍历序列，用lmax[i]记录长度为i的单调序列的最小尾数，用二分法查找lmax数组进行该数组的维护 15.4-6练习
int binarySrh( int *s, int len, int x )
{
    int left = 0,right = len-1, mid = (left+right)/2;
    while( left<=right )
    {
        if( x>s[mid] )	left = mid+1;
            else if( x<s[mid] ) right = mid-1;
                else return mid;
        mid = (left+right)/2;
    }
    return left;
}
void longestNlgn(int* a, int n){
    int* maxl = new int[n];
    int* mem = new int[n]; //最后用来打印该最长单调序列
    int len = 0;
    for(int i = 0 ; i < n ; i++){
        int j = binarySrh(maxl, len, a[i]);
        maxl[j] = a[i];
        mem[i] = j;
        if(++j > len)
            len = j;
    }
    cout<<"最长单调递增子序列长度为"<<len<<endl;
    len--;
    for(int i = n - 1; i >= 0 and len >= 0; i--){
        if(mem[i] == len){
            cout<<a[i]<<" ";
            len--;
        }
    }
}
/******************************************************************/
//最优二叉查找树 15.5
void ConstructOptimalBst(int** root, int i, int j, int p){
    if(i > j){
        if(j < p)
            cout<<"d"<<j<<"是k"<<p<<"的左子树"<<endl;
        else
            cout<<"d"<<j<<"是k"<<p<<"的右子树"<<endl;
    }
    else{
        if(p == -1)
            cout<<"k"<<root[i][j]<<"是根"<<endl;
        else{
            if(i < p)
                cout<<"k"<<root[i][j]<<"是k"<<p<<"的左子树"<<endl;
            else
                cout<<"k"<<root[i][j]<<"是k"<<p<<"的右子树"<<endl;
        }
        ConstructOptimalBst(root, i, root[i][j] - 1, root[i][j]);
        ConstructOptimalBst(root, root[i][j] + 1, j, root[i][j]);
    }
}
void OptimalBst(int* p, int* q, int n){
    int** e = new int*[n + 2]; //e[i][j] 包含ki - kj关键字的最优二叉查找树的期望代价
    int** w = new int*[n + 2]; //w[i][j] 包含ki - kj关键字的概率总和
    int** root = new int*[n + 2];
    for(int i = 1 ; i < n + 2; i++){
        e[i] = new int[n + 1];
        w[i] = new int[n + 1];
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
        root[i] = new int[n + 1];
    }
    
    for(int i = 1; i <= n; i++){ //最优二叉树当前节点数
        for(int j = 1; j <= n - i + 1; j++){ //从kj开始到k(j+i-1)的子树
            e[j][j + i - 1] = INF;
            w[j][j + i - 1] =  w[j][j + i - 2] + p[j + i - 1] + q[j + i - 1];
            //for(int k = j; k <= j + i - 1; k++){ //下式替换掉之后，以O(n^2)运行
            if(i == 1){
                int k = j;
                int t = e[j][k - 1] + e[k + 1][j + i - 1] + w[j][j + i - 1];
                if(t < e[j][j + i - 1]){
                    e[j][j + i - 1] = min(e[j][j + i -1], t);
                    root[j][j + i - 1] = k;
                }
            }
            else{
                for(int k = root[j][j + i - 2]; k <= root[j + 1][j + i - 1]; k++){
                    int t = e[j][k - 1] + e[k + 1][j + i - 1] + w[j][j + i - 1];
                    if(t < e[j][j + i - 1]){
                        e[j][j + i - 1] = t;
                        root[j][j + i - 1] = k;
                    }
                }
            }
        }
    }
    ConstructOptimalBst(root, 1, n, -1);
}
//最有二叉树备忘录版
int LookUpOptimal(int* p, int* q, int** e, int** w, int** root, int i, int j){
    if(e[i][j] < INF)
        return e[i][j];
    else{
        for(int k = i; k <= j; k++){
            int temp = LookUpOptimal(p, q, e, w, root, i, k - 1) + LookUpOptimal(p, q, e, w, root, k + 1, j) + w[i][j];
            if(e[i][j] > temp){
                e[i][j] = temp;
                root[i][j] = k;
            }
        }
        return e[i][j];
    }
}
void MomoizedOptimal(int* p, int* q, int n){
    int** e = new int*[n + 2]; //e[i][j] 包含ki - kj关键字的最优二叉查找树的期望代价
    int** w = new int*[n + 2]; //w[i][j] 包含ki - kj关键字的概率总和
    int** root = new int*[n + 2];
    for(int i = 1 ; i < n + 2; i++){
        e[i] = new int[n + 1];
        w[i] = new int[n + 1];
        root[i] = new int[n + 1];
        for(int j = 0; j < n + 1; j++){
            e[i][j] = INF;
            w[i][j] = INF;
        }
    }
    for(int i = 1; i < n + 2; i++){
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
        for(int j = i; j < n + 1; j++){
            w[i][j] = w[i][j - 1] + p[j] + q[j];
        }
    }
    LookUpOptimal(p, q, e, w, root, 1, n);
    ConstructOptimalBst(root, 1, n, -1);
}
/******************************************************************/
int main(int argc, const char * argv[]) {
    int p[8] ={0,4,6,8,2,10,12,14};
    int q[8] ={6,6,6,6,5,5,5,5,};
    OptimalBst(p, q, 7);
    MomoizedOptimal(p, q, 7);
    return 0;
}
