//
//  main.cpp
//  二项堆
//
//  Created by 伏开宇 on 2017/4/5.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "BinHeap.hpp"
int main(int argc, const char * argv[]) {
    int a[7] = {12,7,25,15,28,33,41};
    int b[6] = {18,3,37,6,8,9};
    BinHeap* h1 = new BinHeap();
    BinHeap* h2 = new BinHeap();
    for(int i = 0 ; i < 7; i++){
        BintreeNode* temp = new BintreeNode(a[i]);
        h1->BinHeapInsert1(temp);
    }
    for(int j = 0; j < 6; j++){
        BintreeNode* temp = new BintreeNode(b[j]);
        h2->BinHeapInsert1(temp);
    }
    h1->BinHeapUnion(h2);
    cout<<h1->BinHeapMini()->key<<endl;
    cout<<h1->BinHeapExtractMin()->key<<endl;
    h1->BinHeapDelete(h1->BinHeapMini());
    
    return 0;
}
