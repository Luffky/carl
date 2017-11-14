//
//  main.cpp
//  斐波那契堆
//
//  Created by 伏开宇 on 2017/4/7.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;
class fibTreeNode{
public:
    fibTreeNode* p;
    fibTreeNode* c;
    fibTreeNode* left;
    fibTreeNode* right;
    int key;
    int degree;
    int size; //子树结点树
    bool mark;
    fibTreeNode(int k){
        key = k;
        mark = false;
        size = 0;
        degree = 0;
        p = nullptr;
        c = nullptr;
        left = this;
        right = this;
    }
};
class fibTree{
public:
    fibTreeNode* min;
    int n;
    fibTree(){
        n = 0;
        min = nullptr;
    }
    fibTreeNode* Minimum(){
        return min;
    }
    void insert(fibTreeNode* x);
    void Union(fibTree* h);
    fibTreeNode* ExtractMin();
    void consolidate();
    void Link(fibTreeNode* a, fibTreeNode* b);
    void Decrease(fibTreeNode* x, int i);
    void cut(fibTreeNode* x, fibTreeNode* y, int d);
    void cascading_cut(fibTreeNode* y, int d);
    void Delete(fibTreeNode* y);
    void PisanoDelte(fibTreeNode* x);
    void ChangeKey(fibTreeNode* x, int i);
    void Prune(fibTreeNode* t, int r);
    bool is_larger(fibTreeNode* x, fibTreeNode* y);
};
void fibTree::insert(fibTreeNode* x){
    if(min == nullptr)
        min = x;
    else{//直接加入根链表
        x->left = min->left;
        x->right = min;
        min->left->right = x;
        min->left = x;
    }
    if(min->key > x->key)
        min = x;
    n++;
}
void fibTree::Union(fibTree* h){
    if(min == nullptr)
        min = h->min;
    else if(h->min == nullptr)
        ;
    else{
        h->min->right->left = min->left;
        min->left->right = h->min->right;
        h->min->right = min;
        min->left = h->min;
    }
    if(min != nullptr and h->min != nullptr and min->key > h->min->key)
        min = h->min;
    n = h->n + n;
    delete h;
}
fibTreeNode* fibTree::ExtractMin(){
    fibTreeNode* z = min;
    if(z != nullptr){
        fibTreeNode* y = z->c;
        fibTreeNode* x;
        for(int i = 0 ; i < z->degree; i++){ //对于被删除的结点的每一个子结点，都加到根链表中去
            x = y->right;
            insert(y);
            y->p = nullptr;
            y = x;
            n--;
        }
        z->left->right = z->right;
        z->right->left = z->left;
        if(z == z->right) //如果被删除的结点是堆中唯一的一个结点，则结束
            min = nullptr;
        else{//否则进入调整，调整整个堆的宽度
            min = z->right;
            consolidate();
        }
        n--;
    }
    return z;
}
void fibTree::Link(fibTreeNode* a, fibTreeNode* b){
    a->right->left = a->left;
    a->left->right = a->right;
    a->p = b;
    if(b->c == nullptr){//如果b没有孩子，直接成为b的孩子结点
        a->left = a;
        a->right = a;
        b->c = a;
    }
    else{//否则成为孩子结点的左结点
        b->c->left->right = a;
        a->left = b->c->left;
        b->c->left = a;
        a->right = b->c;
        b->c = a;
    }
    b->size = b->size + a->size + 1;
    b->degree++;
    a->mark = false;
}
void fibTree::consolidate(){
    int d = log2(n) + 1;
    fibTreeNode** A = new fibTreeNode*[d];
    for(int i = 0 ; i < d; i++)
        A[i] = nullptr;
    fibTreeNode* end = min->left; //循环结束标记
    fibTreeNode* now = min; //当前结点
    while(now != end){
        if(A[now->degree] != nullptr and A[now->degree] != now){ //如果当前有degree相同的其他根则合并
            if(A[now->degree]->key < now->key){
                Link(now, A[now->degree]);
                now = A[now->degree];
                A[now->degree - 1] = nullptr;
            }
            else{
                Link(A[now->degree], now);
                A[now->degree - 1] = nullptr;
            }
        }
        else{ //如果没有则加入数组
            A[now->degree] = now;
            now = now->right;
        }
    }
    while(A[now->degree] != nullptr){//对最后一个根进行合并
        if(A[now->degree]->key < now->key){
            Link(now, A[now->degree]);
            now = A[now->degree];
            A[now->degree] = nullptr;
        }
        else{
            Link(A[now->degree], now);
            A[now->degree - 1] = nullptr;
        }
    }
    end = now;
    min = now;
    do{//找到min
        if(min->key > now->key)
            min = now;
        now = now->right;
    }while(now != end);
}
void fibTree::Decrease(fibTreeNode* x, int i){
    if(i > x->key){
        cout<<"新值大于旧值"<<endl;
        exit(0);
    }
    int d = x->size + 1;
    x->key = i;
    fibTreeNode* y = x->p;
    if(y != nullptr and x->key < y->key){//调整堆的深度
        cut(x, y, d);
        cascading_cut(y, d);
    }
    
}
void fibTree::cut(fibTreeNode* x, fibTreeNode* y, int d){
    y->degree--;
    y->size = y->size - d;
    if(y->degree == 0)
        y->c = nullptr;
    else
        y->c = x->right;
    x->right->left = x->left;
    x->left->right = x->right;
    x->p = nullptr;
    x->mark = false;
    insert(x);
    n--;
}
void fibTree::cascading_cut(fibTreeNode* x, int d){
    fibTreeNode* z = x->p;
    if(z != nullptr){
        if(x->mark == false){ //如果没被标记则标记
            x->mark = true;
            while(z != nullptr){
                z->size = z->size - d;
                z = z->p;
            }
        }
        else{ //否则被递归cut
            cut(x, z, d + x->size + 1);
            cascading_cut(z, d + x->size + 1);
        }
    }
}
void fibTree::Delete(fibTreeNode* x){
    Decrease(x, INT_FAST32_MIN);
    ExtractMin();
}
//思考题20-1
void fibTree::PisanoDelte(fibTreeNode* x){
    if(x == min)
        ExtractMin();
    else{
        fibTreeNode* y = x->p;
        if(y != nullptr){
            cut(x, y, x->size + 1);
            cascading_cut(y, x->size + 1);
        }
        y = x->c;
        fibTreeNode* z;
        for(int i = 0 ; i < x->degree; i++){
            z = y->right;
            insert(y);
            y->p = nullptr;
            y = z;
            n--;
        }
        x->left->right = x->right;
        x->right->left = x->left;
    }
}
//思考题20-2
bool fibTree::is_larger(fibTreeNode* x, fibTreeNode* y){
    if(x->key > y->key)
        return 1;
    else
        return 0;
}
void fibTree::ChangeKey(fibTreeNode* x, int i){
    if(i <=  x->key)
        Decrease(x, i);
    else{
        x->key = i;
        while(x->c != nullptr){
            int flag = 0;
            fibTreeNode* child = x->c;
            for(int j = 0; j < x->degree; j++){//如果大于任何一个儿子，则交换key值，然后当前节点成为儿子结点，继续向下迭代
                if(is_larger(x, child)){
                    int temp = child->key;
                    child->key = x->key;
                    x->key = temp;
                    x = child;
                    flag = 1;
                    break;
                }
                child = child->right;
            }
            if(flag == 0)
                break;
        }
    }
}
void fibTree::Prune(fibTreeNode* t, int r){
    if(t == min){ //第一层根链表递归
        if(r < n){
            n = n - r;
            fibTreeNode* x = min;
            do{
                if(r > x->size){//如果删除的个数大于等于x的结点数，则直接删除x子树
                    x->left->right = x->right;
                    x->right->left = x->left;
                    r = r - x->size - 1;
                    x = x->right;
                }
                else{//如果删除的个数小于x的结点数，递归删除
                    x->size -= r;
                    Prune(x->c, r);
                    if(x->size == 0)
                        x->c = nullptr;
                    r = 0;
                }
            }while(r != 0);
            min = x;
            fibTreeNode* k = min;
            do {
                x = x->right;
                if(min->key > x->key)
                    min = x;
            } while (x != k);
        }
        else{
            min = nullptr;
            n = 0;
        }
    }
    else{ //进入子树递归
        fibTreeNode* x = t;
        do{
            if(r > x->size){//如果删除的个数大于等于x的结点数，则直接删除x子树
                x->left->right = x->right;
                x->right->left = x->left;
                x->p->degree--;
                r = r - x->size - 1;
                x = x->right;
                x->p->c = x;
            }
            else{//如果删除的个数小于x的结点数，递归删除
                x->size -= r;
                Prune(x->c, r);
                if(x->size == 0)
                    x->c = nullptr;
                r = 0;
            }
        }while(r != 0);
    }
}
int main(int argc, const char * argv[]) {
    fibTree* f = new fibTree();
    fibTreeNode** t = new fibTreeNode*[14];
    int a[14] = {23,7,3,18,39,52,38,41,17,30,24,26,35,46};
    int b;
    for(int i = 0 ; i < 9; i++){
        t[i] = new fibTreeNode(a[i]);
        f->insert(t[i]);
    }
    f->ExtractMin();
    t[6]->mark = true;
    f->Decrease(t[6], 2);
    f->Prune(f->min, 1);
    return 0;
}
