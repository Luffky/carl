//
//  main.cpp
//  PERMUT-BY-SORTING
//
//  Created by 伏开宇 on 2017/3/5.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <math.h>
#include <iostream>
using namespace std;


class candidate{
private:
    int number;
    int prior;
public:
    void SetNumber(int i){
        number = i;
    }
    void SetPrior(int i){
        prior = i;
    }
    int GetNumber(){
        return number;
    }
    int GetPrior(){
        return prior;
    }
    void CopyClass(candidate b){
        this->SetNumber(b.GetNumber());
        this->SetPrior(b.GetPrior());
    }
    candidate Swap(candidate a){
        candidate b;
        b.CopyClass(* this);
        this->CopyClass(a);
        return b;
    }
};



void Merge2(candidate *a, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    candidate *left = new candidate[n1];
    candidate *right = new candidate[n2];
    for(int i = 0; i<n1; i++){
        left[i].CopyClass(a[p+i]);
    }
    for(int i = 0; i<n2; i++){
        right[i].CopyClass(a[q+1+i]);
    }
    int i = 0;
    int j = 0;
    for(int k = p; k<r+1; k++){
        if(i < n1 && j < n2){
            if(left[i].GetPrior() < right[j].GetPrior()){
                a[k].CopyClass(left[i]);
                i++;
            }
            else{
                a[k].CopyClass(right[j]);
                j++;
            }
        }
        else if(i >= n1){
            a[k].CopyClass(right[j]);
            a[k] = right[j];
            j++;
        }
        else if(j >= n2){
            a[k].CopyClass(left[i]);
            i++;
        }
    }
    
    
}

//合并主程序
void MergeSort(candidate * a, int p, int r){
    if(p < r){
        int q = (p+r)/2;
        MergeSort(a, p, q);
        MergeSort(a, q+1, r);
        Merge2(a, p, q, r);
    }
    
    
}

//输入排序随机化算法
void RandomBySorting(candidate * candidate1, int n){
    
    for(int i = 0; i<n; i++){
        candidate1[i].SetPrior(arc4random_uniform(pow(n, 3)));
        candidate1[i].SetNumber(i);
        
    }
    MergeSort(candidate1, 0, n-1);
}



//输入原地随机化算法
void RandomInPlace(candidate * candidate1, int n){
    for(int i = 0; i<n; i++){
        candidate1[i].SetPrior(arc4random_uniform(pow(n, 3)));
        candidate1[i].SetNumber(i);
        
    }
    
    for(int i = 0; i<n; i++){
        int R = arc4random_uniform(n-i)+i;
        candidate1[R] = candidate1[i].Swap(candidate1[R]);
        
    }
}

int main(int argc, const char * argv[]) {
    int n = 10;
    candidate * candidate1 = new candidate [n];
    
    //RandomBySorting(candidate1, n);
    RandomInPlace(candidate1, n);
    
    for(int i = 0; i<n; i++){
        cout<<candidate1[i].GetNumber()<<" "<<candidate1[i].GetPrior()<<endl;
    }
    
    return 0;
}
