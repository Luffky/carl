//
//  main.cpp
//  TREE
//
//  Created by 伏开宇 on 2017/3/14.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include "Function.hpp"
using namespace std;
//二叉树 10.4-2，10.4-3练习
class BinaryTree{
public:
    TreeNode *root;
    int n;
    BinaryTree(){
        root = nullptr;
        n = 0;
    }
    //递归中序遍历
    void InorderTreeWalk(TreeNode *x){
        if(x != nullptr){
            InorderTreeWalk(x->left);
            cout<<x->key<<" ";
            InorderTreeWalk(x->right);
        }
    }
    //递归前序遍历
    void PreotorderTreeWalk(TreeNode *x){
        if(x != nullptr){
            cout<<x->key<<" ";
            PreotorderTreeWalk(x->left);
            PreotorderTreeWalk(x->right);
        }
    }
    //递归后序遍历
    void PostorderTreeWalk(TreeNode *x){
        if(x != nullptr){
            PostorderTreeWalk(x->left);
            PostorderTreeWalk(x->right);
            cout<<x->key<<" ";
        }
    }
    //使用栈的非递归中序遍历
    void StackInorderTreeWalk(){
        ListStack s;
        TreeNode *tree = root;
        while(1){
            if(tree != nullptr){
                s.push(tree);
                tree = tree->left;
            }
            else{
                if(s.IsEmpty() == 1)
                    break;
                tree = s.pop();
                cout<<tree->key<<" ";
                tree = tree->right;
            }
            
        }
    }
    //使用栈的非递归前序遍历
    void StackPreorderTreeWalk(){
        ListStack s;
        TreeNode *tree = root;
        while(1){
            if(tree != nullptr){
                cout<<tree->key<<" ";
                if(tree->right != nullptr)
                    s.push(tree->right);
                tree = tree->left;
            }
            else{
                if(s.IsEmpty() == 1)
                    break;
                tree = s.pop();
            }
        }
    }
    //使用栈的非递归后序遍历
    void StackPostorderTreeWalk(){
        ListStack s;
        TreeNode *tree = root;
        s.push(tree);
        TreeNode *pre = nullptr;
        while(s.IsEmpty() == 0){
            tree = s.GetTop();
            if((tree->right == nullptr and tree->left == nullptr)
               or (pre != nullptr and (pre == tree->left or pre == tree->right))){
                cout<<tree->key<<" ";
                s.pop();
                pre = tree;
            }
            else{
                if(tree->right != nullptr)
                    s.push(tree->right);
                if(tree->left != nullptr)
                    s.push(tree->left);
            }
        }
    }
    //线索二叉树中序遍历
    void ThreadedInorderTreeWalk(){
        TreeNode *tree = root;
        TreeNode *prev = nullptr;
        if(tree != nullptr){
            while (tree != nullptr) {
                if(tree->left != nullptr){
                    prev = tree->left;
                    while (prev->right != nullptr and prev->right != tree) {
                        prev = prev->right;
                    }
                    if(prev->right == nullptr){ //第一次访问此节点
                        prev->right = tree;
                        tree = tree->left;
                    }
                    else{                        //第二次访问此节点，输出
                        prev->right = nullptr;
                        cout<<tree->key<<" ";
                        tree = tree->right;
                    }
                }
                
                else{
                    cout<<tree->key<<" ";
                    tree = tree->right;
                }
            }
        }
    }
    //线索二叉树前序遍历
    void ThreadedpreorderTreeWalk(){
        TreeNode *tree = root;
        TreeNode *prev = nullptr;
        if(tree != nullptr){
            while (tree != nullptr) {
                if(tree->left != nullptr){
                    prev = tree->left;
                    while (prev->right != nullptr and prev->right != tree) {
                        prev = prev->right;
                    }
                    if(prev->right == nullptr){ //第一次访问此节点，输出
                        cout<<tree->key<<" ";
                        prev->right = tree;
                        tree = tree->left;
                    }
                    else{                        //第二次访问此节点
                        prev->right = nullptr;
                        tree = tree->right;
                    }
                }
                
                else{
                    cout<<tree->key<<" ";
                    tree = tree->right;
                }
            }
        }
    }
    //递归查找
    TreeNode *TreeSearch(TreeNode *x, int k){ //复杂度为O(h)
        if(x == nullptr or x->key == k)
            return x;
        else{
            if(x->key < k)
                return TreeSearch(x->right, k);
            else
                return TreeSearch(x->left, k);
        }
    }
    //非递归查找
    TreeNode *IterativeTreeSearch(int k){
        TreeNode *tree = root;
        while (tree != nullptr and tree->key != k) {
            if(tree->key < k)
                tree = tree->right;
            else
                tree = tree->left;
        }
        return tree;
    }
    //非递归最大关键字元素
    TreeNode *TreeMaxium(TreeNode *x){
        TreeNode *tree = x;
        while(tree->right != nullptr){
            tree = tree->right;
        }
        return tree;
    }
    //非递归最小关键字元素
    TreeNode *TreeMinimum(TreeNode *x){
        TreeNode *tree = x;
        while(tree->left != nullptr){
            tree = tree->left;
        }
        return tree;
    }
    //递归最大关键字元素
    TreeNode *RecursiveTreeMaxium(TreeNode *x){
        if(x->right != nullptr)
            return RecursiveTreeMaxium(x->right);
        else
            return x;
    }
    //递归最小关键字元素
    TreeNode *RecursiveTreeMinimum(TreeNode *x){
        if(x->left != nullptr)
            return RecursiveTreeMinimum(x->left);
        else
            return x;
    }
    //中序遍历后继
    TreeNode *TreeSuccessor(TreeNode *x){
        TreeNode *tree = x->right;
        if(tree != nullptr){
            return TreeMinimum(tree);
        }
        TreeNode * parent = x->p;
        while(parent->left != x and parent != nullptr){
            x = parent;
            parent = parent->p;
        }
        return parent;
    }
    //中序遍历前趋
    TreeNode *TreePredecessor(TreeNode *x){
        TreeNode *tree = x->left;
        if(tree != nullptr){
            return TreeMaxium(tree);
        }
        TreeNode * parent = x->p;
        while(parent->right != x and parent != nullptr){
            x = parent;
            parent = parent->p;
        }
        return parent;
    }
    //非递归插入
    void TreeInsert(TreeNode *z){
        n++;
        TreeNode *y = nullptr;
        TreeNode *x = root;
        while(x != nullptr){
            y = x;
            if(x->key < z->key)
                x = x->right;
            else
                x = x->left;
        }
        z->p = y;
        if(y == nullptr)
            root = z;
        else{
            if(y->key < z->key)
                y->right = z;
            else
                y->left = z;
        }
    }
    //删除
    void TreeDelete(TreeNode *z){
        if(z->left == nullptr and z->right == nullptr){
            TreeNode *temp = z->p;
            if(temp == nullptr)
                root = nullptr;
            else if(temp->left == z)
                temp->left = nullptr;
            else
                temp->right = nullptr;
        }
        else if(z->left != nullptr and z->right != nullptr){
            int rand = arc4random_uniform(2);
            TreeNode *temp = nullptr;
            if(rand == 1)
                temp = TreeSuccessor(z);
            else
                temp = TreePredecessor(z);
            TreeDelete(temp);
            z->Copy(temp);
        }
        else{
            if(z->left != nullptr){
                TreeNode *temp = z->p;
                if(temp == nullptr)
                    root = z->left;
                else if(temp->left == z)
                    temp->left = z->left;
                else
                    temp->right = z->left;
                z->left->p = temp;
            }
            else{
                TreeNode *temp = z->p;
                if(temp == nullptr)
                    root = z->right;
                else if(temp->left == z)
                    temp->left = z->right;
                else
                    temp->right = z->right;
                z->right->p = temp;
            }
        }
    }
    //递归插入
    void RecursiveInsert(TreeNode *x, TreeNode *z){
        if(x == nullptr)
            root = z;
        else if(x->key == z->key){
            int rand = arc4random_uniform(2);
            if(rand == 0){
                if(x->right == nullptr){
                    x->right = z;
                    z->p = x;
                }
                else{
                    RecursiveInsert(x->right, z);
                }
            }
            else{
                if(x->left == nullptr){
                    x->left = z;
                    z->p = x;
                }
                else
                    RecursiveInsert(x->left, z);
            }
        }
        else if(x->key < z->key){
            if(x->right == nullptr){
                x->right = z;
                z->p = x;
            }
            else
                RecursiveInsert(x->right, z);
        }
        else{
            if(x->left == nullptr){
                x->left = z;
                z->p = x;
            }
            else
                RecursiveInsert(x->left, z);
        }
    }
    ///////////////////////////////////////////////////////持久树
    //持久树插入 思考题13-1
    BinaryTree *PersistentTreeInsert(TreeNode *z){
        ListStack *s = new ListStack;
        TreeNode *tree = root;
        while(tree != nullptr){
            s->push(tree);
            if(tree->key < z->key)
                tree = tree->right;
            else
                tree = tree->left;
        }
        TreeNode *temp = z;
        BinaryTree *t = new BinaryTree;
        while(s->IsEmpty() == 0){
            tree = s->pop();
            temp = new TreeNode(tree->key);
            if(z->key <= temp->key){
                temp->left = z;
                temp->right = tree->right;
            }
            else{
                temp->right = z;
                temp->left = tree->left;
            }
            z = temp;
        }
        t->n  = n + 1;
        t->root = temp;
        return t;
        
    }
    //左旋
    void LeftRotate(TreeNode *x){
        if(x->right != nullptr){
            TreeNode *temp = x->right;
            x->hx = max(GetHigh(x->left), GetHigh(temp->left)) + 1;
            temp->hx = max(GetHigh(temp->right), GetHigh(x)) + 1;
            x->right = temp->left;
            if(temp->left != nullptr)
                temp->left->p = x;
            temp->left = x;
            temp->p = x->p;
            if(x->p == nullptr){
                root = temp;
                //nil->left = root;
                //nil->right = root;
            }
            else if(x->p->left == x)
                x->p->left = temp;
            else
                x->p->right = temp;
            
            x->p = temp;
        }
        else{
            cout<<"右子树为空，左旋失败"<<endl;
            exit(0);
        }
    }
    //右旋
    void RightRotate(TreeNode *x){
        if(x->left != nullptr){
            TreeNode *temp = x->left;
            x->hx = max(GetHigh(x->right), GetHigh(temp->right)) + 1;
            temp->hx = max(GetHigh(temp->left), GetHigh(x)) + 1;
            x->left = temp->right;
            if(temp->right != nullptr)
                temp->right->p = x;
            temp->right = x;
            temp->p = x->p;
            if(x->p == nullptr){
                root = temp;
                //nil->left = root;
                //nil->right = root;
            }
            else if(x->p->left == x)
                x->p->left = temp;
            else
                x->p->right = temp;
            
            x->p = temp;
        }
        else{
            cout<<"左子树为空，右旋失败"<<endl;
            exit(0);
        }
    }
    ///////////////////////////////////////////////////////AVL树 思考题 13-3
    //AVL树平衡
    void Balance(TreeNode *x){
        TreeNode *temp = x;
        if(GetHigh(x->left) + 2 == GetHigh(x->right)){
            temp = x->right;
            if(GetHigh(temp->right) < GetHigh(temp->left)){
                RightRotate(temp);
                LeftRotate(temp->p->p);
            }
            else{
                LeftRotate(temp->p);
            }
        }
        else if(GetHigh(x->right) + 2 == GetHigh(x->left)){
            temp = x->left;
            if(GetHigh(temp->right) < GetHigh(temp->left)){
                RightRotate(temp->p);
            }
            else{
                LeftRotate(temp);
                RightRotate(temp->p->p);
            }
        }
        else{
            x->hx = max(GetHigh(x->left), GetHigh(x->right)) + 1;
        }
    }
    //得到高度
    int GetHigh(TreeNode *x){
        if(x == nullptr)
            return -1;
        else
            return x->hx;
    }
    //avl树递归插入
    void AVLInsert(TreeNode *x, TreeNode *z){
        if(x == nullptr){
            root = z;
        }
        else if(x->key <= z->key){
            if(x->right == nullptr){
                x->right = z;
                x->hx = max(GetHigh(x->left), GetHigh(x->right)) + 1;
                z->p = x;
            }
            else{
                AVLInsert(x->right, z);
                Balance(x);
            }
        }
        else{
            if(x->left == nullptr){
                x->left = z;
                x->hx = max(GetHigh(x->left), GetHigh(x->right)) + 1;
                z->p = x;
            }
            else{
                AVLInsert(x->left, z);
                Balance(x);
            }
        }
        

        
    }
    //avl删除
    void AVLDelete(TreeNode *z){
        if(z->left == nullptr and z->right == nullptr){
            TreeNode *temp = z->p;
            if(temp == nullptr)
                root = nullptr;
            else if(temp->left == z)
                temp->left = nullptr;
            else
                temp->right = nullptr;
            while(temp != nullptr){
                Balance(temp);
                temp = temp->p;
            }
        }
        else if(z->left != nullptr and z->right != nullptr){
            int rand = arc4random_uniform(2);
            TreeNode *temp = nullptr;
            if(rand == 1)
                temp = TreeSuccessor(z);
            else
                temp = TreePredecessor(z);
            AVLDelete(temp);
            z->Copy(temp);
        }
        else{
            if(z->left != nullptr){
                TreeNode *temp = z->p;
                if(temp == nullptr)
                    root = z->left;
                else if(temp->left == z)
                    temp->left = z->left;
                else
                    temp->right = z->left;
                z->left->p = temp;
                while(temp != nullptr){
                    Balance(temp);
                    temp = temp->p;
                }
            }
            else{
                TreeNode *temp = z->p;
                if(temp == nullptr)
                    root = z->right;
                else if(temp->left == z)
                    temp->left = z->right;
                else
                    temp->right = z->right;
                z->right->p = temp;
                while(temp != nullptr){
                    Balance(temp);
                    temp = temp->p;
                }
                
            }
        }
    }
    ///////////////////////////////////////////////////////Treap树
    //treap 树 思考题 13-4
    //树堆调整
    void InsertFixup(TreeNode *z){
        while(z != root and z->value < z->p->value){
            if(z->p->left == z){
                RightRotate(z->p);
            }
            else{
                LeftRotate(z->p);
            }
        }
    }
    //树堆插入
    void TreapInsert(TreeNode *z){
        n++;
        TreeNode *y = nullptr;
        TreeNode *x = root;
        while(x != nullptr){
            y = x;
            if(x->key < z->key)
                x = x->right;
            else
                x = x->left;
        }
        z->p = y;
        if(y == nullptr)
            root = z;
        else{
            if(y->key < z->key)
                y->right = z;
            else
                y->left = z;
        }
        InsertFixup(z);
    }
    ///////////////////////////////////////////////////////Treap树
    
