//
//  main.cpp
//  Tree-New
//
//  Created by 伏开宇 on 2017/6/30.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include <stack>
using namespace std;
class TreeNode{
public:
    int key;
    map<string, int> value; //存储各种信息
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
    int color; //0 = 红，1 = 黑
    TreeNode(int key){
        this->key = key;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        value.emplace("height", 0);
        value.emplace("bh", 0);
        value.emplace("size", 0);
        value.emplace("max", 0);
        value.emplace("high", 0);
        value.emplace("low", 0);
        color = 1;
    }
};
class Tree{
public:
    TreeNode* root;
    static TreeNode* NIL;
    map<string, int> attribute;
    Tree(){
        attribute.emplace("amount", 0);
        NIL->value["bh"] = 0;
        NIL->parent = NIL;
        NIL->left = NIL;
        NIL->right = NIL;
        root = NIL;
    }
    void InTreeWalk(TreeNode* cur){
        if (cur->left != nullptr) {
            InTreeWalk(cur->left);
        }
        cout<<cur->key<<" ";
        if (cur->right != nullptr) {
            InTreeWalk(cur->right);
        }
    }
    void preTreeWalk(TreeNode* cur){
        cout<<cur->key<<" ";
        if (cur->left != nullptr) {
            preTreeWalk(cur->left);
        }
        if (cur->right != nullptr) {
            preTreeWalk(cur->right);
        }
    }
    void PostTreeWalk(TreeNode* cur){
        if (cur->left != nullptr) {
            PostTreeWalk(cur->left);
        }
        if (cur->right != nullptr) {
            PostTreeWalk(cur->right);
        }
        cout<<cur->key<<" ";
    }
    void InTreeWalk(){
        stack<TreeNode*> S;
        TreeNode* cur = root;
        while (1) {
            if (cur != nullptr) {
                S.push(cur);
                cur = cur->left;
            }
            else{
                if (S.empty() == 1) {
                    break;
                }
                cur = S.top();
                S.pop();
                cout<<cur->key<<" ";
                cur = cur->right;
            }
        }
    }
    void PreTreeWalk(){
        stack<TreeNode*> S;
        TreeNode* cur = root;
        while (1) {
            if (cur != nullptr) {
                cout<<cur->key<<" ";
                S.push(cur);
                cur = cur->left;
            }
            else{
                if (S.empty() == 1) {
                    break;
                }
                cur = S.top();
                S.pop();
                cur = cur->right;
            }
        }
    }
    void PostTreeWalk(){
        stack<TreeNode*> S;
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        S.push(cur);
        while (S.empty() == 0) {
            cur = S.top();
            if ((cur->right == nullptr and cur->left == nullptr) or
                (pre != nullptr and (pre == cur->left or pre == cur->right))) {
                cout<<cur->key<<" ";
                S.pop();
                pre = cur;
            }
            else{
                if (cur->right != nullptr) {
                    S.push(cur->right);
                }
                if (cur->left != nullptr) {
                    S.push(cur->left);
                }
            }
        }
    }
    void ThreadInWalk(){
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        if (cur != nullptr) {
            while (cur != nullptr) {
                if (cur->left != nullptr){
                    prev = cur->left;
                    while (prev->right != nullptr and prev->right != cur) {
                        prev = prev->right;
                    }
                    if (prev->right == nullptr) { //第一次访问
                        prev->right = cur;
                        cur = cur->left;
                    }
                    else if(prev->right == cur){ //第二次访问
                        prev->right = nullptr;
                        cout<<cur->key<<" ";
                        cur = cur->right;
                    }
                }
                else{
                    cout<<cur->key<<" ";
                    cur = cur->right;
                }
            }
        }
    }
    void ThreadPreWalk(){
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        if (cur != nullptr) {
            while (cur != nullptr) {
                if (cur->left != nullptr){
                    prev = cur->left;
                    while (prev->right != nullptr and prev->right != cur) {
                        prev = prev->right;
                    }
                    if (prev->right == nullptr) { //第一次访问
                        cout<<cur->key<<" ";
                        prev->right = cur;
                        cur = cur->left;
                    }
                    else if(prev->right == cur){ //第二次访问
                        prev->right = nullptr;
                        cur = cur->right;
                    }
                }
                else{
                    cout<<cur->key<<" ";
                    cur = cur->right;
                }
            }
        }
    }
    TreeNode* Search(TreeNode* cur, int x){
        if (cur != nullptr) {
            if (cur->key == x) {
                return cur;
            }
            else if (cur->key > x) {
                return Search(cur->left, x);
            }
            else {
                return Search(cur->right, x);
            }
        }
        else {
            return nullptr;
        }
    }
    TreeNode* Search(int x){
        TreeNode* cur = root;
        while (cur != NIL) {
            if (cur->key == x) {
                return cur;
            }
            else if (cur->key < x){
                cur = cur->right;
            }
            else
                cur = cur->left;
        }
        return NIL;
    }
    TreeNode* Min(TreeNode* x){
        while (x->left != NIL) {
            x = x->left;
        }
        return x;
    }
    TreeNode* Max(TreeNode* x){
        while (x->right != NIL) {
            x = x->right;
        }
        return x;
    }
    TreeNode* Successor(TreeNode* x){
        if (x->right != NIL) {
            return Min(x->right);
        }
        TreeNode* parent = x->parent;
        while (parent != NIL and parent->left != x) {
            x = parent;
            parent = x->parent;
        }
        return parent;
    }
    TreeNode* Predecessor(TreeNode* x){
        if (x->left != NIL) {
            return Max(x->left);
        }
        TreeNode* parent = x->parent;
        while (parent != NIL and parent->right != x) {
            x = parent;
            parent = x->parent;
        }
        return parent;
    }
    void Insert(int x){
        attribute["amount"]++;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        while (cur != nullptr) {
            prev = cur;
            if (x <= cur->key) {
                cur = cur->left;
            }
            else {
                cur = cur->right;
            }
        }
        if (prev == nullptr) {
            root = new TreeNode(x);
            return;
        }
        if (x <= prev->key) {
            prev->left = new TreeNode(x);
            prev->left->parent = prev;
        }
        else {
            prev->right = new TreeNode(x);
            prev->right->parent = prev;
        }
    }
    void Insert(TreeNode* cur, int x){
        if (root == nullptr) {
            root = new TreeNode(x);
            attribute["amount"]++;
            return;
        }
        else if (cur == root){
            attribute["amount"]++;
        }
        if (x <= cur->key) {
            if (cur->left == nullptr) {
                cur->left = new TreeNode(x);
                cur->left->parent = cur;
            }
            else {
                Insert(cur->left, x);
            }
        }
        else {
            if (cur->right == nullptr) {
                cur->right = new TreeNode(x);
                cur->right->parent = cur;
            }
            else {
                Insert(cur->right, x);
            }
        }
    }
    void Delete(TreeNode* x){
        attribute["amount"]--;
        if (x->left == nullptr and x->right == nullptr) {
            if (x->parent == nullptr) {
                root = nullptr;
            }
            else{
                if (x->parent->left == x) {
                    x->parent->left = nullptr;
                }
                else {
                    x->parent->right = nullptr;
                }
            }
        }
        else if (x->left == nullptr or x->right == nullptr){
            TreeNode* child;
            if (x->left == nullptr) {
                child = x->right;
            }
            else {
                child = x->left;
            }
            if (x->parent == nullptr) {
                root = child;
                child->parent = nullptr;
            }
            else{
                if (x->parent->left == x) {
                    x->parent->left = child;
                    child->parent = x->parent;
                }
                else {
                    x->parent->right = child;
                    child->parent = x->parent;
                }
            }
        }
        else {
            if (x->right->left != nullptr){
                TreeNode* successor = Successor(x);
                successor->parent->left = successor->right;
                if (successor->right != nullptr) {
                    successor->right->parent = successor->parent;
                }
                successor->right = x->right;
                x->right->parent = successor;
                successor->parent = x;
                x->right = successor;
            }
            if (x->parent == nullptr) {
                root = x->right;
            }
            else {
                if (x->parent->left == x) {
                    x->parent->left = x->right;
                    x->right->parent = x->parent;
                }
                else{
                    x->parent->right = x->right;
                    x->right->parent = x->parent;
                }
            }
            x->right->left = x->left;
            x->left->parent = x->right;
        }
    }
    void TreePrint(TreeNode* T,int level);
    /*--------------------------------------|
     |                                       |
     |        红黑树相关函数                    |
     |                                       |
     |                                       |
     ----------------------------------------*/
    void Left_rotate(TreeNode* x){
        if (x->right != NIL) {
            TreeNode* y = x->right;
            x->right = y->left;
            if (y->left != NIL) {
                y->left->parent = x;
            }
            y->left = x;
            y->parent = x->parent;
            if (x->parent == NIL) {
                root = y;
            }
            else if (x->parent->left == x){
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            x->parent = y;
            y->value["size"] = x->value["size"];
            x->value["size"] = x->left->value["size"] + x->right->value["size"] + 1;
            y->value["max"] = x->value["max"];
            x->value["max"] = max(max(x->left->value["max"], x->right->value["max"]), x->value["high"]);
        }
    }
    void Right_rotate(TreeNode* x){
        if (x->left != NIL) {
            TreeNode* y = x->left;
            x->left = y->right;
            if (y->right != NIL) {
                y->right->parent = x;
            }
            y->right = x;
            y->parent = x->parent;
            if (x->parent == NIL) {
                root = y;
            }
            else if (x->parent->left == x){
                x->parent->left = y;
            }
            else {
                x->parent->right = y;
            }
            x->parent = y;
            y->value["size"] = x->value["size"];
            x->value["size"] = x->left->value["size"] + x->right->value["size"] + 1;
            y->value["max"] = x->value["max"];
            x->value["max"] = max(max(x->left->value["max"], x->right->value["max"]), x->value["high"]);
        }
    }
    void EditBh(TreeNode* cur){
        if (cur != NIL) {
            cur->value["bh"];
            EditBh(cur->parent);
        }
    }
    void Insert_Fixup(TreeNode* node){
        while (node->parent->color == 0) { //因为父亲结点为红色，所以肯定有爷爷结点
            if (node->parent->parent->left == node->parent) {
                TreeNode* uncle = node->parent->parent->right;
                if (uncle->color == 0) { //情况一,叔叔是红色
                    node->parent->color = 1;
                    uncle->color = 1;
                    node->parent->parent->color = 0;
                    node->parent->parent->value["bh"]++;
                    node = node->parent->parent;
                    continue;
                }
                else if (node == node->parent->right) { //情况二
                    node = node->parent;
                    Left_rotate(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                Right_rotate(node->parent->parent);
            }
            else{
                TreeNode* uncle = node->parent->parent->left;
                if (uncle->color == 0) {
                    node->parent->color = 1;
                    uncle->color = 1;
                    node->parent->parent->color = 0;
                    node->parent->parent->value["bh"]++;
                    node = node->parent->parent;
                    continue;
                }
                else if (node == node->parent->left){
                    node = node->parent;
                    Right_rotate(node);
                }
                node->parent->color = 1;
                node->parent->parent->color = 0;
                Left_rotate(node->parent->parent);
            }
        }
        root->color = 1;
    }
    void RB_Insert(int x){
        attribute["amount"]++;
        TreeNode* prev = NIL;
        TreeNode* cur = root;
        TreeNode* node = new TreeNode(x);
        node->value["size"] = 1;
        node->value["bh"] = 1;
        while (cur != NIL) {
            prev = cur;
            cur->value["size"]++;
            if (x <= cur->key) {
                cur = cur->left;
            }
            else
                cur = cur->right;
        }
        node->parent = prev;
        if (prev == NIL) {
            root = node;
        }
        else{
            if (x <= prev->key){
                prev->left = node;
            }
            else{
                prev->right = node;
            }
        }
        node->left = NIL;
        node->right = NIL;
        node->color = 0;
        Insert_Fixup(node);
    }
    void Transplant(TreeNode* u, TreeNode* v){
        if (u->parent == NIL) {
            root = v;
        }
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }
    void Delete_Fixup(TreeNode* x){
        while (x != root and x->color == 1) {
            if (x == x->parent->left) {
                TreeNode* w = x->parent->right;
                if (w->color == 0) { //将情况一转换为情况二、三、四
                    w->color = 1;
                    w->parent->color = 0;
                    Left_rotate(w->parent);
                    w = x->parent->right;
                }
                if (w->right->color == 1 and w->left->color == 1) { //情况二
                    w->color = 0;
                    x = x->parent;
                    x->value["bh"]--;
                    continue;
                }
                else if (w->right->color == 1 and w->left->color == 0){ //情况三
                    w->color = 0;
                    w->left->color = 1;
                    Right_rotate(w);
                    w = w->parent;
                }
                w->color = w->parent->color; //情况四
                w->parent->color = 1;
                w->right->color = 1;
                Left_rotate(w->parent);
                w->value["bh"]++;
                w->left->value["bh"]--;
                x = root;
            }
            else {
                TreeNode* w = x->parent->left;
                if (w->color == 0) {
                    w->color = 1;
                    w->parent->color = 0;
                    Right_rotate(w->parent);
                    w = x->parent->left;
                }
                if (w->left->color == 1 and w->right->color == 1) {
                    w->color = 0;
                    x = x->parent;
                    x->value["bh"]--;
                    continue;
                }
                else if (w->left->color == 1 and w->right->color == 0){
                    w->color = 0;
                    w->right->color = 1;
                    Left_rotate(w);
                    w = w->parent;
                }
                w->color = w->parent->color;
                w->left->color = 1;
                w->parent->color = 1;
                Right_rotate(w->parent);
                w->value["bh"]++;
                w->right->value["bh"]--;
                x = root;
            }
        }
        x->color = 1;
    }
    void RB_Delete(TreeNode* cur){
        TreeNode* temp = cur;
        TreeNode* x;
        int original_color = cur->color;
        if (cur->left == NIL and cur->right == NIL) {
            Transplant(cur, cur->left);
            x = cur->left;
        }
        else if(cur->left != NIL and cur->right == NIL){
            Transplant(cur, cur->left);
            x = cur->left;
        }
        else if(cur->right != NIL and cur->right == NIL){
            Transplant(cur, cur->right);
            x = cur->right;
        }
        else {
            temp = Successor(cur);
            original_color = temp->color;
            x = temp->right;
            if (temp->parent != cur) {
                Transplant(temp, temp->right);
                temp->right = cur->right;
                temp->right->parent = temp;
            }
            else {
                x->parent = temp;
            }
            Transplant(cur, temp);
            temp->value["bh"] = cur->value["bh"];
            temp->left = cur->left;
            cur->left->parent = temp;
            temp->color = cur->color;
        }
        for (TreeNode* temp = x->parent; temp != NIL; temp = temp->parent) {
            temp->value["value"]--;
        }
        if (original_color == 1) { //如果被删除的是黑色结点则需要调整
            Delete_Fixup(x);
        }
    }
    TreeNode* Select(int i){
        int rank = root->left->value["size"] + 1;
        TreeNode* cur = root;
        if (i > root->value["size"]) {
            cout<<"there is no more than i elements in the tree"<<endl;
            return NIL;
        }
        while (rank != i) {
            if (rank < i) {
                i = i - rank;
                cur = cur->right;
                rank = cur->left->value["size"] + 1;
            }
            else {
                cur = cur->left;
                rank = cur->left->value["size"] + 1;
            }
        }
        return cur;
    }
    int Rank(TreeNode* k){
        int rank = k->left->value["size"] + 1;
        for (TreeNode* cur = k->parent; cur != NIL; cur = cur->parent) {
            if (cur->right == k) {
                rank += cur->left->value["size"] + 1;
            }
            k = cur;
        }
        return rank;
    }
    void int_Insert(int low, int high){
        attribute["amount"]++;
        TreeNode* prev = NIL;
        TreeNode* cur = root;
        TreeNode* node = new TreeNode(low);
        node->value["low"] = low;
        node->value["high"] = high;
        node->value["max"] = high;
        node->value["size"] = 1;
        node->value["bh"] = 1;
        while (cur != NIL) {
            prev = cur;
            cur->value["size"]++;
            cur->value["max"] = max(high, cur->value["max"]);
            if (low <= cur->key) {
                cur = cur->left;
            }
            else
                cur = cur->right;
        }
        node->parent = prev;
        if (prev == NIL) {
            root = node;
        }
        else{
            if (low <= prev->key){
                prev->left = node;
            }
            else{
                prev->right = node;
            }
        }
        node->left = NIL;
        node->right = NIL;
        node->color = 0;
        Insert_Fixup(node);;
    }
    void int_Delete(TreeNode* cur){
        TreeNode* temp = cur;
        TreeNode* x;
        int original_color = cur->color;
        if (cur->left == NIL and cur->right == NIL) {
            Transplant(cur, cur->left);
            x = cur->left;
        }
        else if(cur->left != NIL and cur->right == NIL){
            Transplant(cur, cur->left);
            x = cur->left;
        }
        else if(cur->right != NIL and cur->right == NIL){
            Transplant(cur, cur->right);
            x = cur->right;
        }
        else {
            temp = Successor(cur);
            original_color = temp->color;
            x = temp->right;
            if (temp->parent != cur) {
                Transplant(temp, temp->right);
                temp->right = cur->right;
                temp->right->parent = temp;
            }
            else {
                x->parent = temp;
            }
            Transplant(cur, temp);
            temp->value["bh"] = cur->value["bh"];
            temp->left = cur->left;
            cur->left->parent = temp;
            temp->color = cur->color;
        }
        for (TreeNode* temp = x->parent; temp != NIL; temp = temp->parent) {
            temp->value["value"]--;
            temp->value["max"] = max(max(temp->value["high"], temp->left->value["max"]), temp->right->value["max"]);
        }
        if (original_color == 1) { //如果被删除的是黑色结点则需要调整
            Delete_Fixup(x);
        }
    }
};
TreeNode* Tree::NIL = new TreeNode(INT32_MIN);
void Tree::TreePrint(TreeNode* T,int level){
    if (T->right != NIL) {
        TreePrint(T->right, level + 1);
    }
    for (int i=0 ; i<level; i++)	//按照递归的层次打印空格
    {
        printf("        ");
    }
    cout<<"---"<<T->key<<"-"<<T->value["high"]<<":"<<T->value["max"]<<endl;
    if (T->left != NIL) {
        TreePrint(T->left, level + 1);
    }
}
int main(int argc, const char * argv[]) {
    int num = 20;
    int* a = new int[num];
    Tree* T = new Tree();
    for (int i = 0; i < num; i++) {
        a[i] = arc4random_uniform(50);
        T->int_Insert(a[i], a[i] + arc4random_uniform(50));
        //T->RB_Insert(a[i]);
        //cout<<a[i]<<endl;
        //        T->TreePrint(T->root, 0);
        //        cout<<endl;
    }
    T->TreePrint(T->root, 0);
    T->int_Delete(T->root->right);
    cout<<endl;
    cout<<endl;
    T->TreePrint(T->root, 0);
    return 0;
}
