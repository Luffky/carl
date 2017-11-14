//
//  BinHeap.cpp
//  二项堆
//
//  Created by 伏开宇 on 2017/4/5.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include "BinHeap.hpp"
using namespace std;
BintreeNode* BinHeap::BinHeapMini(){
    BintreeNode* y = nullptr;
    BintreeNode* x = head;
    int min = INT32_MAX;
    while(x != nullptr){
        if(x->key < min){
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}
void BinHeap::BinLink(BintreeNode* y, BintreeNode* z){
    y->p = z;
    y->sibling = z->child;
    z->degree++;
    z->child = y;
}
BintreeNode* BinHeap::BinHeapMerge(BinHeap* H){
    BintreeNode* head = new BintreeNode(-1);
    BintreeNode* temp = head;
    BintreeNode* l = this->head;
    BintreeNode* r = H->head;
    while(l != nullptr and r != nullptr){
        if(l->degree <= r->degree){
            head->sibling = l;
            l = l->sibling;
            head = head->sibling;
        }
        else{
            head->sibling = r;
            r = r->sibling;
            head = head->sibling;
        }
    }
    if(l != nullptr){
        head->sibling = l;
    }
    else if(r != nullptr){
        head->sibling = r;
    }
    return temp->sibling;
}
void BinHeap::BinHeapUnion(BinHeap* H2){
    BinHeap* H = new BinHeap();
    H->head = BinHeapMerge(H2);
    delete H2;
    if(H->head == nullptr)
        this->head = nullptr;
    BintreeNode* prev = nullptr;
    BintreeNode* x = H->head;
    BintreeNode* next = x->sibling;
    while(next != nullptr){
        if(x->degree != next->degree or (next->sibling != nullptr and x->degree == next->sibling->degree))//如果当前结点和下个结点度数不同或者连续三个结点度数相同
        {
            prev = x;
            x = next;//移向下一个结点
        }
        else if(x->key <= next->key){ //连续两个相同度数结点且前面的key小于后面的key
            x->sibling = next->sibling;//连接后项
            BinLink(next, x);//将后面一个结点作为前一节点的最左儿子
        }
        else{//连续两个相同度数结点且后面的key小于前面的key
            if(prev == nullptr){ //如果当前是第一个结点
                H->head = next;
            }
            else{
                prev->sibling = next;
            }
            BinLink(x, next); //将前面一个节点作为后一个节点的最左儿子
            x = next; //当前结点向后移动一位
        }
        next = next->sibling;
    }
    this->head = H->head;
    free(H);
}
void BinHeap::BinHeapInsert(BintreeNode* x){
    BinHeap* H = new BinHeap;
    H->head = x;
    BinHeapUnion(H);
}
//不S使用union函数进行插入 19.2-8练习
void BinHeap::BinHeapInsert1(BintreeNode* x){
    BintreeNode* y = head;
    while(y != nullptr and y->degree == x->degree){
        if(x->key > y->key){
            BinLink(x, y);
            x = y;
            y = y->sibling;
        }
        else{
            BintreeNode* temp = y->sibling;
            BinLink(y, x);
            y = temp;
        }
    }
    head = x;
    x->sibling = y;
}
BintreeNode* BinHeap::BinHeapExtractMin(){
    BintreeNode* y = nullptr;
    BintreeNode* x = head;
    if(head != nullptr){
        int min = head->key;
        while(x->sibling != nullptr){
            if(x->sibling->key < min){
                min = x->sibling->key;
                y = x;
            }
            x = x->sibling;
        }
        if(y != nullptr){
            x = y->sibling;
            y->sibling = y->sibling->sibling;
        }
        else{
            x = head;
            head = head->sibling;
        }
        BinHeap* H = new BinHeap;
        BintreeNode* temp = x->child->sibling;
        y = x->child;
        y->p = nullptr;
        y->sibling = nullptr;
        BintreeNode* z;
        while(temp != nullptr){
            temp->p = nullptr;
            z = temp->sibling;
            temp->sibling = y;
            y = temp;
            temp = z;
        }
        H->head = y;
        BinHeapUnion(H);
        return x;
    }
    else
        return nullptr;
}
void BinHeap::BinHeapDec(BintreeNode* x, int k){
    if(k > x->key){
        cout<<"新值大于旧值"<<endl;
        exit(0);
    }
    x->key = k;
    BintreeNode* y = x;
    BintreeNode* z = y->p;
    while(z != nullptr and y->key < z->key){
        int temp = z->key;
        z->key = y->key;
        y->key = temp;
        y = z;
        z = y->p;
    }
}
void BinHeap::BinHeapDelete(BintreeNode* x){
    int i = BinHeapMini()->key;
    BinHeapDec(x, i - 1);
    BinHeapExtractMin();
}
