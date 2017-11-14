//
//  HEAPSORT.cpp
//  PRIORITY-QUEUE
//
//  Created by 伏开宇 on 2017/3/6.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
#include "HEAPSORT.hpp"
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)

#define DPARENT(i,d) ((i - 1) / d)
#define CHILD(i,c,d) (d * i + c + 1)

#define INFIT 9999999
using namespace std;

//堆排序 第六章
//D叉堆
void DxHeap::MaxHeapify(int i){
    int largest = i ;
    for(int j = 0; j<GetD(); j++){
        int child = CHILD(i, j, GetD());
        if(child < GetHeapSize() and GetNum(largest) < GetNum(child)){
            largest = child;
        }
    }
    
    if(largest != i){
        Swap(i, largest);
        MaxHeapify(largest);
    }
}

void DxHeap::BuildMaxHeap(){
    for(int i = (GetHeapSize()-1)/d+1; i>=0; i--){
        MaxHeapify(i);
    }
}

Type DxHeap::ExtractMax(){
    if(GetHeapSize()<1)
        exit(0);
    
    else{
        Type temp = array[0];
        array[0] = array[GetHeapSize()-1];
        SelfSubtractHeapSize();
        MaxHeapify(0);
        return temp;
    }
   
}

void DxHeap::IncreaseKey(int i, int key){
    if(key <= array[i].GetNum())
        cout<<"新增关键字小于原关键字，增加失败"<<endl;
    else{
        array[i].SetNum(key);
        for (int j = i; j>0 ; ) {
            int k = DPARENT(j,d);
            if(array[j].GetNum() > array[k].GetNum()){
                Swap(j, k);
                j = k;
            }
            else
                break;
        }
    }
}

void DxHeap::MaxHeapInsert(Type a){
    if(GetHeapSize() == GetLength()){
        cout<<"堆已满，无法插入新元素"<<endl;
    }
    else{
        SelfPlusHeapSize();
        array[GetHeapSize()-1] = a;
        array[GetHeapSize()-1].SetNum(-1);
        IncreaseKey(GetHeapSize()-1, a.GetNum());
    }
}


//////////////////////////////////
//维持最大堆的性质 递归
void Heap::MaxHeapify(int i){
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = 0;
    if(l < this->GetHeapSize() and this->GetNum(l) > this->GetNum(i))
        largest = l;
    else
        largest = i;
    if(r < this->GetHeapSize() and this->GetNum(r) > this->GetNum(largest))
        largest = r;
    if(largest != i){
        this->Swap(i, largest);
        MaxHeapify(largest);
    }
}
//维持最大堆的性质 迭代
void Heap::MaxHeapify1(int i){
    int largest = i;
    do{
        i= largest;
        int l = LEFT(i);
        int r = RIGHT(i);
        if(l <= this->GetHeapSize() and this->GetNum(l) > this->GetNum(i))
            largest = l;
        else
            largest = i;
        if(r <= this->GetHeapSize() and this->GetNum(r) > this->GetNum(largest))
            largest = r;
        if(largest != i){
            this->Swap(i, largest);
        }
    }while(largest != i);
}
//建堆
void Heap::BuildMaxHeap(){
    
    for (int i = this->GetHeapSize()/2 - 1; i >= 0; i--) {
        this->MaxHeapify(i);
        
    }
}

//堆排序

void Heap::HeapSort(){
    BuildMaxHeap();
    for (int i = this->GetHeapSize() - 1; i > 0; i--) {
        this->Swap(i, 0);
        this->SetHeapSize(this->GetHeapSize()-1);
        MaxHeapify(0);
    }
}
//返回最大关键字元素
Type Heap::HeapMaximum(){
    return array[0];
}

//退出最大关键字元素
Type Heap::ExtractMax(){
    if(GetHeapSize()<1)
        exit(0);
    else{
        Type temp = array[0];
        array[0] = array[GetHeapSize()-1];
        SelfSubtractHeapSize();
        MaxHeapify1(0);
        return temp;
    }
}

//增大指定元素关键字
void Heap::IncreaseKey(int i, int key){
    if(key <= array[i].GetNum())
        cout<<"新增关键字小于原关键字，增加失败"<<endl;
    else{
        array[i].SetNum(key);
        for (int j = i; j>0 ; ) {
            int k = PARENT(j);
            if(array[j].GetNum() > array[k].GetNum()){
                Swap(j, k);
                j = k;
            }
            else
                break;
        }
    }
}
//插入新元素
void Heap::MaxHeapInsert(Type a){
    if(GetHeapSize() == GetLength()){
        cout<<"堆已满，无法插入新元素"<<endl;
    }
    else{
        SelfPlusHeapSize();
        array[GetHeapSize()-1] = a;
        array[GetHeapSize()-1].SetNum(-1);
        IncreaseKey(GetHeapSize()-1, a.GetNum());
    }
}
//删除元素 6.5-7练习
void Heap::HeapDelete(int i){
    IncreaseKey(i, INFIT);
    ExtractMax();
}


//先进先出队列插入 6.5-6练习
void Heap::Insert(Type a){
    if(GetHeapSize() >= GetLength()){
        exit(0);
    }
    else{
        a.SetNum(GetLength() - GetHeapSize());
        MaxHeapInsert(a);
    }
}
//出队列 6.5-6练习
Type Heap::Delete(){
    Type temp = ExtractMax();
    for(int i = 0; i < GetHeapSize()-1; i++){
        IncreaseKey(i, array[i].GetNum()+1);
    }
    return temp;
}



