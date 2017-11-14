//
//  main.cpp
//  Exercise3(思考题8-2）
//
//  Created by 伏开宇 on 2017/3/9.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;


//思考题8-2 （4）
void CountringSort(int *a, int *b, int n, int k, int dig){
    int *c = new int[k];
    c[0] = -1;
    for(int i = 1; i < k; i++){
        c[i] = 0;
    }
    int Dev = 1;
    for(int i = 0; i < dig; i++){
        Dev *= 10;
    }
    for (int i = 0; i < n; i++){
        c[a[i] % (10 * Dev) / Dev]++;
    }
    for (int i = 1; i < k; i++){
        c[i] += c[i-1];
    }
    for (int i = n - 1; i > 0; i--){
        b[c[a[i] % (10 * Dev) / Dev]--] = a[i];
    }
    for (int i = 0; i < n; i++){
        a[i] = b[i];
    }
}

void RadixSort(int *a, int *b, int n, int k, int d){
    for(int i = 0; i < d; i++){
        CountringSort(a, b, n, k, i);
    }
}



//思考题8-2 （2）

void Partition(int * a, int p, int r){
    int key = a[r];
    
    int i = p - 1;
    for(int j = p; j < r; j++){
        if (a[j] == key) {
            i++;
            int temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
    
    a[r] = a[i+1];
    a[i+1] = key;
}

//思考题8-3 (3)
void BubbleSort(int *a, int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = n - 1; j > i; j--){
            if(a[j] < a[j-1]){
                int temp = a[j];
                a[j] = a[j-1];
                a[j-1] = temp;
            }
        }
    }
}

//思考题8-3 （5）
void CountringSort1(int *a,int n, int k){
    int *c = new int[k];
    int *d = new int[k];
    c[0] = -1;
    for(int i = 1; i < k; i++){
        c[i] = 0;
    }
    for (int i = 0; i < n; i++){
        c[a[i]]++;
    }
    for (int i = 1; i < k; i++){
        c[i] += c[i-1];
    }
    
    for (int i = 0; i < k; i++){
        d[i] = c[i];
    }
    
    for (int i = n - 1; i > 0;){
        //cout<<c[a[i]]<<" "<<a[c[a[i]]]<<" "<<i<<" "<<a[i]<<" "<<d[a[i]]<<endl;
        if (d[a[i] - 1] < i and i <= d[a[i]] and a[i] != 0) {
            i--;
        }
        else if(a[i] == 0 and i <= d[a[i]]){
            i--;
        }
        else{
            
            
            int temp = a[c[a[i]]];
            a[c[a[i]]--] = a[i];
            a[i] = temp;
        }
    }
}

//思考题8.3
void CountringSort2(int *a, int *b, int n, int k){
    int *c = new int[k];
    int *d = new int[k];
    c[0] = -1;
    for(int i = 1; i < k; i++){
        c[i] = 0;
    }
    for (int i = 0; i < n; i++){
        c[a[i]]++;
    }
    for (int i = 1; i < k; i++){
        c[i] += c[i-1];
    }
    
    for (int i = 0; i < k; i++){
        d[i] = c[i];
    }
    
    for (int i = n - 1; i > 0;){
        if (d[a[i] - 1] < i and i <= d[a[i]] and a[i] != 0) {
            i--;
        }
        else if(a[i] == 0 and i <= d[a[i]]){
            i--;
        }
        else{
            int temp = a[c[a[i]]];
            int temp1 = b[c[a[i]]];
            a[c[a[i]]] = a[i];
            b[c[a[i]] --] = b[i];
            a[i] = temp;
            b[i] = temp1;
            
        }
    }
}

void CountringSort2(int *a, int * b,int k, int p, int q, int digit){
    int *c = new int[k];
    c[0] = -1;
    for(int i = 1; i < k; i++){
        c[i] = 0;
    }
    int Dev = 1;
    for(int i = 0; i < digit; i++){
        Dev *= 10;
    }
    for (int i = p; i <= q; i++){
        c[a[i] % (10 * Dev) / Dev]++;
    }
    for (int i = 1; i < k; i++){
        c[i] += c[i-1];
    }
    for (int i = q; i >= p; i--){
        b[c[a[i] % (10 * Dev) / Dev]--] = a[i];
    }
    for (int i = 0; i <= q - p; i++){
        a[p + i] = b[i];
    }
    
    for(int i = 0; i < 100; i ++){
        cout<<a[i]<<" ";
    }
    
}


