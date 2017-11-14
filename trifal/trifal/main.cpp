//
//  main.cpp
//  trifal
//
//  Created by 伏开宇 on 2017/4/7.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;
#define N 6;
#define M 3;
int total = 0;
bool isprime(int a)
{
    for(int i=2;i<=sqrt(a);i++)
        if(a%i==0) return false;
    return true;
}
void s(int x, int t, int z, int* a){
    if(x <= N){
        if(t != M){
            if(x != N)
                s(x + 1, t + 1, z + a[x], a);
        }
        else if(!isprime(z)){
            if(x != N)
                s(x + 1, t, z - a[x - 1] + a[x], a);
        }
        else{
            if(x != N)
                s(x + 1, t, z - a[x - 1] + a[x], a);
            total++;
            cout<<z<<endl;
        }
    }
}
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
