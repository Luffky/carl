//
//  main.cpp
//  HEAP-SORT
//
//  Created by 伏开宇 on 2017/3/6.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
#define PARENT(i) ((i - 1) / 2)
#define LEFT(i) (2 * i + 1)
#define RIGHT(i) (2 * i + 2)
//堆节点数据结构
class Type{
private:
    int num;
public:
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
//堆本身数据结构
class Heap{
private:
    Type * array; //堆节点
    int length;
    int heap_size;
public:
    Heap(Type * a, int b){
        array = a;
        length = b;
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
    void MaxHeapify(int i);
    void MaxHeapify1(int i);
    void BuildMaxHeap();
    void HeapSort();
};

//堆排序 第六章
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
    this->SetHeapSize(this->GetLength());
    
    for (int i = this->GetLength()/2 - 1; i >= 0; i--) {
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




int main(int argc, const char * argv[]) {
    Type * a = new Type[10];
    for (int i = 0; i < 10; i++) {
        a[i].SetNum(arc4random_uniform(20));
    }
    for (int i = 0; i<10; i++) {
        cout<<a[i].GetNum()<<" ";
    }
    cout<<endl;
    Heap * h = new Heap(a,10);
    
    h->HeapSort();
    
    for (int i = 0; i<10; i++) {
        cout<<a[i].GetNum()<<" ";
    }
    cout<<endl;
    
    
    return 0;
}
