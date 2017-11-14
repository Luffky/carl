//
//  main.cpp
//  LINKLIST
//
//  Created by 伏开宇 on 2017/3/13.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//单链表节点
class Node1{
public:
    int key;
    Node1 * next;
    Node1(int a){
        key = a;
        next = nullptr;
    }
};



//环形单链表 有哑元 10.2-5练习
class OnewayListNode{
public:
    Node1 * Sentinel;
    int n;
    OnewayListNode(){
        Sentinel = new Node1(INT32_MAX);
        Sentinel->next = Sentinel;
        n = 0;
    }
    void Delete(){
        Node1 *x = Sentinel->next;
        Node1 *y;
        while(x != Sentinel){
            y = x->next;
            free(x);
            x = y;
        }
    }
    
    Node1* ListSearch(int k){
        Node1 *x = Sentinel->next;
        while(x != Sentinel and x->key != k){
            x = x->next;
        }
        if(x != Sentinel)
            return x;
        else
            return nullptr;
    }
    
    void ListInsert(int k){
        Node1 *node = new Node1(k);
        node->next = Sentinel->next;
        Sentinel->next = node;
    }
    
    void ListDelete(int k){
        Node1 *node = Sentinel;
        while(node->next != Sentinel){
            if(node->next->key == k){
                Node1 *temp = node->next;
                node->next = node->next->next;
                free(temp);
            }
            else
                node = node->next;
        }
        
    }
    
    void ListReverse(){
        Node1 *prev = Sentinel;
        Node1 *node = Sentinel->next;
        Node1 *next = node->next;
        while(node != Sentinel){
            node->next = prev;
            prev = node;
            node = next;
            next = node->next;
        }
        node->next = prev;
    }
};

//双链表节点
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

//双链表 无哑元
class ListNode{
public:
    Node * head;
    int n;
    ListNode(){
        n = 0;
        head = nullptr;
    }
    void Delete(){
        Node *x = head;
        Node *y;
        while(x != nullptr){
            y = x->next;
            free(x);
            x = y;
        }
    }
    Node* ListSearch(int k){
        Node *x = head;
        while(x != nullptr and x->key != k)
            x = x->next;
        return x;
    }
    
    void ListInsert(Node *x){
        x->next = head;
        if(head != nullptr)
            head->prev = x;
        x->prev = nullptr;
        head = x;
        n++;
    }
    
    void ListDelete(Node *x){
        if(x->prev != nullptr)
            x->prev->next = x->next;
        else
            head = x->next;
        if(x->next != nullptr)
            x->next->prev = x->prev;
        n--;
    }
    
    void ListUnion(ListNode *a){
        Node *x =head;
        if(head == nullptr){
            n += a->n;
            head = a->head;
            free(a);
        }
        else{
            while (x->next != nullptr) {
                x = x->next;
            }
            x->next = a->head;
            if(a->head != nullptr)
                a->head->prev = x;
            n += a->n;
            free(a);
        }
    }
    
};

//双链有序链表(链表实现的可合并最小堆 思考题10-2)
class SortedListNode{
public:
    Node *Sentinel;
    int n;
    SortedListNode(){
        n = 0;
        Sentinel = new Node(INT32_MAX);
        Sentinel->next = Sentinel;
        Sentinel->prev = Sentinel;
    }
    
    void ListSortedInsert(int key){ //排序插入
        Node *node = new Node(key);
        Node *temp = Sentinel->next;
        if(Sentinel->next == Sentinel){
            Sentinel->next = node;
            Sentinel->prev = node;
            node->next = Sentinel;
            node->prev = Sentinel;
        }
        else{
            while (key > temp->key and temp != Sentinel) {
                temp = temp->next;
            }
            temp->prev->next = node;
            node->prev = temp->prev;
            node->next = temp;
            temp->prev = node;
        }
        n++;
    }
    
    void ListDelet(int key){ //排序删除
        Node *node = Sentinel->next;
        while(node != Sentinel){
            if(node->key == key){
                node->prev->next = node->next;
                node->next->prev = node->prev;
                n--;
                break;
            }
                
        }
        cout<<"未找到对应key结点"<<endl;
    }
    
