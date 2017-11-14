//
//  HEAPSORT.hpp
//  PRIORITY-QUEUE
//
//  Created by 伏开宇 on 2017/3/6.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef HEAPSORT_hpp
#define HEAPSORT_hpp
#define null -9999999;
#include <stdio.h>
//堆数据结构
class Type{
private:
    int num; //按需改变类型
    int data;
public:
    Type(){
        //data = i;
        num = null;
    }
    int GetData(){
        return data;
    }
    void SetData(int a){
        data = a;
    }
    int GetNum(){
        return num;
    }
    void SetNum(int a){
        num = a;
    }
    Type Copy(){
        return *this;
    }
};
//d叉堆 思考题6-2
class DxHeap{
private:
    Type * array;
    int length;
    int heap_size;
    int d;
public:
    DxHeap(Type * a, int b, int c, int d){
        array = a;
        length = b;
        heap_size = c;
        this->d = d;
    }
    int GetNum(int i){
        return array[i].GetNum();
    }
    void SetNum(int i, int a){
        array[i].SetNum(a);
    }
    int GetLength(){
        return length;
    }
    void SetLength(int i){
        length = i;
    }
    int GetHeapSize(){
        return heap_size;
    }
    void SetHeapSize(int i){
        heap_size = i;
    }
    int GetD(){
        return d;
    }
    
    
    void Swap(int i, int j){
        Type temp = array[i].Copy();
        array[i] = array[j].Copy();
        array[j] = temp.Copy();
    }
    void SelfSubtractHeapSize(){
        heap_size --;
    }
    void SelfPlusHeapSize(){
        heap_size ++;
    }
    void MaxHeapify(int i);
    void MaxHeapify1(int i);
    void BuildMaxHeap();
    void HeapSort();
    Type HeapMaximum();
    Type ExtractMax();
    void IncreaseKey(int i,int a);
    void MaxHeapInsert(Type a);
    void HeapDelete(int i);
    void Insert(Type a);
    Type Delete();
    
};


//堆本身数据结构
class Heap{
private:
    Type * array; //堆节点
    int length;  //实际个数
    int heap_size;//堆中个数
public:
    Heap(Type * a, int b, int c){
        array = a;
        length = b;
        heap_size = c;
    }
    int GetNum(int i){
        return array[i].GetNum();
    }
    void SetNum(int i, int a){
        array[i].SetNum(a);
    }
    int GetLength(){
        return length;
    }
    void SetLength(int i){
        length = i;
    }
    
    int GetHeapSize(){
        return heap_size;
    }
    void SetHeapSize(int i){
        heap_size = i;
    }
    void Swap(int i, int j){
        Type temp = array[i].Copy();
        array[i] = array[j].Copy();
        array[j] = temp.Copy();
    }
    void SelfSubtractHeapSize(){
        heap_size --;
    }
    void SelfPlusHeapSize(){
        heap_size ++;
    }
    void MaxHeapify(int i);
    void MaxHeapify1(int i);
    void BuildMaxHeap();
    void HeapSort();
    Type HeapMaximum();
    Type ExtractMax();
    void IncreaseKey(int i,int a);
    void MaxHeapInsert(Type a);
    void HeapDelete(int i);
    void Insert(Type a);
    Type Delete();
};




#endif /* HEAPSORT_hpp */
