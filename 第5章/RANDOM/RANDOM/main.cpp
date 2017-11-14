//
//  main.cpp
//  RANDOM
//
//  Created by 伏开宇 on 2017/3/5.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;


//产生均等概率随机数 5.1-2练习
int Random(int a, int b){
    int n = b - a + 1;
    double c = log2((double) n);
    int k = ceil(c);
    int binary = 0;
    do{
        binary = 0;
        for(int i = 0; i < k; i++){
            binary += arc4random_uniform(2)*pow(2, i);
        }
    }while(binary >= n);
    
    return a + binary;
}
//以P概率输出1的随机函数 5.1-3练习
int BiasedRandom(double p, int b){
    int temp = p * b;
    int binary = 0;
    do{
        binary = 0;
        for(int i = 0; i < (int) log2(b) + 1; i++){
            binary += arc4random_uniform(2)*pow(2, i);
        }
    }while(binary >= b);
    
    if(binary >= temp)
        return 0;
    else
        return 1;
}
//5.1-3
int Rand(double p){
    int x,y;
    do{
        x = BiasedRandom(p, 1000);
        y = BiasedRandom(p, 1000);
    }while(x == y);
    
    return x;
}
//概率计数 思考题5-1
class RandomCounter{
private:
    int count;
    
public:
    RandomCounter(){
        count = 1;
    }
   void Increment(){
        int i = BiasedRandom(1.0/(double)(10 * count - 10 * (count-1)), 10000);
        count += i;
    }
    int Getcount(){
        return 10 * count;
    }
};
//随机搜索 思考题 5-2
int RandomSearch(int *a, int n, int x){
    int flag = n;
    int *b = new int [n];
    for(int i = 0; i<n; i++){
        b[i] = 0;
    }
    int i = 0;
    int j = 0;
    while(flag != 0){
        j++;
        i = arc4random_uniform(n);
        if(a[i] == x){
            cout<<j<<endl;
            return i;
        }
        else{
            if(b[i] == 0){
                b[i]++;
                flag--;
            }
        }
    }
    cout<<j<<endl;
    return -1;
}



int main(int argc, const char * argv[]) {
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    cout<<RandomSearch(a, 10, 1)<<endl;
    return 0;
}
