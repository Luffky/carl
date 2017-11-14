//
//  main.cpp
//  GREEDY-ALGORITHM
//
//  Created by 伏开宇 on 2017/3/28.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "select.hpp"
#include <math.h>
using namespace std;
//活动选择问题
//贪心算法递归
void Recursive(int* f, int* s, int i, int n){
    int m = i + 1;
    while(m <= n and s[m] < f[i])
        m++;
    if(m <= n){
        cout<<m<<" ";
        Recursive(f, s, m, n);
    }
}
//贪心算法迭代
void iterate(int* f, int* s, int n){
    int i = 1;
    int m = 2;
    cout<<i<<" ";
    while(m <= n){
        if(s[m] >= f[i]){
            cout<<m<<" ";
            i = m;
        }
        m++;
    }
}
//动态规划
void Dynamic(int* f, int* s, int n){
    int** c = new int*[n + 2];
    int** select = new int*[n + 2];
    for(int i = 0 ; i < n + 2; i++){
        c[i] = new int[n + 2];
        select[i] = new int[n + 2];
        for(int j = 0 ; j < n + 2; j++){
            c[i][j] = 0;
            select[i][j] = 0;
        }
    }
    for(int l = 2; l <= n + 1; l++){
        for(int i = 0; i <= n + 1 - l; i++){
            c[i][i + l] = 0;
            for(int k = i + 1; k < i + l; k++){
                if(s[k] >= f[i] and f[k] <= s[i + l]){
                    int temp = c[i][k] + c[k][i + l] + 1;
                    if(temp > c[i][i + l]){
                        c[i][i + l] = temp;
                        select[i][i + l] = k;
                    }
                }
            }
        }
    }
    for(int i = 0 ; i <= n + 1; i++){
        for(int j = 0 ; j <= n + 1; j++){
            cout<<select[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<c[0][n + 1]<<endl;
    int start = select[0][n + 1];
    while(start != 0){
        cout<<start<<" ";
        start = select[start][n + 1];
    }
}
//多教室活动调度 16.1-3
class Node{
public:
    int key;
    Node* next;
    Node* prev;
    Node(int k){
        key = k;
        next = nullptr;
        prev = nullptr;
    }
};
class ListNode{
public:
    Node* head;
    int n;
    int max;
    ListNode(){
        head = nullptr;
        n = 0;
        max = 0;
    }
    void Insert(Node* a){
        n++;
        if(max < n){
            max = n;
        }
        Node* temp = head;
        Node* prev = nullptr;
        if(temp == nullptr){
            head = a;
        }
        else{
            while(temp != nullptr and a->key > temp->key){
                prev = temp;
                temp = temp->next;
            }
            if(temp == nullptr){
                prev->next = a;
                a->prev = prev;
            }
            else if(temp == head){
                head = a;
                a->next = temp;
                temp->prev = a;
            }
            else{
                prev->next = a;
                a->prev = prev;
                a->next = temp;
                temp->prev = a;
            }
        
        }
    }
    void Delete(Node* a){
        n--;
        if(head == a){
            head = a->next;
            if(head != nullptr)
                head->prev = nullptr;
        }
        else{
            a->prev->next = a->next;
            if(a->next != nullptr)
                a->next->prev = a->prev;
        }
    }
    void Alldelete(int k){
        Node* temp = head;
        while(temp != nullptr and temp->key <= k){
            Delete(temp);
            temp = temp->next;
        }
    }
};
void Color(int* f, int* s, int n){
    ListNode* l = new ListNode;
    for(int i = 0; i < n; i++){
        int now = s[i];
        Node* temp = new Node(f[i]);
        l->Alldelete(now);
        l->Insert(temp);
    }
    cout<<l->max<<endl;
}
//0-1背包问题 16.2-2
void Print(int** c, int* w, int i , int j){
    if(i >= 1){
        if(c[i][j] != c[i - 1][j]){
            Print(c, w, i - 1, j - w[i - 1]);
            cout<<i<<" ";
        }
        else{
            Print(c, w, i - 1, j);
        }
    }
}
void bag(int* w, int* v, int n, int m){
    int** c = new int*[n + 1];
    //int**select = new int*[n + 1];
    for(int i = 0 ; i < n + 1 ; i++){
        c[i] = new int[m + 1];
        //select[i] = new int[m + 1];
        c[i][0] = 0;
        //select[i][0] = 0;
        if(i == 0){
            for(int j = 0 ; j < m + 1; j++){
                c[i][j] = 0;
                //select[i][j] = 0;
            }
        }
    }
    for(int i = 1 ; i < n + 1; i++){
        for(int j = 1; j < m + 1; j++){
            if(w[i - 1] > j){
                c[i][j] = c[i - 1][j];
            }
            else{
                if(c[i - 1][j] >= c[i - 1][j - w[i - 1]] + v[i - 1]){
                    c[i][j] = c[i - 1][j];
                    //select[i][j] = 0;
                }
                else{
                    c[i][j] = c[i - 1][j - w[i - 1]] + v[i - 1];
                    //select[i][j] = 1;
                }
            }
        }
    }
    cout<<c[n][m]<<endl;
    Print(c, w, n, m);
}
//部分背包问题 O(N)算法 16.2-6
int partitionx(int* w, int* v, int i , int j, int m){
    int mid = i;
    for(; mid <= j; mid++){
        if(v[mid] == m){
            break;
        }
    }
    int temp = v[mid];
    int temp1 = w[mid];
    v[mid] = v[j];
    w[mid] = w[j];
    v[j] = temp;
    w[j] = temp1;
    int key = v[j];
    int k = i - 1;
    for(int l = i; l < j; l++){
        if(v[l] <= key){
            k++;
            temp1 = w[l];
            temp = v[l];
            w[l] = w[k];
            v[l] = v[k];
            w[k] = temp1;
            v[k] = temp;
        }
    }
    temp1 = w[j];
    w[j] = w[k + 1];
    v[j] = v[k + 1];
    w[k + 1] = temp1;
    v[k + 1] = key;
    return k + 1;
}
void PartBag(int* w, int* v, int i, int j, int m, int n, int* value){
    int* lll = new int[n];
    for(int k = i; k <= j; k++){
        lll[k] = v[k];
    }
    int mid = SelectOut(lll, i, j, (i + j) / 2);
    
    int e = partitionx(w, v, i, j, mid);
//    cout<<v[e]<<w[e]<<endl;
//    for(int k = i ; k <= j; k++){
//        cout<<v[k]<<" "<<w[k]<<endl;
//    }
    int G = 0;
    for(int k = e + 1 ; k <= j; k++){
        G += w[k];
    }
    if(G > m){
        PartBag(w, v, e + 1, j, m, n, value);
    }
    else{
        if(G + w[e] >= m){
            for(int k = j; k > e; k--){
                cout<<"("<<v[k]<<","<<w[k]<<")"<<endl;
                *value += v[k] * w[k];
            }
            cout<<"("<<v[e]<<","<<m - G<<")"<<endl;
            *value += v[e] * (m - G);
        }
        else{
            for(int k = j; k >= e; k--){
                cout<<"("<<v[k]<<","<<w[k]<<")"<<endl;
                *value += v[k] * w[k];
            }
            PartBag(w, v, i, e - 1, m - G - w[e], n, value);
        }
    }
}
//任务调度问题 16.5
void Task(int* d, int* w, int n){
    int fine = 0;
    for(int i = 0 ; i < n - 1; i++){
        for(int j = n - 1; j > i; j--){
            if(w[j] > w[j - 1]){
                int temp = w[j];
                int temp1 = d[j];
                w[j] = w[j - 1];
                d[j] = d[j - 1];
                w[j - 1] = temp;
                d[j - 1] = temp1;
            }
        }
    }
    int* N = new int[n + 1];
    for(int i = 0 ; i <= n; i++){
        N[i] = 0;
    }
    for(int i = 0 ; i < n; i++){
        int flag = 0;
        for(int j = d[i]; j <= n; j++){
            N[j]++;
            if(N[j] > j){
                flag = 1;
                N[j]--;
                break;
            }
        }
        if(flag == 0){
            cout<<i + 1<<" ";
        }
        else
            fine += w[i];
    }
    cout<<"总惩罚数为"<<fine<<endl;
}
//找换硬币 思考题16-1
void FindChange(int n, int k, int c, int* coin, int m){
    //16-1.a 只有一角、五分、二角五分、一分
    int total = 0;
    if(k == 0){
        int l = n / 25;
        total += l;
        cout<<l<<"个二角五分  ";
        n = n % 25;
        l = n / 10;
        total += l;
        cout<<l<<"个一角  ";
        n = n % 10;
        l = n / 5;
        total += l;
        cout<<l<<"个五分  ";
        n = n % 5;
        l = n / 1;
        total += l;
        cout<<l<<"个一分"<<endl;
        cout<<"共计"<<total<<"个硬币"<<endl;
    }
    //16-1.b 有c的幂次面值硬币
    else if(k == 1){
        int cj = 1;
        int j;
        for(j = 0; cj <= n; j++){
            cj *= c;
        }
        j--;
        for(int i = j; i >= 0; i--){
            int d = pow(c, i);
            int l = n / d;
            total += l;
            cout<<l<<"个"<<d<<" ";
            n = n % d;
        }
        cout<<"共计"<<total<<"个硬币"<<endl;
    }
    //16-1.d 任意k种不同硬币
    else{
        int* coincount = new int[n + 1];
        int* ck = new int[n + 1];
        ck[0] = 0;
        for(int j = 1 ; j <= n; j++){
            ck[j] = INT32_MAX;
            for(int i = 0; i < m; i++){
                if(j - coin[i] >=0 and ck[j - coin[i]] < ck[j]){
                    ck[j] = ck[j - coin[i]];
                    coincount[j] = i;
                }
            }
            ck[j]++;
        }
        cout<<ck[n]<<endl;
        for(int i = n; i > 0;){
            cout<<coin[coincount[i]]<<" ";
            i = i - coin[coincount[i]];
        }
        cout<<endl;
    }
}
int partition(int* a, int p ,int r){
    int i = p - 1;
    int key = a[r];
    for(int j = p; j < r; j++){
        if(a[j] <= key){
            i++;
            int temp = a[j];
            a[j] = a[i];
            a[i] = temp;
        }
    }
    a[r] = a[i + 1];
    a[i + 1] = key;
    return i + 1;
}
void QuickSort(int* a, int p, int r){
    if(p < r){
        int q = partition(a, p, r);
        QuickSort(a, p, q - 1);
        QuickSort(a, q + 1, r);
    }
}
//最小化平均结束时间调度 思考题16-2
void Dispatch(Node1** p, int flag, int n){
    int total = 0;
    int time = 0;
    if(flag == 0){ //不可抢占
        Heap* h = new Heap(p, n);
        h->BuildHeap();
        Node1* temp;
        cout<<"|"<<time<<"|   ";
        for(int i = 0 ; i < n; i++){
            temp = h->HeapExtractMin();
            time += temp->p;
            total += time;
            cout<<temp->name<<"   |"<<time<<"|   ";
        }
        cout<<endl;
        cout<<(double)total/(double)n<<endl;
    }
    else{//可抢占可调度
        Node1** ak = new Node1*[n]; //未到来任务数组
        Heap* r = new Heap(p, n); //已到来任务优先队列
        Heap* e = new Heap(ak, n);//未到来任务优先队列
        e->heap_size = 0; //已到来任务队列初始为0
        r->BuildHeap(); //未到来任务建最小堆
        Node1* current = r->HeapExtractMin();
        int temp = current->p;
        current->p = current->r;
        current->r = temp;
        e->HeapInsert(current);
        time = current->r;
        for(int i = r->HeapMinimum()->p; i == time;){
            current = r->HeapExtractMin();
            temp = current->p;
            current->p = current->r;
            current->r = temp;
            e->HeapInsert(current);
            if(r->heap_size != 0)
                i = r->HeapMinimum()->p;
            else
                break;
        }
        current = e->HeapExtractMin();
        int next;
        if(r->heap_size != 0)
            next = r->HeapMinimum()->p;
        else
            next = INT32_MAX;
        cout<<"|"<<time<<"|   ";
        while(r->heap_size != 0 or e->heap_size != 0 or current != nullptr){
            if(current != nullptr and next >= time + current->p){ //如果目前有任务并且，在下一任务来之前，此任务先结束
                time += current->p;
                total += time;
                cout<<current->name<<"   |"<<time<<"|   ";
                if(e->heap_size != 0) //如果已到来队列里还有任务
                    current = e->HeapExtractMin();
                else
                    current = nullptr;
            }
            else if(current != nullptr and next < time + current->p){ //如果有任务，并且下一任务到来时此任务还没结束
                Node1* op;
                int temp;
                for(int i = r->HeapMinimum()->p; i == next;){
                    op = r->HeapExtractMin();
                    temp = op->p;
                    op->p = op->r;
                    op->r = temp;
                    e->HeapInsert(op);
                    if(r->heap_size != 0)
                        i = r->HeapMinimum()->p;
                    else
                        break;
                }
                op = e->HeapMinimum();
                if(op->p < current->p - (next - time)){ //如果当前任务剩余时间大于到来的程序执行时间
                    current->p -= (next - time);
                    e->HeapInsert(current); //将当前任务插回已到来任务队列中
                    if(time != next)
                        cout<<current->name<<"   |"<<next<<"|   ";
                    time = next;
                    current = e->HeapExtractMin(); //当前任务更换为处理时间最小的任务
                }
                if(r->heap_size != 0)
                    next = r->HeapMinimum()->p;
                else
                    next = INT32_MAX;
            }
            else{ //如果目前没有任务
                Node1* op;
                int temp;
                for(int i = r->HeapMinimum()->p; i == next;){
                    op = r->HeapExtractMin();
                    temp = op->p;
                    op->p = op->r;
                    op->r = temp;
                    e->HeapInsert(op);
                    if(r->heap_size != 0)
                        i = r->HeapMinimum()->p;
                    else
                        break;
                }
                current = e->HeapExtractMin();
                time = next;
                if(r->heap_size != 0)
                    next = r->HeapMinimum()->p;
                else
                    next = INT32_MAX;
            }
        }
        cout<<endl;
        cout<<"总计"<<total<<endl;
    }
}

int main(int argc, const char * argv[]) {
    int n = 6;
    Node1**m = new Node1*[n];
    int p[6] = {7,3,1,5,2,6};
    int r[6] = {2,4,5,15,16,17};
    string s[6] = {"a","b","c","d","e","f"};
    for(int i = 0; i < n; i++){
        m[i] = new Node1(r[i], p[i], s[i]);
    }
    Dispatch(m, 1, n);
    cout<<endl;
    return 0;
}
