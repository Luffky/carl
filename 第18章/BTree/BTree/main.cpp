//
//  main.cpp
//  BTree
//
//  Created by 伏开宇 on 2017/4/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Btree.hpp"
//B树的合并与分裂
class S{
public:
    Btree* s1;
    Btree* s2;
    S(Btree* a, Btree* b){
        s1 = a;
        s2 = b;
    }
};
Btree* Rejoin(Btree* a, Btree* b, int k){ //假设 a.key < k < b.key
    if(a->root->n != 0 and b->root->n != 0){
        if(a->root->height == b->root->height){
            BtreeNode* temp = new BtreeNode(a->t);
            temp->n++;
            temp->height = a->root->height + 1;
            temp->leaf = 0;
            temp->key[0] = k;
            temp->c[0] = a->root;
            temp->c[1] = b->root;
            a->root = temp;
            delete b;
            return a;
        }
        else if(a->root->height < b->root->height){
            BtreeNode* temp = b->FindHeight(a->root->height, 0);
            for(int i = temp->n ; i > 0; i--)
                temp->key[i] = temp->key[i - 1];
            temp->key[0] = k;
            temp->n++;
            for(int i = temp->n; i > 0; i--)
                temp->c[i] = temp->c[i - 1];
            temp->c[0] = a->root;
            delete a;
            return b;
        }
        else{
            BtreeNode* temp = a->FindHeight(b->root->height, 1);
            temp->key[temp->n] = k;
            temp->n++;
            temp->c[temp->n] = b->root;
            delete b;
            return a;
        }
    }
    else{
        if(a->root->n == 0){
            b->BtreeInsert(k);
            return b;
        }
        else{
            a->BtreeInsert(k);
            return a;
        }
    }
}
S* Break(Btree* a, Btree* s1, Btree* s2, int k){
    BtreeNode* r = a->root;
    int sen = 0;//哨兵
    int sen1 = 0;
    int flag = 0;
    while(1){
        int i = 0;
        int j = r->n - 1;
        while(j > -1 and k < r->key[j]){
            if(s2->root == nullptr) //此时s2未合并任何树
                s2->root = r->c[j + 1];
            else if(j == r->n - 1){ //此时s2已不空，且该子结点为最右子结点
                Btree* temp = new Btree(2);
                temp->root = r->c[j + 1];
                s2 = Rejoin(temp, s2, sen1);
            }
            else{
                Btree* temp = new Btree(2);
                temp->root = r->c[j + 1];
                s2 = Rejoin(temp, s2, r->key[j + 1]);
            }
            j--;
        }
        if(j > -1 and k == r->key[j]){ //找到k
            if(s2->root == nullptr) //此时s2未合并任何树
                s2->root = r->c[j + 1];
            else{
                Btree* temp = new Btree(2);
                temp->root = r->c[j + 1];
                if(j == r->n - 1)
                    s2 = Rejoin(temp, s2, sen1);
                else
                    s2 = Rejoin(temp, s2, r->key[j + 1]);
            }
        }
        else if(r->c[j + 1]->leaf){ //未找到k，但是下一个结点是叶节点
            if(s2->root == nullptr){ //此时s2未合并任何树
                BtreeNode* ne = new BtreeNode(2);
                s2->root = ne;
            }
            else{
                if(j == r->n - 1)
                    s2->BtreeInsert(sen1);
                else
                    s2->BtreeInsert(r->key[j + 1]);
            }
        }
        while(i < r->n and k > r->key[i]){
            if(s1->root == nullptr) //此时s1未合并任何树
                s1->root = r->c[i];
            else if(i == 0){ //此时s1已不空，且该子结点为最左子结点
                Btree* temp = new Btree(2);
                temp->root = r->c[i];
                s1 = Rejoin(s1, temp, sen);
            }
            else{
                Btree* temp = new Btree(2);
                temp->root = r->c[i];
                s1 = Rejoin(s1, temp, r->key[i - 1]);
            }
            i++;
        }
        if(i < r->n and k == r->key[i]){ //找到k
            if(s1->root == nullptr) //此时s1未合并任何树
                s1->root = r->c[i];
            else{
                Btree* temp = new Btree(2);
                temp->root = r->c[i];
                if(i == 0)
                    s1 = Rejoin(s1, temp, sen);
                else
                    s1 = Rejoin(s1, temp, r->key[i - 1]);
                break;
            }
        }
        else if(r->c[i]->leaf){ //未找到k，但是下一个结点是叶节点
            flag = 1;
            if(s1->root == nullptr){ //此时s2未合并任何树
                BtreeNode* ne = new BtreeNode(2);
                s1->root = ne;
            }
            else{
                if(i == 0)
                    s1->BtreeInsert(sen);
                else
                    s1->BtreeInsert(r->key[i - 1]);
            }
            r = r->c[i];
            break;
        }
        if(i > 0)
            sen = r->key[i - 1];
        if(j < r->n - 1)
            sen1 = r->key[j + 1];
        r = r->c[i];
    }
    if(flag){
        int i = 0;
        int j = r->n - 1;
        while(i < r->n and k > r->key[i]){
            s1->BtreeInsert(r->key[i]);
            i++;
        }
        while (i > -1 and k < r->key[j]) {
            s2->BtreeInsert(r->key[j]);
            j--;
        }
    }
    S* kk = new S(s1,s2);
    return kk;
}
int main(int argc, const char * argv[]) {
    Btree* b = new Btree(2);
    for(int i = 0 ; i < 20; i++){
        b->BtreeInsert(i);
    }
    Btree* s1 = new Btree(2);
    Btree* s2 = new Btree(2);
    s1->root = nullptr;
    s2->root = nullptr;
    S* s = new S(nullptr, nullptr);
    s = Break(b, s1, s2, 15);
    return 0;
}
