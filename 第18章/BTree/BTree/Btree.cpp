//
//  Btree.cpp
//  BTree
//
//  Created by 伏开宇 on 2017/4/3.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
#include "Btree.hpp"
using namespace std;
Return* Btree::Search(BtreeNode* x, int k){
    int  i = 0;
    while(i < x->n and k > x->key[i])
        i++;
    if(i < x->n and k == x->key[i]){
        Return* temp = new Return(x, i);
        return temp;
    }
    if(x->leaf){
        cout<<"查找失败"<<endl;
        return nullptr;
    }
    else{
        //DISK-READ(x->c[i]) 读取第i个子女
        return Search(x->c[i], k);
    }
}
void Btree::CreateBtree(){
    BtreeNode* x = new BtreeNode(t);
    //DISK-WRITE(x);
    root = x;
}
void Btree::BtreeSplitChild(BtreeNode* x, BtreeNode* y, int i){
    BtreeNode* z = new BtreeNode(t);
    z->leaf = y->leaf;
    z->height = y->height;
    z->n = t - 1;
    for(int j = 0; j < t - 1; j++) //分裂复制关键字
        z->key[j] = y->key[t + j];
    if(!y->leaf){
        for(int j = 0; j < t; j++) //分裂复制儿子指针
            z->c[j] = y->c[t + j];
    }
    y->n = t - 1;
    for(int j = x->n; j >= i + 1; i--) //移动父节点的儿子指针
        x->c[j + 1] = x->c[j];
    x->c[i + 1] = z; //父亲新增加的儿子
    for(int j = x->n - 1; j >= i; i--) //移动父节点的关键值
        x->key[j + 1] = x->key[j];
    x->key[i] = y->key[t - 1]; //父亲新增加的关键字
    x->n++;
    //DISK-WRITE(y),DISK-WRITE(z),DISK-WRITE(x)
}
void Btree::BtreeInsert(int k){
    BtreeNode* r = root;
    if(r->n == 2 * t - 1){ //如果根节点已满，建立一个空节点代替原有根节点，原有根节点成为其儿子，从而能够成功分裂
        BtreeNode* s = new BtreeNode(t);
        root = s;
        s->leaf = 0;
        s->c[0] = r;
        s->height = s->c[0]->height + 1;
        BtreeSplitChild(s, r, 0); //分裂原有根节点，此时树高增加1，此为树高增加的唯一途径
        BtreeInsertNonfull(s, k);//开始正常插入
    }
    else
        BtreeInsertNonfull(r, k);//若根节点不满直接递归插入
}
void Btree::BtreeInsertNonfull(BtreeNode* x, int k){
    int i = x->n - 1;
    if(x->leaf){ //若当前结点是叶节点，则插入
        while (i >= 0 and x->key[i] > k) {
            x->key[i + 1] = x->key[i];
            i--;
        }
        x->key[i + 1] = k;
        x->n++;
        //DISK-WRITE(X);
    }
    else{ //若当前结点是内部结点，则挑选路径
        while (i >= 0 and x->key[i] > k)
            i--;
        i++;
        //DISK-READ(x->c[i]);
        if(x->c[i]->n == 2 * t - 1){ //若该子树已满，则先分裂
            BtreeSplitChild(x, x->c[i], i);
            if(k > x->key[i]) //分裂后，根据中间数的大小再次挑选子路径
                i++;
        }
        BtreeInsertNonfull(x->c[i], k);
    }
}
int Btree::FindMin(BtreeNode* x){
    BtreeNode* r = x;
    if(r != nullptr and r->n != 0){
        while(r->leaf == 0){
            //DISK-READ(r->c[0])
            r = r->c[0];
        }
        return r->key[0];
    }
    else{
        cout<<"该子树为空"<<endl;
        exit(0);
    }
}
int Btree::FindMax(BtreeNode* x){
    BtreeNode* r = x;
    int i = r->n;
    if(i != 0){
        while(r->leaf == 0){
            //DISK-READ(r->c[i])
            r = r->c[i];
            i = r->n;
        }
        return r->key[i - 1];
    }
    else{
        cout<<"该子树为空"<<endl;
        exit(0);
    }
}
int Btree::FindPredessor(BtreeNode* x, int i){
    if(x->leaf == 0){ //如果不是叶结点
        return FindMax(x->c[i]);
    }
    else if(i != 0){ //如果是叶结点，但不是第一个关键字
        return x->key[i - 1];
    }
    else{ //如果是叶节点且是第一个关键字
        BtreeNode* r = root;
        ListStack* s = new ListStack();
        while(1){
            int i = 0;
            while(i < r->n and r->key[i] < x->key[i])
                i++;
            if(i < r->n and r->key[i] == x->key[i]) //如果找到当前关键字则结束迭代
                break;
            if(r->leaf) //如果已到叶节点还没找到当前关键字，结束迭代
                break;
            s->push(r); //否则将下降到当前关键字路径上的结点压入栈中
            r = r->c[i]; //结点下降，继续迭代
        }
        BtreeNode* y = x;
        while(1){
            if(s->IsEmpty()){
                cout<<"没有前驱"<<endl;
                return -1;
            }
            BtreeNode* temp = s->pop();
            if(temp->c[0] != y){ //如果在某个祖先结点该结点所在子树不是第一个分支
                int j = 1;
                while(temp->c[j] != y)
                    j++;
                return temp->key[j - 1];
            }
            y = temp;
        }
        
    }
}
int Btree::FindSuccessor(BtreeNode* x, int i){
    if(x->leaf == 0){
        return FindMin(x->c[i + 1]);
    }
    else if(i != x->n - 1){
        return x->key[i + 1];
    }
    else{
        BtreeNode* r = root;
        ListStack* s = new ListStack();
        while(1){
            int i = 0;
            while(i < r->n and r->key[i] < x->key[i])
                i++;
            if(i < r->n and r->key[i] == x->key[i]) //如果找到当前关键字则结束迭代
                break;
            if(r->leaf) //如果已到叶节点还没找到当前关键字，结束迭代
                break;
            s->push(r); //否则将下降到当前关键字路径上的结点压入栈中
            r = r->c[i]; //结点下降，继续迭代
        }
        BtreeNode* y = x;
        while (1) {
            if(s->IsEmpty()){
                cout<<"没有后继"<<endl;
                return -1;
            }
            BtreeNode* temp = s->pop();
            if(temp->c[temp->n] != y){
                int j = 0;
                while(temp->c[j] != y)
                    j++;
                return temp->key[j];
            }
            y = temp;
        }
    }
}
void Btree::Merge(BtreeNode* x, BtreeNode* y, int k){
    x->key[t - 1] = k;
    for(int i = 0 ; i < t - 1; i++){
        x->key[t + i] = y->key[i];
        if(!x->leaf)
            x->c[t + i] = y->c[i];
    }
    x->c[2 * t - 1] = y->c[t - 1];
    x->n = 2 * t - 1;
    delete y;
}
void Btree::BtreeDelete(BtreeNode* x, int k){
    int i = 0;
    while(i < x->n and x->key[i] < k)
        i++;
    if(i < x->n and x->key[i] == k){ //如果关键字在该结点中
        if(x->leaf){ //如果该结点是一个叶节点 情况1
            while(i < x->n - 1){
                x->key[i] = x->key[i + 1];
                i++;
            }
            x->n--;
            return;
        }
        else{ //如果该结点是一个内结点
            int pre = x->c[i]->n;
            int suc = x->c[i + 1]->n;
            if(pre >= t){ //如果前驱结点大于等于t 情况2a
                int temp = FindMax(x->c[i]); //找到前驱关键字
                BtreeDelete(x->c[i], temp); //递归删除前驱关键字
                x->key[i] = temp; //用前驱关键字替换掉被删除的关键字
                return;
            }
            else if(suc >= t){ //如果后继结点大于等于t 情况2b
                int temp = FindMin(x->c[i + 1]);
                BtreeDelete(x->c[i + 1], temp);
                x->key[i] = temp;
                return;
            }
            else{ //如果前驱后继结点均小于t 情况2c
                Merge(x->c[i], x->c[i + 1], x->key[i]); //将后继结点合并入前驱结点
                int q = i;
                while(q < x->n - 1){ //维护前驱结点
                    x->key[q] = x->key[q + 1];
                    x->c[q + 1] = x->c[q + 2];
                    q++;
                }
                x->n--;
                if(x->n == 0){ //如果x为空结点，x必为根，用c[0]替换
                    if(root == x)
                        root = x->c[i];
                    delete x;
                }
                BtreeDelete(x->c[i], k);
            }
        }
    }
    else{ //如果关键字不在该结点中
        int n = x->c[i]->n;
        BtreeNode* p = x->c[i];
        if(n == t - 1){ //如果目标结点关键字数等于t-1
            if(i <= x->n - 1 and x->c[i + 1]->n >= t){ //有右兄弟结点，且至少有t个关键字
                BtreeNode* suc = x->c[i + 1];
                BtreeNode* now = x->c[i];
                now->key[n] = x->key[i]; //父亲结点某关键字下降到该结点
                now->n++;
                x->key[i] = suc->key[0]; //右兄弟最小关键字上升到父亲结点
                for(int j = 0 ; j < suc->n - 1; j++){
                    suc->key[j] = suc->key[j + 1];
                }
                if(!suc->leaf){ //如果为内结点，则维护孩子指针数组
                    now->c[n + 1] = suc->c[0];
                    for(int j = 0 ; j < suc->n; j--){
                        suc->c[j] = suc->c[j + 1];
                    }
                }
                suc->n--;
            }
            else if(i > 0 and x->c[i - 1]->n >= t){ //有左兄弟结点，且至少有t个关键字
                BtreeNode* pre = x->c[i - 1];
                BtreeNode* now = x->c[i];
                for(int j = n; j > 0; j--){
                    now->key[j] = now->key[j - 1];
                }
                now->key[0] = x->key[i - 1]; //父亲结点某关键字下降到该结点
                if(!pre->leaf){ //如果为内结点，则维护孩子指针数组
                    for(int j = n + 1; j > 0; j--){
                        now->c[j] = now->c[j - 1];
                    }
                    now->c[0] = pre->c[pre->n];
                    pre->c[pre->n] = nullptr;
                }
                x->key[i - 1] = pre->key[pre->n - 1]; //左兄弟最大关键字上升到父亲结点
                pre->n--;
                now->n++;
            }
            else{ //左右兄弟均不满足小于t个关键字
                if(i <= x->n - 1){ //和右兄弟合并
                    Merge(x->c[i], x->c[i + 1], x->key[i]); //将右兄弟合并入结点
                    int k = i; //维护父亲结点
                    while(k < x->n - 1){
                        x->key[k] = x->key[k + 1];
                        x->c[k + 1] = x->c[k + 2];
                        k++;
                    }
                    x->n--;
                    if(x->n == 0){ //如果父亲节点为空结点，则用c[0]替换根
                        if(root == x)
                            root = x->c[i];
                        delete x;
                    }
                }
                else{ //和左兄弟合并
                    Merge(x->c[i - 1], x->c[i], x->key[i - 1]); //将结点合并入左兄弟
                    int k = i - 1; //维护父亲结点
                    while(k < x->n - 1){ //维护当前结点
                        x->key[k] = x->key[k + 1];
                        x->c[k + 1] = x->c[k + 2];
                        k++;
                    }
                    x->n--;
                    if(x->n == 0){ //如果x合并后为空结点
                        if(root == x)
                            root = x->c[i - 1];
                        delete x;
                    }
                    p = x->c[i - 1];
                }
            }
        }
        BtreeDelete(p, k);
    }
}
BtreeNode* Btree::FindHeight(int h, int t){
    if(t == 0){//寻找最左结点
        BtreeNode* r = root;
        if(r->n == 2 * this->t - 1){ //若根节点已满
            BtreeNode* s = new BtreeNode(this->t);
            root = s;
            s->leaf = 0;
            s->c[0] = r;
            s->height = s->c[0]->height + 1;
            BtreeSplitChild(s, r, 0);
            r = s;
        }
        //开始迭代
        while(r->height - 1 > h){
            if(r->c[0]->n == 2 * this->t - 1){//若最左结点已满
                BtreeSplitChild(r, r->c[0], 0);
            }
            r = r->c[0];
        }
        return r;
        
    }
    else{ //寻找最右结点
        BtreeNode* r = root;
        if(r->n == 2 * this->t - 1){ //若根节点已满
            BtreeNode* s = new BtreeNode(this->t);
            root = s;
            s->leaf = 0;
            s->c[0] = r;
            s->height = s->c[0]->height + 1;
            BtreeSplitChild(s, r, 0);
            r = s;
        }
        //开始迭代
        while(r->height - 1 > h){
            if(r->c[r->n]->n == 2 * this->t - 1){//若最左结点已满
                BtreeSplitChild(r, r->c[r->n], r->n);
            }
            r = r->c[r->n];
        }
        return r;
    }
}
