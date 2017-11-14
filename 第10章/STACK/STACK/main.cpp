//
//  main.cpp
//  STACK
//
//  Created by 伏开宇 on 2017/3/13.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//队列栈 10.1-7练习
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
    int IsLast(){
        if((head + 1) % length == tail)
            return 1;
        else
            return 0;
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

class QueueStack{
private:
    ArrayQueue **a;
    int active;
public:
    QueueStack(int n){
        a = new ArrayQueue*[2];
        int *b = new int[n + 1];
        int *c = new int[n + 1];
        a[0] = new ArrayQueue(b, n + 1);
        a[1] = new ArrayQueue(c, n + 1);
        active = 0;
    }
    int IsEmpty(){
        if(a[active]->IsEmpty())
            return 1;
        else
            return 0;
    }
    
    int IsFull(){
        if(a[active]->IsFull())
            return 1;
        else
            return 0;
    }
    
    void push(int k){
        if(IsFull() == 0)
            a[active]->Enqueue(k);
        else{
            cout<<"栈上溢出"<<endl;
            exit(0);
        }
    }
    
    int pop(){
        if (IsEmpty()) {
            cout<<"栈下溢出"<<endl;
            exit(0);
        }
        else{
            while (a[active]->IsLast() == 0) {
                a[1 - active]->Enqueue(a[active]->Dequeue());
            }
            active = 1 - active;
            return a[1 - active]->Dequeue();
        }
    }
    
};

//数组栈
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

//链表栈 10.2-2练习
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
            Node *temp = Sentinel->next;
            ListDelete(temp);
            return *temp;
        }
        else{
            cout<<"链表空"<<endl;
            exit(0);
        }
    }
    
};

class ListStack{
public:
    ListNode1 *l;
    ListStack(){
        l = new ListNode1();
    }
    int IsEmpty(){
        if(l->n == 0)
            return 1;
        else
            return 0;
    }
    
    void push(int x){
        Node * temp = new Node(x);
        l->ListInsert(temp);
    }
    
    int pop(){
        if(IsEmpty() == 0){
            int x = l->ListPop().key;
            return x;
        }
        else{
            cout<<"栈空"<<endl;
            exit(0);
        }
        
    }
};



int main(int argc, const char * argv[]) {
    ListStack *q = new ListStack;
    q->push(10);
    q->push(5);
    q->push(12);
    q->push(100);
    q->push(23);
    q->push(21);
    for(int i = 0; i < 7; i++){
        cout<<q->pop()<<" ";
    }
    cout<<endl;
    return 0;
}
