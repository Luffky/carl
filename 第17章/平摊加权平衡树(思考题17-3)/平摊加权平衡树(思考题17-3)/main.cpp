//
//  main.cpp
//  平摊加权平衡树(思考题17-3)
//
//  Created by 伏开宇 on 2017/4/1.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//树节点
class TreeNode{
public:
    int key;
    int value; //树堆优先级
    int size;
    TreeNode *p;
    TreeNode *left;
    TreeNode *right;
    int hx; //结点高度
    TreeNode(int x){
        size = 1;
        value = 0;
        hx = 0;
        key = x;
        p = nullptr;
        left = nullptr;
        right = nullptr;
    }
    void Copy(TreeNode *x){
        key = x->key;
    }
};
//替罪羊树
class BinaryTree{
public:
    TreeNode *root;
    int n;
    double alpha;
    BinaryTree(double a){
        root = nullptr;
        alpha = a;
        n = 0;
    }
    //判断是否alpha平衡
    int AlphaBlance(TreeNode* a){
        int lsize = 0;
        int rsize = 0;
        if(a->left == nullptr)
            lsize = 0;
        else
            lsize = a->left->size;
        if(a->right == nullptr)
            rsize = 0;
        else
            rsize = a->right->size;
        if(lsize <= alpha * a->size and rsize <= alpha * a->size)
            return 1;
        else
            return 0;
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
            y->size++;
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
        TreeNode* High = nullptr; //APLHA平衡
        while(y != nullptr){
            if(AlphaBlance(y) == 0)
                High = y;
            y = y->p;
        }
        if(High != nullptr)
            Build(High);
    }
    //删除
    void TreeDelete(TreeNode *z){
        int flag = 0;
        TreeNode *temp = z->p;
        if(z->left == nullptr and z->right == nullptr){
            if(temp == nullptr)
                root = nullptr;
            else if(temp->left == z){
                temp->left = nullptr;
            }
            else{
                temp->right = nullptr;
            }
            while(temp != nullptr){
                temp->size--;
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
            TreeDelete(temp);
            z->Copy(temp);
            flag = 1;
        }
        else{
            if(z->left != nullptr){
                if(temp == nullptr)
                    root = z->left;
                else if(temp->left == z)
                    temp->left = z->left;
                else
                    temp->right = z->left;
                z->left->p = temp;
                while(temp != nullptr){
                    temp->size--;
                    temp = temp->p;
                }
            }
            else{
                if(temp == nullptr)
                    root = z->right;
                else if(temp->left == z)
                    temp->left = z->right;
                else
                    temp->right = z->right;
                z->right->p = temp;
                while(temp != nullptr){
                    temp->size--;
                    temp = temp->p;
                }
            }
            if(flag == 0){ //检查是否ALPHA平衡
                TreeNode* High = nullptr;
                while(temp != nullptr){
                    if(AlphaBlance(temp) == 0)
                        High = temp;
                    temp = temp->p;
                }
                if(High != nullptr)
                    Build(High);
            }
            
        }
    }
    //递归中序遍历输出
    void InorderTreeWalk(TreeNode *x, int* a, int* no){
        if(x != nullptr){
            InorderTreeWalk(x->left, a, no);
            a[(*no)++] = x->key;
            InorderTreeWalk(x->right, a, no);
        }
    }
    void Delete(TreeNode* n){
        if(n != nullptr){
            if(n->left != nullptr)
                Delete(n->left);
            if(n->right != nullptr)
                Delete(n->right);
        }
    }
    //重建平衡树
    void BuildBalancedTree(int*a, TreeNode* x, int s, int t){
        if(s > t)
            return;
        int m = (t + s) / 2;
        //更新当前结点数据
        x->key = a[m];
        x->size = t - s + 1;
        //为当前子树生成儿子
        if(s < m){
            TreeNode* left = new TreeNode(-1);
            x->left = left;
            left->p = x;
        }
        if(t > m){
            TreeNode* right = new TreeNode(-1);
            x->right = right;
            right->p = x;
        }
        BuildBalancedTree(a, x->left, s, m - 1);
        BuildBalancedTree(a, x->right, m + 1, t);
        
    }
    void Build(TreeNode* x){
        int t = x->size - 1;
        int s = 0;
        int* a = new int[t - s + 1];
        int no = 0;
        InorderTreeWalk(x, a, &no);
        Delete(x->left);
        Delete(x->right);
        BuildBalancedTree(a, x, s, t);
    }
};
int main(int argc, const char * argv[]) {
    int n = 10;
    BinaryTree* b = new BinaryTree(0.7);//ALPHA平衡
    for(int i = 0; i < n; i++){
        int k = arc4random_uniform(20);
        TreeNode* temp = new TreeNode(k);
        b->TreeInsert(temp);
    }
    b->InorderTreeWalk(b->root);
    
    cout<<endl;
    return 0;
}