    //非递归深度常数空间遍历 10.4-5练习
    void PrintOutNotRecurssion1(){
        TreeNode *prev = nullptr;
        TreeNode *node = root;
        while(node != nullptr){
            if(prev == node->p){
                cout<<node->key<<" ";
                prev = node;
                if(node->left != nullptr)
                    node = node->left;
                else{
                    if(node->right != nullptr)
                        node = node->right;
                    else
                        node = node->p;
                }
            }
            else if(prev == node->left && node->right != nullptr){
                prev = node;
                node = node->right;
            }
            else{
                prev = node;
                node = node->p;
            }
        }
    }
};
//基数树 思考题12-2
class RadixTree{
public:
    TreeNode *root;
    int n;
    RadixTree(){
        root = new TreeNode(0);
        n = 0;
    }
    void Insert(string a){
        int i = 0;
        TreeNode *temp = root;
        while(i < a.length()){
            if(a[i] == '0'){
                if(temp->left == nullptr){
                    TreeNode *node;
                    if(i == a.length() - 1)
                        node = new TreeNode(1);//有关键字
                    else
                        node = new TreeNode(0);//无关键字
                    temp->left = node;
                    temp = temp->left;
                }
                else{
                    temp = temp->left;
                    if(i == a.length() - 1)
                       temp->key = 1;
                }
            }
            else{
                if(temp->right == nullptr){
                    TreeNode *node;
                    if(i == a.length() - 1)
                        node = new TreeNode(1);//有关键字
                    else
                        node = new TreeNode(0);//无关键字
                    temp->right = node;
                    temp = temp->right;
                }
                else{
                    temp = temp->right;
                    if(i == a.length() - 1)
                        temp->key = 1;
                }
            }
            
            i++;
        }
        
    }
    void Sort(string s, TreeNode *t){
        if(t->key == 1)
            cout<<s<<endl;
        if(t->left != nullptr)
            Sort(s + '0', t->left);
        if(t->right != nullptr)
            Sort(s + '1', t->right);
        
    }
};
//孩子兄弟二叉树 10.4-4练习
class TreeNode1{
public:
    TreeNode1 * p;
    TreeNode1 * LeftChild;
    TreeNode1 * RightSibling;
    int key;
    TreeNode1(int k){
        key = k;
        p = nullptr;
        LeftChild = nullptr;
        RightSibling = nullptr;
    }
};
class NBranchTree{
public:
    TreeNode1 *root;
    int n;
    NBranchTree(){
        root = nullptr;
        n = 0;
    }
    
