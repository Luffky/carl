//
//  main.cpp
//  哈夫曼编码贪心算法
//
//  Created by 伏开宇 on 2017/3/29.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
class Node{
public:
    char c;
    int f;
    string chr;
    Node* left;
    Node* right;
    Node(char ch, int fc){
        c = ch;
        f = fc;
        left = nullptr;
        right = nullptr;
        chr = nullptr;
    }
    Node(string s, Node* l, Node* r){
        chr.assign(s);
        left = l;
        right = r;
    }
    int IsLeaf(){
        if(left == nullptr and right == nullptr)
            return 1;
        else
            return 0;
    }
};
//最小优先队列
class Heap{
public:
    Node** a;
    int heap_size;
    int length;
    Heap(Node** b, int l){
        a = b;
        length = l;
    }
    void MinHeapify(int i);
    void BuildHeap();
    Node* HeapMinimum();
    Node* HeapExtractMin();
    void HeapInsert(Node* a);
    void DecreaseKey(int i, int k);
};
void Heap::MinHeapify(int i){
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int smallest = i;
    if(l < heap_size and a[smallest]->f > a[l]->f){
        smallest = l;
    }
    if(r < heap_size and a[smallest]->f > a[r]->f){
        smallest = r;
    }
    if(smallest != i){
        Node* temp = a[i];
        a[i] = a[smallest];
        a[smallest] = temp;
        MinHeapify(smallest);
    }
}
void Heap::BuildHeap(){
    heap_size = length;
    for(int i = heap_size / 2 - 1; i >= 0; i--){
        MinHeapify(i);
    }
}
Node* Heap::HeapMinimum(){
    return a[0];
}
Node* Heap::HeapExtractMin(){
    if(heap_size < 1)
        exit(0);
    Node* temp = a[0];
    heap_size--;
    a[0] = a[heap_size];
    MinHeapify(0);
    return temp;
}
void Heap::DecreaseKey(int i, int k){
    if(k > a[i]->f){
        cout<<"减小关键字大于原关键字，减小失败"<<endl;
        return;
    }
    a[i]->f = k;
    int p = (i - 1) / 2;
    while(1){
        if(a[i]->f < a[p]->f){
            Node* temp = a[p];
            a[p] = a[i];
            a[i] = temp;
        }
        i = p;
        if(i == 0)
            break;
        p = (p - 1) / 2;
    }
}
void Heap::HeapInsert(Node* b){
    if(heap_size == length){
        cout<<"堆已满"<<endl;
        return;
    }
    a[heap_size++] = b;
    int k = b->f;
    b->f = INT32_MAX;
    DecreaseKey(heap_size - 1, k);
}
//生成哈夫曼树
Node* Huffman(Node** c, int n){
    Heap* h;
    h = new Heap(c, n);
    h->BuildHeap();
    for(int i = 0; i < n - 1; i++){
        Node* z = new Node(' ', 0);
        z->left = h->HeapExtractMin();
        z->right = h->HeapExtractMin();
        z->f = z->left->f + z->right->f;
        h->HeapInsert(z);
    }
    return h->HeapExtractMin();
}
//哈夫曼树传输 16.3-5练习
void EncodeNode(Node* node, string s){
    if(node->IsLeaf()){
        s += "1";
        s += node->chr;
    }
    else{
        s += "0";
        EncodeNode(node->left, s);
        EncodeNode(node->right, s);
    }
}
Node* DecodeNode(string s, int* k){
    char c = s[(*k)++];
    if(c == '1'){
        string temp;
        temp.assign(s.substr(*k, *k + 7));
        *k = *k + 8;
        return new Node(temp, nullptr, nullptr);
    }
    else{
        Node* left = DecodeNode(s, k);
        Node* right = DecodeNode(s, k);
        return new Node(nullptr, left, right);
    }
}
int main(int argc, const char * argv[]) {
    int n = 8;
    Node** c = new Node*[n];
    for(int i = 0 ; i < n; i++){
        char j;
        int k;
        cin>>j>>k;
        c[i] = new Node(j, k);
    }
    Node* temp;
    temp = Huffman(c, n);
    return 0;
}
