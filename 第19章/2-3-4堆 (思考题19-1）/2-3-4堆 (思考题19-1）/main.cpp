//
//  main.cpp
//  2-3-4堆 (思考题19-1）
//
//  Created by 伏开宇 on 2017/4/6.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
class One_Two_ThreeTreeNode{
public:
    int key;
    bool is_leaf;
    int n;
    One_Two_ThreeTreeNode* p;
    One_Two_ThreeTreeNode** child;
    One_Two_ThreeTreeNode(int i){
        n = 0;
        key = i;
        is_leaf = 1;
        child = new One_Two_ThreeTreeNode* [4];
        p = nullptr;
    }
};

class One_Two_ThreeTree{
public:
    One_Two_ThreeTreeNode* root;
    int height;
    One_Two_ThreeTree(){
        root = nullptr;
        height = 0;
    }
    One_Two_ThreeTreeNode* Minimum();
    void DecreaseKey(One_Two_ThreeTreeNode* x, int k);
    void insert(One_Two_ThreeTreeNode* x);
    void Delete(One_Two_ThreeTreeNode* x);
    One_Two_ThreeTreeNode* extractMin(One_Two_ThreeTreeNode* r);
    void Union(One_Two_ThreeTree* h);
    void Split(One_Two_ThreeTreeNode* x, One_Two_ThreeTreeNode* y);
    void InsertNo(One_Two_ThreeTreeNode* x, One_Two_ThreeTreeNode* k);
    One_Two_ThreeTreeNode* ExtractMin();
};
One_Two_ThreeTreeNode* One_Two_ThreeTree::Minimum(){
    return extractMin(root);
}
void One_Two_ThreeTree::DecreaseKey(One_Two_ThreeTreeNode* x, int k){
    One_Two_ThreeTreeNode* temp = x->p;
    x->key = k;
    while (temp != nullptr) { //自底向上维护key
        temp->key = temp->child[0]->key;
        for(int i = 1; i < temp->n; i++){
            if(temp->key > temp->child[i]->key)
                temp->key = temp->child[i]->key;
        }
        temp = temp->p;
    }
}
void One_Two_ThreeTree::Split(One_Two_ThreeTreeNode* x, One_Two_ThreeTreeNode* y){
    One_Two_ThreeTreeNode* z = new One_Two_ThreeTreeNode(0);
    z->child[0] = y->child[2];
    z->child[1] = y->child[3];
    y->child[2] = nullptr;
    y->child[3] = nullptr;
    z->n = 2;
    y->n = 2;
    z->is_leaf = y->is_leaf;
    z->p = y->p;
    y->key = min(y->child[0]->key, y->child[1]->key);
    z->key = min(z->child[0]->key, z->child[1]->key);
    x->child[x->n] = z;
    x->n++;
}
void One_Two_ThreeTree::insert(One_Two_ThreeTreeNode* x){
    One_Two_ThreeTreeNode* r = root;
    if(r == nullptr){ //如果堆为空
        root = x;
    }
    else if(r->n == 0){ //如果堆只有一个结点
        One_Two_ThreeTreeNode* s = new One_Two_ThreeTreeNode(0); //增加一个内结点
        root = s;
        s->key = min(x->key, r->key);
        s->n = 2;
        s->is_leaf = 0;
        s->child[0] = r; //将原来的结点和新增加的结点作为内结点的两片叶子
        s->child[1] = x;
        height++;
        r->p = s;
        x->p = s;
    }
    else if(r->n == 4){
        One_Two_ThreeTreeNode* s = new One_Two_ThreeTreeNode(0);
        root = s;
        s->key = r->key;
        s->is_leaf = 0;
        s->n = 1;
        s->child[0] = r;
        r->p = s;
        height++;
        Split(s, r); //增加一个根，将原来的根作为其第一个孩子，并且分裂原来的根
        InsertNo(s, x); //递归插入
    }
    else
        InsertNo(r, x);
}
void One_Two_ThreeTree::InsertNo(One_Two_ThreeTreeNode* x, One_Two_ThreeTreeNode* k){
    if(x->key > k->key)    //维护key值
        x->key = k->key;
    if(x->child[0]->is_leaf){ //若已到达倒数第二层，则将新节点作为一个儿子插入
        x->child[x->n] = k;
        x->n++;
        x->key = min(x->key, k->key);
        k->p = x;
    }
    else{ //若在内部，用随机化算法，随机选择插入的分支，以免整个2-3-4堆过于瘦长
        int ran = arc4random_uniform(x->n);
        if(x->child[ran]->n == 4){
            Split(x, x->child[ran]); //若目标分支已满，则分裂，并且从分裂的两个分支中随机选择一个进入
            int m = arc4random_uniform(2);
            ran = m ? ran : x->n - 1;
        }
        InsertNo(x->child[ran], k);
    }
}
void One_Two_ThreeTree::Delete(One_Two_ThreeTreeNode* x){
    One_Two_ThreeTreeNode* p = x->p;
    if(p->n == 1){ //如果删除的结点为父亲的单独儿子，则向上迭代，直到找到某一层不为独生子，将除了非独生子的儿子以外的所遍历的结点全部删除
        delete x;
        One_Two_ThreeTreeNode* q = p->p;
        while (q!= nullptr and q->n == 1) {
            delete p;
            p = q;
            q = p->p;
        }
        x = p;
        p = q;
    }
    if(p == nullptr){ //若为空，则说明这是一个链形树，删除掉唯一的儿子则整个堆变为空
        root = nullptr;
        height = 0;
    }
    else{
        One_Two_ThreeTreeNode* temp = p;
        int i = 0;
        while(p->child[i]!= x) //找到要删除的结点
            i++;
        p->child[i] = nullptr;
        while(i < p->n - 1) //将后面的结点向前移动
            p->child[i] = p->child[i + 1];
        p->child[i + 1] = nullptr;
        p->n--;
        delete x;
        while (temp != nullptr) { //向上迭代维护key值
            temp->key = temp->child[0]->key;
            for(int i = 1; i < temp->n; i++){
                if(temp->key > temp->child[i]->key)
                    temp->key = temp->child[i]->key;
            }
            temp = temp->p;
        }
    }
}
One_Two_ThreeTreeNode* One_Two_ThreeTree::extractMin(One_Two_ThreeTreeNode* r){
    if(!r->is_leaf){ //由顶向下递归寻找到最小叶子的路径
        int i = 0;
        for(; i < r->n; i++){
            if(r->key == r->child[i]->key)
                break;
        }
        return extractMin(r->child[i]);
    }
    else
        return r;
}
One_Two_ThreeTreeNode* One_Two_ThreeTree::ExtractMin(){
    One_Two_ThreeTreeNode* temp;
    temp = extractMin(root); //返回最小叶子结点
    if(temp != nullptr){
        Delete(temp);  //删除该结点
    }
    return temp; //返回该结点
}
void One_Two_ThreeTree::Union(One_Two_ThreeTree* h){
    One_Two_ThreeTreeNode* r;
    One_Two_ThreeTreeNode* s;
    One_Two_ThreeTreeNode* e;
    int h1,h2;
    if(h->height != height){ //若两个堆高度不等
        if(h->height < height){
            r = root;
            s = h->root;
            h1 = h->height;
            h2 = height;
        }
        else{
            r = h->root;
            s = root;
            h1 = height;
            h2 = h->height;
        }
        e = r;
        while(h2 - 1 > h1){ //在高的堆中找到高度和低的堆高度相同的一层
            if(r->child[0]->n == 4)
                Split(r, r->child[0]); //如下降路径上发现满结点则分裂
            r = r->child[0];
            h2--;
        }
        r->child[r->n] = s; //将低的堆作为一个儿子插入到高的堆高度对应的一层
        s->p = r;
        r->n++;
        One_Two_ThreeTreeNode* temp = r;
        while (temp != nullptr) { //维护key值
            temp->key = temp->child[0]->key;
            for(int i = 1; i < temp->n; i++){
                if(temp->key > temp->child[i]->key)
                    temp->key = temp->child[i]->key;
            }
           temp = temp->p;
        }
        root = e; //更新根节点
        delete h;
    }
    else{ //若两个堆高度相同，则新增加一个结点作为根，原来的两个根作为其儿子
        One_Two_ThreeTreeNode* s = new One_Two_ThreeTreeNode(0);
        s->key = min(root->key, h->root->key);
        s->n = 2;
        s->is_leaf = 0;
        s->child[0] = root;
        s->child[1] = h->root;
        root->p = s;
        h->root->p = s;
        root = s;
        height++;
        delete h;
    }
}
int main(int argc, const char * argv[]) {
    int a[20] = {12,42,15,62,43,7,5,86,90,34,88,77,66,55,44,33,22,11,2,98};
    int b[5] = {1,34,56,99,3};
    One_Two_ThreeTree* h1 = new One_Two_ThreeTree();
    One_Two_ThreeTree* h2 = new One_Two_ThreeTree();
    for(int i = 0; i < 20; i++){
        One_Two_ThreeTreeNode* temp = new One_Two_ThreeTreeNode(a[i]);
        h1->insert(temp);
    }
    for(int i = 0; i < 5; i++){
        One_Two_ThreeTreeNode* temp = new One_Two_ThreeTreeNode(b[i]);
        h2->insert(temp);
    }
    One_Two_ThreeTreeNode* test = new One_Two_ThreeTreeNode(2);
    h1->insert(test);
    h1->Union(h2);
    return 0;
}