    void PrintOut(TreeNode1 *t){
        if(t != nullptr)
            cout<<t->key<<" ";
        if(t->LeftChild != nullptr)
            PrintOut(t->LeftChild);
        if(t->RightSibling != nullptr)
            PrintOut(t->RightSibling);
    }
    
};
//孩子兄弟二叉树两个指针 10.4-6
class TreeNode2{
    TreeNode2 *LeftChild;
    TreeNode2 *Next;
    bool flag;
    int key;
    TreeNode2(int k){
        key = k;
        LeftChild = nullptr;
        Next = nullptr;
        flag = 0;
    }
    
    TreeNode2 *FindParent(TreeNode2 *t){
        TreeNode2 *node = t;
        while(node->flag != 1)
            node = node->Next;
        return node->Next;
    }
};



int Rand(int *a){
    int b;
    do{
        b = arc4random_uniform(100);
    }while(a[b] == 0);
    return b;
}

int main(int argc, const char * argv[]) {
    int ran[100];
    for(int i = 0 ; i < 100; i++){
        ran[i] = 1;
    }
    BinaryTree *b = new BinaryTree();
    TreeNode **a = new TreeNode*[50];
    for(int i = 0 ; i < 10; i++){
        a[i] = new TreeNode(arc4random_uniform(100));
        a[i]->value = Rand(ran);
        b->TreapInsert(a[i]);
    }
    b->InorderTreeWalk(b->root);
  
    return 0;
}