    void MergedList(SortedListNode *l){ //两排序链表合并
        Node *a = Sentinel->next;
        Node *b = l->Sentinel->next;
        Node *head = Sentinel;
        while(a != Sentinel and b!= l->Sentinel){
            if(a->key <= b->key){
                head->next = a;
                a->prev = head;
                a = a->next;
                head = head->next;
            }
            else{
                head->next = b;
                b->prev = head;
                b = b->next;
                head = head->next;
            }
        }
        if(a == Sentinel and  b == l->Sentinel){
            head->next = Sentinel;
            Sentinel->prev = head;
        }
        else if(a == Sentinel){
            head->next = b;
            b->prev = head;
            l->Sentinel->prev->next = Sentinel;
            Sentinel->prev = l->Sentinel->prev;
        }
        else{
            head->next = a;
            a->prev = head;
        }
        free(l);
    }
    
    int Mimum(){ //找最小关键值结点
        if(Sentinel->next != Sentinel)
            return Sentinel->next->key;
        else{
            cout<<"堆为空"<<endl;
            exit(0);
        }
    }
    
    int ExtractMin(){ //取出最小关键值结点
        if(Sentinel->next != Sentinel){
            Node *node = Sentinel->next;
            int key = node->key;
            node->next->prev = Sentinel;
            Sentinel->next = node->next;
            free(node);
            return key;
        }
        else{
            cout<<"堆为空"<<endl;
            exit(0);
        }
    }
    
    
    //未排序链表方法
    void ListInsert(int key){
        Node *x = new Node(key);
        Sentinel->next->prev = x;
        x->next = Sentinel->next;
        Sentinel->next = x;
        x->prev = Sentinel;
        n++;
    }
    
    int FindMin(){
        Node *node = Sentinel->next;
        int min = 0;
        if(node != Sentinel)
            min = node->key;
        while(node != Sentinel){
            if(min > node->key)
                min = node->key;
            node = node->next;
        }
        return min;
    }
    
    void ListUnion(SortedListNode *a){
        Node *x = Sentinel->prev;
        if(a->Sentinel->next != a->Sentinel){
            x->next = a->Sentinel->next;
            a->Sentinel->next->prev = x;
            Sentinel->prev = a->Sentinel->prev;
            a->Sentinel->prev->next = Sentinel;
        }
        free(a);
    }
    
    int Minimum(){
        return FindMin();
    }
    
    int ExtractMin2(){
        int key = FindMin();
        ListDelet(key);
        return key;
    }
    
    
    
    
    
}heap;

//双链表 有哑元
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
    void Delete(){
        Node *x = Sentinel->next;
        Node *y;
        while(x != Sentinel){
            y = x->next;
            free(x);
            x = y;
        }
    }
    Node* ListSeaarch(int k){
        Node *x = Sentinel->next;
        while(x != Sentinel and x->key != k)
            x = x->next;
        if(x != Sentinel)
            return x;
        else
            return nullptr;
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
    
    void ListUnion(ListNode1 *a){
        Node *x = Sentinel;
        while(x->next != Sentinel){
            x = x->next;
        }
        if(a->Sentinel->next != a->Sentinel){
            x->next = a->Sentinel->next;
            a->Sentinel->next->prev = x;
            Sentinel->prev = a->Sentinel->prev;
            a->Sentinel->prev->next = Sentinel;
        }
        free(a);
    }
    
};


//双链表单指针 10.2-8L练习
class Node2{
public:
    int key;
    Node2 *np;
    Node2(int k){
        key = k;
        np = nullptr;
    }
};

Node2 *xr(Node2 *left, Node2 *right) {
    return (Node2 *) (((unsigned long) left) ^ ((unsigned long) right));
}

