//
//  main.cpp
//  HASH
//
//  Created by 伏开宇 on 2017/3/15.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;
#define SLOT 23 //槽数
#define A 0.6180339887 //乘法哈希参数
#define c1 1 //二次探查参数
#define c2 3
#define p 29 //全域哈希大素数
int DELETE = 0; //标记

//各种散列函数 11.3
int DivideHASH(int k){
    return k % SLOT;
}

int MultipleHASH(int k){
    double temp = k * A;
    int x = (int) floor(SLOT * (temp - floor(temp)));
    return x;
}
//全域哈希函数 选择a[1,p-1] b[0,p-1]
int UniversalHASH(int k, int a, int b, int m){
    int x = ((a * k + b) % p) % m;
    return x;
}

//开放寻址探查函数

//线性探查
int LinearProbing(int k, int i, int (* HASH)(int )){
    int x = (HASH(k) + i) % SLOT;
    return x;
}

//二次探查
int QuadraticProbing(int k ,int i, int (* HASH)(int )){
    int x = (HASH(k) + c1 * i + c2 * i * i) % SLOT;
    return x;
}

//双重散列
int DoubleHash(int k, int i, int (* HASH)(int )){
    int  x = (HASH(k) + i * (1 + (k % (SLOT - 1)))) % SLOT;
    return x;
}

int Hash(int k, int i, int (* PROBING)(int , int , int (* HASH)(int )), int (* HASH)(int )){
    return PROBING(k, i, HASH);
}



//字符串解释为自然数
int StringToKey(string s, int base, int n){
    int key = 0;
    for(int i = 0 ; i < n; i++){
        key += ((s[i] % SLOT) * (int) pow(base % SLOT, i)) % SLOT;
    }
    key = key % SLOT;
    return key;
}




//元素
class Element{
public:
    char data;
    int key;
    Element * next;
    Element * prev;
    Element(int k){
        key = k;
        next = nullptr;
        prev = nullptr;
    }
};
//完全散列 11.5
class SecondHash{
public:
    int mj;
    int aj;
    int bj;
    Element **a;
    SecondHash(int m, int ai, int bi){
        a = new Element*[m];
        for(int i = 0 ; i < m; i ++){
            a[i] = nullptr;
        }
        mj = m;
        aj = ai;
        bj = bi;
    }
    
    void Insert(Element *x){
        int n = UniversalHASH(x->key, aj, bj, mj);
        if(a[n] == nullptr)
            a[n] = x;
        else{
            cout<<"发生碰撞,插入失败"<<endl;
        }
    }
    
    Element *Search(int k){
        return a[UniversalHASH(k, aj, bj, mj)];
    }
};
class PerfectHash{
public:
    SecondHash **a;
    int m;
    int ak;
    int bk;
    PerfectHash(int ai, int bi, int n, int **k){
        a = new SecondHash*[n];
        for(int i = 0 ; i < n; i ++){
            a[i] = new SecondHash(k[i][0], k[i][1], k[i][2]);
        }
        m = n;
        ak = ai;
        bk = bi;
    }
    
    void Insert(Element *x){
        int n = UniversalHASH(x->key, ak, bk, m);
        SecondHash *temp = a[n];
        temp->Insert(x);
    }
    
    Element *Search(int k){
        int n = UniversalHASH(k, ak, bk, m);
        SecondHash *temp = a[n];
        Element *temp1 = temp->Search(k);
        if(temp1 == nullptr){
            cout<<"查找失败"<<endl;
            return temp1;
        }
        else
            return temp1;
    }
};
//开放寻址 11.4
class OpenAddress{
public:
    Element **a;
    int m;
    OpenAddress(int n){
        a = new Element*[n];
        for(int i = 0 ; i < n; i ++){
            a[i] = nullptr;
        }
        m = n;
    }
    
    void HashInsert(Element *x){
        int i = 0;
        int j;
        do{
            j = Hash(x->key, i, LinearProbing, DivideHASH);
            if(a[j] == nullptr || a[j] == (Element *)&DELETE){
                a[j] = x;
                return;
            }
            else
                i++;
        }while(i < m);
        cout<<"HASH表已满"<<endl;
    }
    
    Element *HashSearch(int k){
        int i = 0;
        int j;
        do{
            j = Hash(k, i, LinearProbing, DivideHASH);
            if(a[j] != nullptr and a[j] != (Element *)&DELETE and a[j]->key == k)
                return a[j];
            i++;
        }while(i < m and a[j] != nullptr);
        cout<<"未找到该元素"<<endl;
        return nullptr;
    }
    
