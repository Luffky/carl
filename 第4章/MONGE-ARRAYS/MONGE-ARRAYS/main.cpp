//
//  main.cpp
//  MONGE-ARRAYS
//
//  Created by 伏开宇 on 2017/3/4.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include<time.h>
using namespace std;

class Array{
public:
    int m;
    int n;
    int step;
    int *data;
};

int get(Array A, int i, int j) {
    return A.data[((i + 1) * A.step - 1) * A.n + j];
}

Array half(Array a) {
    Array result = { a.m, a.n, a.step * 2, a.data };
    return result;
}

int height(Array array) {
    return array.m / array.step;
}

int min_index(Array A, int row, int left, int right) {
    int min = left;
    
    for (int i = left; i < right; i++) {
        if (get(A, row, i) < get(A, row, min)) {
            min = i;
        }
    }
    
    return min;
}

void find_minimums(Array A, int *mins) {
    if (height(A) == 1) {
        mins[0] = min_index(A, 0, 0, A.n);
    }
    else {
        Array evens = half(A);
        int even_minimums[height(evens)];
        
        find_minimums(evens, even_minimums);
        
        int leftmost = 0;
        
        for (int i = 0; i < height(evens); i++) {
            leftmost = min_index(A, 2 * i, mins[2 * i - 1], even_minimums[i] + 1);
            
            mins[2 * i]     = leftmost;
            mins[2 * i + 1] = even_minimums[i];
        }
        
        if (height(A) % 2) {
            mins[height(A) - 1] = min_index(A, height(A) - 1, mins[height(A) - 2], A.n);
        }
    }
}

int main(int argc, const char * argv[]) {
    int n = 1000000;
    double Totaltime = 0;
    while(n>0){
        clock_t start,finish;
        double totaltime;
        start=clock();
        
        int data[20] =
                       {37,23,24,32,
                        21,6,7,10,
                        53,34,30,31,
                        32,13,9,6,
                        43,21,15,8};
        Array a ={5,4,1,data};
        int min[5];
        find_minimums(a, min);
//        for(int i = 0; i<5; i++){
//            cout<<min[i]+1<<" ";
//        }
//        cout<<endl;
        
        finish=clock();
        totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
        Totaltime = Totaltime + totaltime;
        n--;
    }
    cout<<Totaltime<<endl;
    return 0;
}