class ListNode2{
public:
    Node2 * head;
    Node2 * tail;
    int n;
    ListNode2(){
        n = 0;
        head = nullptr;
        tail = nullptr;
    }
    void Delete(){
        Node2 *prev = nullptr;
        Node2 *node = head;
        Node2 *next;
        while(node != nullptr){
            next = xr(node->np, prev);
            free(node);
            prev = node;
            node = next;
            
        }
    }
    Node2 *ListSearch(int k){
        Node2 *prev = nullptr;
        Node2 *node = head;
        Node2 *next;
        
        while(node != nullptr and node->key != k){
            next = xr(node->np, prev);
            prev = node;
            node = next;
        }
        return node;
    }
    
    void ListInsert(Node2 *x){
        x->np = head;
        if(head == nullptr)
            tail = x;
        else{
            head->np = xr(head->np, x);
        }
        head = x;
        n++;
    }
    
    void ListDelete(Node2 *x){
        Node2 *prev = nullptr;
        Node2 *node = head;
        Node2 *next;
        while(node != x){
            next = xr(node->np, prev);
            prev = node;
            node = next;
        }
        next = xr(node->np, prev);
        if(prev)
            prev->np = xr(next, xr(prev->np, node));
        else
            head = next;
        if(next)
            next->np = xr(prev, xr(next->np, node));
        else
            tail = prev;
        free(x);
        
        n--;
    }
    
    void Reverse(){
        Node2 * temp = head;
        head = tail;
        tail = temp;
    }
    
};

//多数组双链表 10.3
class SingleArrayList{
public:
    int head;
    int free;
    int n = 10;
    int next[10];
    int key[10];
    int prev[10];
    SingleArrayList(){
        head = -1;
        free = 0;
        for (int i = 0; i < 9; i++) {
            next[i] = i + 1;
        }
        next[9] = -1;
    }
    
    int ListSeaarch(int k){
        if(head != -1){
            int now = head;
            while(now != -1){
                if(key[now] == k)
                    return now;
                now = next[now];
            }
            cout<<"查找失败"<<endl;
            return -1;
        }
        else{
            cout<<"链表为空,查找失败";
            exit(0);
        }
        
    }
    
    int AllocateObject(){
        if(free == -1){
            return -1;
        }
        else{
            int x = free;
            free = next[x];
            return x;
        }
    }
    
    void CompactifyObject(){
        if(free != -1){
            int h = free;
            while(h != -1){
                prev[h] = -2;
                h = next[h];
            }
            int left = 0;
            int right = n - 1;
            while(left != right){
                while(prev[left] != -2 and left < right)
                    left++;
                while(prev[right] == -2 and right > left)
                    right--;
                if(right != left){
                    next[left] = next[right];
                    key[left] = key[right];
                    prev[left] = prev[right];
                    next[right] = left;
                    prev[right] = -2;
                }
            }
            head = next[head];
            left = 0;
            while(left != right){
                if(next[left] >= right)
                    next[left] = next[next[left]];
                if(prev[left] >= right)
                    prev[left] = next[prev[left]];
                left++;
            }
            free = right;
            int i = right;
            for(; i< n - 1; i++){
                next[i] = i + 1;
            }
            next[i] = -1;
        }
        
    }
    
    void FreeObject(int x){
        next[x] = free;
        free = x;
    }
    
    void ListInsert(int k){
        int x = AllocateObject();
        if(x == -1)
            cout<<"链表已满"<<endl;
        else{
            key[x] = k;
            next[x] = head;
            prev[x] = -1;
            if(head != -1)
                prev[head] = x;
            head = x;
        }
    }
    
    void ListDelete(int k){
        if(next[k] != -1){
            prev[next[k]] = prev[k];
        }
        if(prev[k] != -1){
            next[prev[k]] = next[k];
        }
        if(head == k)
            head = next[k];
        FreeObject(k);
    }
    
    
};



int main(int argc, const char * argv[]) {
    SingleArrayList l;
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    for(int i = 0; i <10; i++){
        l.ListInsert(a[i]);
    }
    l.ListDelete(4);
    l.ListDelete(3);
    l.ListDelete(7);
    l.CompactifyObject();
    l.ListInsert(20);
    int temp = l.head;
    while(temp != -1){
        cout<<l.key[temp]<<" ";
        temp = l.next[temp];
    }
    cout<<endl;

    
    
    return 0;
}
