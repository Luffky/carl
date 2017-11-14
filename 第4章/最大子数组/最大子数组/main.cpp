//
//  main.cpp
//  最大子数组
//
//  Created by 伏开宇 on 2017/6/25.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//动态规划最大子数组
int maxSum(int* array, int length){
    int maxAll =  0;
    int maxTail = 0;
    for (int i = 0;  i < length; i++) {
        maxTail = max(array[i], maxTail + array[i]);
        maxAll = max(maxAll, maxTail);
    }
    return maxAll;
}
int main(int argc, const char * argv[]) {
    
    return 0;
}
