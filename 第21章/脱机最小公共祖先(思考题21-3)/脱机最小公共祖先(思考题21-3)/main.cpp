//
//  main.cpp
//  脱机最小公共祖先(思考题21-3)
//
//  Created by 伏开宇 on 2017/4/11.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
#define num 5
#define NumNode 8
class TreeNode;
class Node;
class P{//公共祖先集合
public:
    Node* u;
    Node* v;
    TreeNode* ancestor;
    P(Node* u, Node* v){
        this->u = u;
        this->v = v;
        ancestor = nullptr;
    }
};
P** pp = new P*[num];
class Node{
public:
    TreeNode* t;//指向代表的结点
    int color;//着色
    Node* ancestor;
    Node* p;
    int rank;
    Node(TreeNode* k){
        t = k;
        p = nullptr;
        rank = -1;
        color = 0;//0代表白色，1代表黑色
        ancestor = nullptr;
    }
    void MakeSet(){
        p = this;
        rank = 0;
    }
    static Node* FindSet(Node* x){
        if(x != x->p)
            x->p = FindSet(x->p);
        return x->p;
    }
    //FindSet 非递归方法 练习21.3-2
    static void FindSetNoRecursive(Node* x){
        Node* y = x;
        while(x != x->p)
            x = x->p;
        while(y != x){
            Node* z = y->p;
            y->p = x;
            y = z;
        }
    }
    static void Union(Node* x, Node* y){
        Node* r1 = FindSet(x);
        Node* r2 = FindSet(y);
        if(r1->rank < r2->rank){
            r1->p = r2;
        }
        else{
            r2->p = r1;
            if(r1->rank == r2->rank){
                r1->rank++;
            }
        }
    }
};
class TreeNode{
public:
    int key;
    int d;
    TreeNode* p;
    TreeNode* child;
    TreeNode* sibling;
    Node* N;//指向不相交集合中代表此结点的元素
    TreeNode(int k){
        key = k;
        d = 0;
        p = nullptr;
        child = nullptr;
        sibling = nullptr;
        N = nullptr;
    }
    void CreateNode(){ //生成代表本结点的不相交集合元素
        Node* n = new Node(this);
        N = n;
    }
};
class Tree{
public:
    TreeNode* root;
    Tree(){
        root = nullptr;
    }
};
void LCA(Node* u, TreeNode** t){
    u->MakeSet();
    Node::FindSet(u)->ancestor = u;
    TreeNode* v = u->t->child;
    for(int i = 0; i < u->t->d; i++){
        LCA(v->N, t); //深度优先搜索
        Node::Union(u, v->N); //和儿子并入一个集合
        Node::FindSet(u)->ancestor = u; //该集合目前所有结点的最小祖先均为当前结点
        v = v->sibling;
    }
    //输出全部共同祖先对
    u->color = 1;
    for(int i = 0 ; i < NumNode; i++){
        if(t[i]->N->color == 1)
            cout<<u->t->key<<"和"<<t[i]->key<<"共同祖先为"<<Node::FindSet(t[i]->N)->ancestor->t->key<<endl;
    }
    //输出选定共同祖先对
//    for(int i = 0 ; i < num; i++){
//        if(pp[i]->u == u){
//            Node* v = pp[i]->v;
//            if(v->color == 1)
//                pp[i]->ancestor = Node::FindSet(v)->ancestor->t;
//            else{
//                Node* temp = pp[i]->u;
//                pp[i]->u = v;
//                pp[i]->v = temp;
//            }
//        }
//    }
}


int main(int argc, const char * argv[]) {
    TreeNode** t = new TreeNode*[8];
    for(int i = 0 ; i < 8; i++){
        t[i] = new TreeNode(i);
        t[i]->CreateNode();
    }
    Tree* tree = new Tree();
    pp[0] = new P(t[0]->N, t[1]->N);
    pp[1] = new P(t[1]->N, t[6]->N);
    pp[2] = new P(t[3]->N, t[4]->N);
    pp[3] = new P(t[5]->N, t[2]->N);
    pp[4] = new P(t[5]->N, t[7]->N);
    tree->root = t[0];
    t[0]->d = 3;
    t[1]->d = 1;
    t[2]->d = 0;
    t[3]->d = 0;
    t[4]->d = 0;
    t[5]->d = 1;
    t[6]->d = 2;
    t[7]->d = 0;
    t[0]->child = t[1];
    t[1]->child = t[5];
    t[5]->child = t[4];
    t[6]->child = t[3];
    t[1]->sibling = t[2];
    t[2]->sibling = t[6];
    t[3]->sibling = t[7];
    LCA(tree->root->N, t);
//    for(int i = 0 ; i < num; i++){
//        cout<<pp[i]->ancestor->key<<endl;
//    }
//    cout<<endl;
    return 0;
}
