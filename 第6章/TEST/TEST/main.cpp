//
//  main.cpp
//  TEST
//
//  Created by 伏开宇 on 2017/3/7.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
using namespace std;
#define BUFFER_SIZE 10
//堆调整
void MaxHeapIfy(int *a,int i,int heapSize,int d)
{
    int largest=0;
    int tmp=0;
    int j=0;
    int child=0;
    int b[d+1];
    for(j=1;j<=d;j++)
    {
        b[j]=d*(i-1)+j+1;//计算d叉堆节点i的每个子女j的索引
    }
    largest=i;
    for(j=1;j<=d;j++)
    {
        child=b[j];
        if(child<=heapSize&&a[largest]<a[child])
        {
            largest=child;
        }
    }
    if(largest!=i)
    {
        tmp=a[i];
        a[i]=a[largest];
        a[largest]=tmp;
        
        MaxHeapIfy(a,largest,heapSize,d);
    }
}

//去掉并返回堆顶元素
int HeapExtractMax(int *a,int *heapSize,int d)
{
    int tmp=a[1];
    a[1]=a[*heapSize];
    (*heapSize)--;
    MaxHeapIfy(a,1,*heapSize,d);
    return tmp;
}

//将最大堆指定元素x的关键字增大到k，k要大于x原关键字
void HeapIncreaseKey(int *a,int x,int k,int d)
{
    int tmp=0;
    if(k<=a[x])
    {
        return;
    }
    a[x]=k;
    while(x>1&&a[x]>a[(x-2)/d+1])
    {
        tmp=a[x];
        a[x]=a[(x-2)/d+1];
        a[(x-2)/d+1]=tmp;
        x=(x-2)/d+1;
    }
}
//插入元素到最大堆
void MaxHeapInsert(int *a,int k,int *heapSize,int d)
{
    int tmp=k-1;
    (*heapSize)++;
    a[*heapSize]=tmp;
    HeapIncreaseKey(a,*heapSize,k,d);
}

//插入法建堆
void BuildMaxHeap(int *b,int len,int *a,int *heapSize,int d)
{
    int i=0;
    for(i=0;i<len;i++)
    {
        MaxHeapInsert(a,b[i],heapSize,d);
    }
}
int main()
{
    int i=0;
    int j=0;
    int heapSize=0;
    int d=3;
    int a[BUFFER_SIZE+1];
    int b[BUFFER_SIZE];
    for(i=0;i<BUFFER_SIZE;i++)
    {
        b[i]=arc4random_uniform(BUFFER_SIZE);
    }
    printf("随机生成的链表：\n");
    for(i=0;i<BUFFER_SIZE;i++)
    {
        printf("%d ",b[i]);
    }
    
    printf("\n插入法建堆：\n"); 
    BuildMaxHeap(b,BUFFER_SIZE,a,&heapSize,d);
    for(i=1;i<=heapSize;i++)
    {
        printf("%d ",a[i]);
    }
    
    printf("\n去掉并返回堆顶元素：\n");
    HeapExtractMax(a,&heapSize,d);
    for(i=1;i<=heapSize;i++)
    {
        printf("%d ",a[i]);
    }
    cout<<endl;
    //system("pause");
    return 0;
} 
