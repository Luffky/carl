//
//  main.cpp
//  QUEUE
//
//  Created by 伏开宇 on 2017/3/13.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//双端数组队列 10.1-5练习
//head指向头元素，tail指向尾元素的下一个，head端插入队列时为shift向左增长，tail端插入队列为push向右增长，且一开始head为-1，直到插入任何元素以后，head就到tail的左边一个元素。如果head端左增长或tail端右增长且head == tail说明队列满，若head段右增长，tail端左增长且head == tail, 说明队列空，重新置head为-1。head == -1为队列空标志
class ArrayDeque{
private:
    int * a;
    int head;
    int tail;
    int length;
public:
    ArrayDeque(int *b, int n){
        a = b;
        length = n;
        head = -1;
        tail = 0;
    }
    
    int IsEmpty(){
        if( head == -1)
            return 1;
        else
            return 0;
    }
    void push(int x){
        if(head == tail){
            cout<<"队列满"<<endl;
            exit(0);
        }
        a[tail] = x;
        
        if(head == -1) //队列空
            head = tail;
        
        tail = (tail + 1) % length;
    }
    
    void shift(int x){
        if(head == tail){
            cout<<"队列满"<<endl;
            exit(0);
        }
        
        if(head == -1) //队列空
            head = tail;
        
        head = (head - 1 + length) % length;
        a[head] = x;
    }
    
    int pop(){
        if(head == -1){
            cout<<"队列空"<<endl;
            exit(0);
        }
        tail = (tail - 1 + length) % length;
        if(head == tail) //队列空
            head = -1;
        return a[tail];
    }
    
    int inshift(){
        if(head == -1){
            cout<<"队列空"<<endl;
            exit(0);
        }
        int x = a[head];
        head = (head + 1) % length;
        if(head == tail) //队列空
            head = -1;
        return x;
        
    }
};

//双栈队列 10.1-6练习
class ArrayStack{
private:
    int *a;
    int top;
    int length;
public:
    ArrayStack(int *b, int n){
        a = b;
        length = n;
        top = -1;
    }
    int StackEmpty(){
        if(top == -1)
            return 1;
        else
            return 0;
    }
    int StackFull(){
        if(top == length - 1)
            return 1;
        else
            return 0;
    }
    void push(int k){
        if(top < length - 1)
            a[++top] = k;
        else{
            cout<<"栈上溢出"<<endl;
            exit(0);
        }
    }
    int pop(){
        if (StackEmpty()) {
            cout<<"栈下溢出"<<endl;
            exit(0);
        }
        else{
            top--;
            return a[top + 1];
        }
    }
};

class TwoStackQueue{
private:
    ArrayStack *a;
    ArrayStack *b;
public:
    TwoStackQueue(int n){
        int *c = new int[n];
        int *d = new int[n];
        a = new ArrayStack(c, n);
        b = new ArrayStack(d, n);
    }
    int IsEmpty(){
        if(a->StackEmpty() and b->StackEmpty())
            return 1;
        else
            return 0;
    }
    int IsFull(){
        if(a->StackFull() and ! b->StackEmpty())
            return 1;
        else
            return 0;
    }
    void Enqueue(int x){
        if(IsFull() == 0){
            if(a->StackFull()){             //如果a满b空，则排空a到b
                while (!a->StackEmpty()) {
                    b->push(a->pop());
                }
            }
            a->push(x);
        }
        else{
            cout<<"队列已满"<<endl;
            exit(0);
        }
    }
    int Dequeue(){
        if(IsEmpty() == 0){
            if(b->StackEmpty()){ //如果b空，则排空a到b
                while (!a->StackEmpty()) {
                    b->push(a->pop());
                }
            }
            return b->pop();
        }
        else{
            cout<<"队列为空"<<endl;
            exit(0);
        }
    }
    
};

//数组队列
class ArrayQueue{
private:
    int *a;
    int head;
    int tail;
    int length;
public:
    ArrayQueue(int *b, int n){
        a = b;
        head = 0;
        tail = 0;
        length = n;
    }
    int IsEmpty(){
        if(head == tail)
            return 1;
        else
            return 0;
    }
    int IsFull(){
        if((tail + 1) % length == head)
            return 1;
        else
            return 0;
    }
    void Enqueue(int x){
        if(IsFull() == 0){
            a[tail] = x;
            tail = (tail + 1) % length;
        }
        else{
            cout<<"队列已满"<<endl;
            exit(0);
        }
    }
    int Dequeue(){
        if(IsEmpty() == 0){
            int x = a[head];
            head = (head + 1) % length;
            return x;
        }
        else{
            cout<<"队列为空"<<endl;
            exit(0);
        }
    }
    
};

//链表队列
class Node{
public:
    int key;
    Node * next;
    Node * prev;
    Node(int a){
        key = a;
        next = nullptr;
        prev = nullptr;
    }
};

class ListNode1{
public:
    Node *Sentinel;
    int n;
    ListNode1(){
        n = 0;
        Sentinel = new Node(INT32_MAX);
        Sentinel->next = Sentinel;
        Sentinel->prev = Sentinel;
    }
    Node ListSeaarch(int k){
        Node *x = Sentinel->next;
        while(x != Sentinel and x->key != k)
            x = x->next;
        return *x;
    }
    void ListInsert(Node *x){
        Sentinel->next->prev = x;
        x->next = Sentinel->next;
        Sentinel->next = x;
        x->prev = Sentinel;
        n++;
    }
    
    void ListDelete(Node *x){
        x->prev->next = x->next;
        x->next->prev = x->prev;
        n--;
    }
    
    Node ListPop(){
        if(n > 0){
            Node * temp = Sentinel->prev;
            ListDelete(temp);
            return *temp;
        }
        else{
            cout<<"链表空"<<endl;
            exit(0);
        }
    }
    
};

class ListQueue{
public:
    ListNode1 *l;
    ListQueue(){
        l = new ListNode1();
    }
    int IsEmpty(){
        if(l->n == 0)
            return 1;
        else
            return 0;
    }
    void push(int x){
        Node *temp = new Node(x);
        l->ListInsert(temp);
    }
    int pop(){
        if(IsEmpty() == 0){
            return l->ListPop().key;
        }
        else{
            cout<<"队列空"<<endl;
            exit(0);
        }
            
    }
    
};
int main(int argc, const char * argv[]) {
    cout<<(unsigned long)nullptr;
    return 0;
}
