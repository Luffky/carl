//
//  main.cpp
//  Josephus排列(思考题14-2)
//
//  Created by 伏开宇 on 2017/3/22.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
using namespace std;
//14-2 a,m为常数，O(n)算法
void Joesphus(int m, int n){
    OnewayListNode* list = new OnewayListNode();
    for(int i = n ; i >= 1; i --){
        list->ListInsert(i);
    }
    Node1* curr = list->Sentinel->next;
    for(int i = 0; i < n; i++){
        for(int k = 0; k < m - 1; k++){
            curr = curr->next;
            if(curr == list->Sentinel)
                curr = curr->next;
        }
        cout<<curr->key<<" ";
        list->ListDelete(curr->key);
        curr = curr->next;
        if(curr == list->Sentinel)
            curr = curr->next;
    }
}
//14-2 b,m不是一个常数，O(nlgn)算法
void Joesphus1(int m, int n){
    RBTreeNode** node = new RBTreeNode*[n];
    RBTree* b = new RBTree();
    for(int i = 0 ; i < n; i++){
        node[i] = new RBTreeNode(i + 1, -1);
        b->RBTreeInsert(node[i]);
    }
    int t = 1;
    int q = n;
    for(int i = 0 ; i < n; i++){
        t = (t + m - 2) % q + 1;
        RBTreeNode* temp = b->Select(b->root, t);
        cout<<temp->key<<" ";
        b->RBTreeDelete(temp);
        q--;
    }
    cout<<endl;
}
int main(int argc, const char * argv[]) {
    int m = 3;
    int n = 21;
    Joesphus1(m, n);
    return 0;
}
