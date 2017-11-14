//
//  main.cpp
//  平摊分析
//
//  Created by 伏开宇 on 2017/3/31.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;
//动态表
class Table{
public:
    int size;
    int num;
    int* table;
    Table(){
        size = 0;
        num = 0;
    }
    void insert(int x){
        if(size == 0){
            table = new int[1];
            size = 1;
        }
        if(size == num){
            int* temp = new int[size * 2];
            for(int i = 0 ; i < size; i++){
                temp[i] = table[i];
            }
            free(table);
            table = temp;
            size = 2 * size;
        }
        table[num] = x;
        num++;
    }
    void Delete(){
        if(num > 0){
            num--;
            if(num < size/4){
                int* temp = new int[size / 2];
                for(int i = 0 ; i < num; i++){
                    temp[i] = table[i];
                }
                free(table);
                table = temp;
                size = size / 2;
            }
        }
        else{
            cout<<"表为空，删除失败"<<endl;
            exit(0);
        }
    }
};
//位反向二进制计数器 思考题17-1 O(n)时间位反向置换
int BitReservedIncreament(int x, int k){
    int mask = pow(2, k - 1);
    int limit = pow(2, k) - 1;
    int count = 0;
    while(x & mask){
        x = x<<1;
        x = x & limit;
        count++;
    }
    x = x|mask;
    while(count > 0){
        x = (unsigned int)x>>1;
        count--;
    }
    cout<<x<<" ";
    return x;
}
//二叉查找动态化 思考题17-2
class DynamicSearch{
public:
    int k;
    int n;
    int** A;
    DynamicSearch(){
        k = 1;
        n = 0;
        A = new int*[k];
    }
    int MidSearch(int*a, int x, int p, int q){
        int mid = (p + q) / 2;
        if(p <= q){
            if(a[mid] == x)
                return mid;
            else if(a[mid] < x){
                return MidSearch(a, x, mid + 1, q);
            }
            else
                return MidSearch(a, x, p, mid - 1);
        }
        else
            return INT32_MIN;
    }
    int* MergeSort(int* a, int* b, int n){
        int* c = new int[2 * n];
        int l = 0;
        int r = 0;
        for(int i = 0; i < 2 * n; i++){
            if(l < n and r < n){
                if(a[l] <= b[r]){
                    c[i] = a[l++];
                }
                else
                    c[i] = b[r++];
            }
            else if(l >= n){
                c[i] = b[r++];
            }
            else{
                c[i] = a[l++];
            }
        }
        return c;
    }
    int Search(int x){
        if(k != 0){
            int mask = 1;
            for(int i = 0 ; i < k; i++){
                int result = INT32_MIN;
                if((n & mask) != 0){
                    result = MidSearch(A[i], x, 0, pow(2, i) - 1);
                }
                if(result != INT32_MIN){
                    cout<<"寻找成功"<<endl;
                    return i;
                }
                mask *= 2;
            }
            cout<<"寻找失败"<<endl;
            return -1;
        }
        else{
            cout<<"寻找失败"<<endl;
            return -1;
        }
    }
    int replace(int x, int y){
        if(k != 0){
            int mask = 1;
            for(int i = 0 ; i < k; i++){
                int result = INT32_MIN;
                if((n & mask) != 0){
                    result = MidSearch(A[i], x, 0, pow(2, i) - 1);
                }
                if(result != INT32_MIN){
                    cout<<"寻找成功"<<endl;
                    A[i][result] = y;
                    if(A[i][result] < A[i][result - 1]){
                        for(int j = result; j > 0 and A[i][j] < A[i][j - 1]; j--){
                            int temp = A[i][j];
                            A[i][j] = A[i][j - 1];
                            A[i][j - 1] = temp;
                        }
                    }
                    else if(A[i][result] > A[i][result + 1]){
                        for(int j = result; j < pow(2, i) - 1 and A[i][j] > A[i][j + 1]; j++){
                            int temp = A[i][j];
                            A[i][j] = A[i][j + 1];
                            A[i][j + 1] = temp;
                        }
                    }
                    
                    return i;
                }
                mask *= 2;
            }
            cout<<"寻找失败"<<endl;
            return -1;
        }
        else{
            cout<<"寻找失败"<<endl;
            return -1;
        }
    }
    void insert(int x){
        int* B = new int[1];
        B[0] = x;
        int mask = 1;
        int i;
        for(i = 0; i < k; i++){
            if((n & mask) == 0){
                A[i] = B;
                break;
            }
            else{
                B = MergeSort(A[i], B, pow(2, i));
                free(A[i]);
            }
            mask *= 2;
        }
        if(i == k){
            k++;
            free(A);
            A = new int* [k];
            A[k - 1] = B;
        }
        n++;
    }
    void Delete(int x){
        if(n == 0){
            cout<<"表为空"<<endl;
            return;
        }
        int j = 0;
        int mask = 1;
        while((n & mask) == 0 and j < k){
            j++;
            mask *= 2;
        }
        
        int y = A[j][(int)pow(2, j) - 1];
        int i = replace(x, y);
        if(i < 0){
            cout<<"表中无该元素，删除失败"<<endl;
            return;
        }
        else{
            int N = 1;
            i = 0;
            for(int k = 0; k < pow(2, j) - 1; N *= 2){
                A[i] = new int[N];
                for(int l = 0 ; l < N; l++){
                    A[i][l] = A[j][k++];
                }
                i++;
            }
            free(A[j]);
        }
        
    }
};
int main(int argc, const char * argv[]) {
    DynamicSearch* d = new DynamicSearch();
    for(int i = 0; i < 100; i++){
        int k = arc4random_uniform(100);
        d->insert(k);
    }
    //d->insert(999);

    d->Delete(50);
    return 0;
}