void RadixSort2(int *a, int k, int d, int p, int q){
    int * b = new int[q - p + 1];
    for(int i = 0; i < d; i++){
        CountringSort2(a, b, k, p, q, i);
        cout<<endl;
    }
}

void NDigitSort(int * a, int n, int m){
    int *b = new int[m]; //每个整数对应的位数
    for(int i = 0; i < m; i++){
        int temp = a[i];
        int digit = 0;
        while (temp) {
            temp /= 10;
            digit++;
        }
        b[i] = digit;
    }
    
//    for(int i = 0; i < 100; i++){
//        cout<<b[i]<<" ";
//    }
//    cout<<endl;
    
    CountringSort2(b, a, m, n + 1);
    
    for(int i = 0; i < 100; i++){
        cout<<a[i]<<" "<<b[i]<<" ";
    }
    cout<<endl;
    
    int j = b[0];
    int k = 0;
    for(int i = 0; i < m;){
        while(b[i + 1] == j)
            i++;
        RadixSort2(a, 10, b[i], k, i);
        
        i++;
        j = b[i];
        k = i;
        
    }
    
}


//思考题 8-3 (2)
void CountingSort3(string *a, string *b, int n, int m){
    int *c = new int[n];
    c[0] = -1;
    for (int i = 1; i < n; i++) {
        c[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        c[a[i].length()]++;
    }
    for (int i = 1; i < n; i++) {
        c[i] += c[i-1];
    }
    for (int i = m - 1; i >= 0; i--) {
        b[c[a[i].length()]-- ] = a[i];
    }
    
    
}

void CountingSort3(string *a,int n, int p, int q, long int digit){
    int *c = new int[n];
    string *b = new string[q - p + 1];
    c[0] = -1;
    for (int i = 1; i < n; i++) {
        c[i] = 0;
    }
    for (int i = p; i <= q; i++) {
        c[a[i][digit - 1] - 97]++;
       //cout<<a[i][digit - 1] - 97<<endl;
        
    }
    for (int i = 1; i < n; i++) {
        c[i] += c[i-1];
    }
    for (int i = q; i >= p; i--) {
        b[c[a[i][digit - 1] - 97 ]].assign(a[i]);
        c[a[i][digit - 1] - 97 ] --;
//        cout<<a[i][digit - 1] - 97<<endl;
//        cout<<c[a[i][digit - 1] - 97] + 1 + p<<endl;
        
    }
    for (int i = q - p; i >= 0; i--) {
        a[p + i].assign(b[i]);
    }
    
    free(c);
    
}

void ViewPoint(string *a, int n){
    for(int i = 0; i < n; i++){
        cout<<a[i]<<a[i].length()<<" ";
    }
    cout<<endl;
}

void NDigitStringSort(string *a, string *b, int n, int m){
    CountingSort3(a, b, n, m);
//    for(int i = 0; i < m; i++){
//        cout<<b[i]<<" ";
//    }
//    cout<<endl;
//    cout<<endl;
    
    long int length = b[m - 1].length();
    int temp = m - 1;
    for(int i = m - 1; i >= 0;){
        while (b[i - 1].length() == length) {
            i--;
        }
        CountingSort3(b, 27, i, temp, length);
        
        //ViewPoint(b, 20);
        cout<<endl;
        i--;
        length = b[i].length();
    }
    
    
    
    
    
}



int main(int argc, const char * argv[]) {
    int m = 20;
    string * a = new string[m];
    string * b = new string[m];
    int n = 0;
    for(int i = 0; i < m; i++){
        int length = arc4random_uniform(20) + 1;
        n += length;
        for(int j = 0; j < length; j++){
            char temp = arc4random_uniform(26)+97;
            //cout<<temp;
            a[i] += temp;
        }
        
    }
    
    //ViewPoint(a, 20);
    NDigitStringSort(a,b,n,m);
    
    for(int i = 0; i < m; i++){
        cout<<b[i]<<" ";
    }
    cout<<endl;
    return 0;
}
