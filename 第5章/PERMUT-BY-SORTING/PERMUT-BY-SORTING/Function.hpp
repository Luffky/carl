//
//  Function.hpp
//  Function
//
//  Created by 伏开宇 on 2017/3/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
void InsertionSortUpper(int * num, int n);
void InsertSortLower(int * num, int n);
void SelectionSort(int * a, int n);
int BinarySearchRecurrence(int *a, int n, int p, int q);
int BinarySearchIteration(int *a, int n, int length);
void Merge(int *a, int p, int q, int r);
void Merge2(int *a, int p, int q, int r);
void MergeSort(int * a, int p, int r);


#endif /* Function_hpp */