    void HashDelete(Element *x){
        int i = 0;
        int j;
        do{
            j = Hash(x->key, i, LinearProbing, DivideHASH);
            if(a[j] == x){
                a[j] = (Element *)&DELETE;
                free(x);
                break;
            }
            i++;
        }while(i < m and a[j] != nullptr);
    }
};
//直接寻址 11.1
class DirectAddress{
public:
    Element **a;
    int m;
    DirectAddress(int n){
        a = new Element*[n];
        for(int i = 0 ; i < n; i ++){
            a[i] = nullptr;
        }
        m = n;
    }
    
    Element *DirectAddressSearch(int k){
        return a[k];
    }
    
    void DirectAddressInsert(Element *x){
        if(a[x->key] == nullptr)
            a[x->key] = x;
        else{
            cout<<"发生碰撞,插入失败"<<endl;
        }
    }
    
    void DirectAdressDelete(Element *x){
        a[x->key] = nullptr;
        free(x);
    }
    
    Element *DirectAdreeMaximum(){
        int max = -1;
        for(int i = m; i >= 0; i--){
            if(a[i] != nullptr)
                max = i;
        }
        if(max != -1)
            return a[max];
        else{
            cout<<"散列表为空"<<endl;
            return nullptr;
        }
    }
};
//链接哈希 11.2
class ChainedHash{
public:
    Element **a;
    int m;
    ChainedHash(int n){
        a = new Element*[n];
        for(int i = 0 ; i < n; i ++){
            a[i] = nullptr;
        }
        m = n;
    }
    
    Element *ChainedHashSearch(int k){
        Element *node = a[DivideHASH(k)];
        while(node != nullptr and node->key != k)
            node = node->next;
        if(node != nullptr)
            return node;
        else{
            cout<<"元素不存在"<<endl;
            return nullptr;
        }
    }
    
    void ChainedHashInsert(Element *x){
        if(a[DivideHASH(x->key)] == nullptr){
            a[DivideHASH(x->key)] = x;
        }
        else{
            x->next = a[DivideHASH(x->key)];
            a[DivideHASH(x->key)]->prev = x;
            a[DivideHASH(x->key)] = x;
        }
    }
    
    void ChainedHashDelete(Element *x){
        if(x->prev == nullptr){
            a[DivideHASH(x->key)] = x->next;
            if(x->next != nullptr)
                x->next->prev = nullptr;
        }
        else{
            if(x->next != nullptr){
                x->next->prev = x->prev;
                x->prev->next = x->next;
            }
            else
                x->prev->next = nullptr;
        }
        free(x);
        
    }
    
};
//大数组直接寻址 11.1-4
class ArrayStack{
public:
    Element **a;
    int top;
    int length;
    ArrayStack(int n){
        a = new Element*[n];
        for(int i = 0 ; i < n; i ++){
            a[i] = nullptr;
        }
        length = n;
        top = -1;
    }
    int StackEmpty(){
        if(top == -1)
            return 1;
        else
            return 0;
    }
    void move(int n){
        if(n <= top)
            a[n] = a[top];
        top--;
    }
    void push(Element *k){
        if(top < length - 1)
            a[++top] = k;
        else{
            cout<<"栈上溢出"<<endl;
            exit(0);
        }
    }
    Element *pop(){
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
class HugeArray{
public:
    int *a;
    int n;
    ArrayStack *s;
    HugeArray(int k){
        s = new ArrayStack(k);
        a = new int[k];
        n = k;
    }
    
    void Insert(Element *x){
        s->push(x);
        a[x->key] = s->top;
    }
    
    Element *Search(int k){
        int temp = a[k];
        if(temp != -1 and temp <= s->top and s->a[temp]->key == k)
            return s->a[temp];
        else{
            cout<<"不存在此元素"<<endl;
            return nullptr;
        }
    }
    
    void Delete(Element *x){
        int temp = a[x->key];
        a[s->a[s->top]->key] = temp;
        s->move(temp);
        a[x->key] = -1;
        
    }
    
    
};


//调试函数
void View(OpenAddress *o){
    for(int i = 0; i < SLOT; i++){
        cout<<o->a[i]->key<<" ";
    }
    cout<<endl;
}

int main(int argc, const char * argv[]) {
    Element **a;
    a = new Element*[SLOT];
    for(int i = 0 ; i < SLOT - 1; i++){
        a[i] = new Element(3 * i);
    }
    a[22] = new Element(2);
    OpenAddress *o = new OpenAddress(SLOT);
    for(int i = 0; i < SLOT; i++){
        o->HashInsert(a[i]);
    }
    o->HashDelete(o->HashSearch(2));
    o->HashSearch(3);
    cout<<o->HashSearch(45)->key<<endl;
    return 0;
}
