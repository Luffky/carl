//
//  Function.cpp
//  REDBLACK-TREE
//
//  Created by 伏开宇 on 2017/3/20.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include "Function.hpp"
RBTreeNode* RBTree::nil = new RBTreeNode(-1,1); //静态成员nil
RBTree::RBTree(){
    root = nil;
    n = 0;
    bh = 0;
}
RBTree::RBTree(RBTreeNode *x){
    n = 0;
    bh = 1;
    root = x;
    x->color = 1;
    x->p = nil;
    x->left = nil;
    x->right = nil;
    //nil->left = root;
    //nil->right = root;
}
void RBTree::SetRoot(RBTreeNode *x){
    root = x;
    bh = 1;
    x->color = 1;
    x->p = nil;
    x->left = nil;
    x->right = nil;
    //nil->left = root;
    //nil->right = root;
}
int RBTree::GetBh(RBTreeNode *x){
    RBTreeNode *temp = x;
    int i = 0;
    while(temp != nil){
        temp = temp->left;
        if(temp->color == 1)
            i++;
    }
    return i;
}
void RBTree::InorderTreeWalk(RBTreeNode *x){
    if(x != nil){
        InorderTreeWalk(x->left);
        cout<<x->key<<" ";
        InorderTreeWalk(x->right);
    }
}
RBTreeNode* RBTree::RBTreeMinimum(RBTreeNode *x){
    RBTreeNode *tree = x;
    while(tree->left != nil){
        tree = tree->left;
    }
    return tree;
}
RBTreeNode* RBTree::RBTreeSuccessor(RBTreeNode *x){
    RBTreeNode *tree = x->right;
    if(tree != nil){
        return RBTreeMinimum(tree);
    }
    RBTreeNode * parent = x->p;
    while(parent->left != x and parent != nil){
        x = parent;
        parent = parent->p;
    }
    return parent;
}
void RBTree::LeftRotate(RBTreeNode *x){
    if(x->right != nil){
        RBTreeNode *temp = x->right;
        temp->size = x->size;
        x->size = x->left->size + temp->left->size + 1;
        x->right = temp->left;
        if(temp->left != nil)
            temp->left->p = x;
        temp->left = x;
        temp->p = x->p;
        if(x->p == nil){
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
void RBTree::RightRotate(RBTreeNode *x){
    if(x->left != nil){
        RBTreeNode *temp = x->left;
        temp->size = x->size;
        x->size = temp->right->size + x->right->size + 1;
        x->left = temp->right;
        if(temp->right != nil)
            temp->right->p = x;
        temp->right = x;
        temp->p = x->p;
        if(x->p == nil){
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
void RBTree::RBTreeInsert(RBTreeNode *z){
    n++;
    RBTreeNode *y = nil;
    RBTreeNode *x = root;
    while(x != nil){
        x->size++;
        y = x;
        if(x->key < z->key)
            x = x->right;
        else
            x = x->left;
    }
    z->p = y;
    if(y == nil)
        SetRoot(z);
    else{
        if(y->key < z->key)
            y->right = z;
        else
            y->left = z;
        z->left = nil;
        z->right = nil;
        z->color = 0;
        RBInsertFixup(z);
    }
}
void RBTree::RBInsertFixup(RBTreeNode *x){
    while(x->p->color == 0){//如果x的父亲是红色，则迭代
        if(x->p == x->p->p->left){ //如果x的父亲是左孩子
            RBTreeNode *y = x->p->p->right; //x的叔叔
            if(y->color == 0){  //x的叔叔如果是红色
                y->color = 1;
                x->p->color = 1;  //将x的父亲和叔叔都置为黑色
                x = x->p->p;
                x->color = 0; //x的爷爷置为红色，以其爷爷为当前节点再次迭代
                x->bh++;
            }
            else{//x的叔叔如果是黑色
                if(x == x->p->left){ //如果x是左孩子
                    x = x->p; //当前节点变为x的父亲
                    RightRotate(x); //右旋
                    x->p->color = 1;//父亲置为黑色
                    x->p->p->color = 0;//爷爷置为红色
                    RightRotate(x->p->p);//右旋爷爷
                }
                else{//如果x是右孩子
                    x = x->p; //当前节点变为x的父亲
                    LeftRotate(x); //左旋
                    x->p->color = 1;//父亲置为黑色
                    x->p->p->color = 0;//爷爷置为红色
                    RightRotate(x->p->p);//右旋爷爷
                }
            }
        }
        else{ //x的父亲是右孩子
            RBTreeNode *y = x->p->p->left; //x的叔叔
            if(y->color == 0){ //同上
                y->color = 1;
                x->p->color = 1;  //将x的父亲和叔叔都置为黑色
                x = x->p->p;
                x->color = 0; //x的爷爷置为红色，以其爷爷为当前节点再次迭代
                x->bh++;
            }
            else{
                if(x == x->p->left){ //如果x是左孩子
                    x = x->p; //当前节点变为x的父亲
                    RightRotate(x); //右旋
                    x->p->color = 1;//父亲置为黑色
                    x->p->p->color = 0;//爷爷置为红色
                    LeftRotate(x->p->p);//左旋爷爷
                }
                else{//如果x是右孩子
                    x = x->p; //当前节点变为x的父亲
                    LeftRotate(x); //左旋
                    x->p->color = 1;//父亲置为黑色
                    x->p->p->color = 0;//爷爷置为红色
                    LeftRotate(x->p->p);//左旋爷爷
                }
            }
            
        }
    }
    if(root->color == 0){
        root->color = 1;
        bh++;
    }
}
void RBTree::RBTreeDelete(RBTreeNode *z){
    RBTreeNode *y = nil;
    RBTreeNode *x = nil;
    int flag = 0;//flag为1表示不进行回复红黑性质
    if(z->left == nil or z->right == nil){
        y = z;
        RBTreeNode *temp = z->p;
        if(y->left != nil)
            x = y->left;
        else
            x = y->right;
        x->p = temp;
        if(temp == nil){
            root = x;
        }
        else if(temp->left == y)
            temp->left = x;
        else
            temp->right = x;
        while(temp != nil){
            temp->size--;
            temp = temp->p;
        }
    }
    else {
        y = RBTreeSuccessor(z);
        RBTreeDelete(y);
        z->Copy(y);
        flag = 1;
    }
    
    if(flag == 0 and y->color == 1)
        RBDeleteFixup(x);
    
}
void RBTree::RBDeleteFixup(RBTreeNode *x){
    while(x != root and x->color == 1){
        if(x->p->left == x){ //如果x是左子树
            RBTreeNode *w = x->p->right;  //设置x的兄弟
            //第一阶段
            if(w->color == 0){ //如果x的兄弟是红色
                w->color = 1;
                x->p->color = 0;
                LeftRotate(x->p); //左旋父亲
                w = x->p->right; //设置新的兄弟，此兄弟必为黑色，所以根据兄弟的孩子着色情况进入第二或者第三或者第四阶段
            }
            //第二阶段
            if(w->left->color == 1 and w->right->color == 1){//如果兄弟的两个孩子都是黑色
                w->color = 0;//置兄弟为红色，且不违反性质4,消除掉了x的两重黑色
                x->p->bh = x->bh;
                x = x->p;//开始下一循环，若从第一阶段进入此阶段，则因为父亲必为红色所以跳出循环，直接在最后置父亲为黑色，程序结束，否则x则上升，以x父亲为当前节点进入下一个循环。
                if(x == root and x->color == 1)
                    bh--;
            }
            else{
                //第三阶段
                if(w->right->color == 1){ //如果兄弟右孩子是黑色
                    w->color = 0;
                    w->left->color = 1; //兄弟左孩子置为黑色
                    RightRotate(w); //右旋兄弟
                    w = x->p->right; //设置新的兄弟，此兄弟必为黑色,且此兄弟的右孩子必为红色，进入第四阶段
                }
                //第四阶段 //如果兄弟右孩子是红色则跳过上一阶段，直接到达该阶段
                w->color = x->p->color; //置兄弟为父亲同色
                x->p->color = 1;
                w->right->color = 1;
                LeftRotate(x->p); //左旋父亲
                x->p->bh = x->bh + 1;
                x->p->p->bh = x->p->bh + 1;
                x = root; //跳出循环
            }
        }
        else{//如果x是右子树
            RBTreeNode *w = x->p->left; //设置x的兄弟
            //第一阶段
            if(w == 0){ //如果x的兄弟是红色
                w->color = 1;
                x->p->color = 0;
                RightRotate(x->p);//右旋父亲
                w = x->p->left; //设置新的兄弟，此兄弟必为黑色，所以进入下一阶段
            }
            //第二阶段
            if(w->left->color == 1 and w->right->color == 1){//如果兄弟的两个孩子都是黑色
                w->color = 0;//置兄弟为红色，且不违反性质4
                x->p->bh = x->bh;
                x = x->p;//开始下一循环，若从第一阶段进入此阶段，则因为父亲必为红色所以跳出循环，直接在最后置父亲为黑色，程序结束，否则x则上升，以x父亲为当前节点进入下一个循环。
                if(x == root and x->color == 1)
                    bh--;
            }
            else{
                //第三阶段
                if(w->left->color == 1){ //如果兄弟左孩子是黑色
                    w->color = 0;
                    w->right->color = 1; //兄弟右孩子置为黑色
                    LeftRotate(w); //右旋兄弟
                    w = x->p->left; //设置新的兄弟，此兄弟必为黑色，进入第四阶段
                }
                //第四阶段
                w->color = x->p->color;
                x->p->color = 1;
                w->left->color = 1;
                RightRotate(x->p);
                x = root;
            }
        }
    }
    x->color = 1;
}
RBTreeNode* RBTree::LocateMaxNodeOfBh(int b){
    RBTreeNode *r = root;
    int h = bh;
    while(h > b){
        if(r->right != nil){
            r = r->right;
            if(r->color == 1)
                h--;
        }
        else{
            cout<<"未找到黑高度为"<<b<<"的节点"<<endl;
            return nullptr;
        }
    }
    return r;
}
RBTreeNode* RBTree::LocateMinNodeOfBh(int b){
    RBTreeNode *r = root;
    int h = bh;
    while(h > b){
        if(r->left != nil){
            r = r->left;
            if(r->color == 1)
                h--;
        }
        else{
            cout<<"未找到黑高度为"<<b<<"的节点"<<endl;
            return nullptr;
        }
    }
    return r;
}
void RBTree::RBJoin(RBTreeNode *x, RBTree *t2,int flag){
    RBTreeNode *temp;
    if(flag == 0){//假设t1所有元素小于等于x小于等于t2所有元素
        temp = LocateMaxNodeOfBh(t2->bh);
        x->left = temp;
        x->right = t2->root;
        temp->p = x;
        t2->root->p = x;
        x->p = temp->p;
        x->color = 0; //置x为红色
        if(bh == t2->bh)
            root = x;
        else
            temp->p->right = x;
        RBInsertFixup(x);
    }
    else{//假设t1所有元素大于等于x大于等于t2所有元素
        temp = LocateMinNodeOfBh(t2->bh);
        x->right = temp;
        x->left = t2->root;
        x->p = temp->p;
        temp->p = x;
        t2->root->p = x;
        x->color = 0; //置x为红色
        if(bh == t2->bh)
            root = x;
        else
            temp->p->left = x;
        RBInsertFixup(x);
    }
}
RBTreeNode* RBTree::Select(RBTreeNode* t, int i){
    if(t == nil){
        return nil;
    }
    int r = t->left->size + 1;
    if(r == i)
        return t;
    else if(r < i){
        i = i - r;
        return Select(t->right, i);
    }
    else{
        return Select(t->left, i);
    }
    
}
RBTreeNode* RBTree::IteSelect(int i){
    RBTreeNode* t = root;
    int r = root->left->size + 1;
    while(i != r){
        if(r < i){
            i = i - r;
            t = t->right;
        }
        else{
            t = t->left;
        }
        r = t->left->size + 1;
    }
    return t;
}
int RBTree::Rank(RBTreeNode* t){
    int r = t->left->size + 1;
    while(t->p != nil){
        if(t == t->p->right){
            r += t->p->left->size + 1;
        }
        t = t->p;
    }
    return r;
}
int RBTree::KeyRank(RBTreeNode* t, int k){
    if(t == nil){
        return INT32_MIN;
    }
    int r = t->left->size + 1;
    if(t->key == k)
        return r;
    else if(t->key < k){
        return r + KeyRank(t->right, k);
    }
    else{
        return KeyRank(t->left, k);
    }
    
}
void RBTree::Enumerate(int a, int b){
    RBTreeNode* temp = root;
    RBTreeNode* prev = nil;
    while(temp != nil){
        prev = temp;
        if(temp->key == a)
            break;
        else if(temp->key < a)
            temp = temp->right;
        else
            temp = temp->left;
    }
    //如果n不在树里
    if(temp != nil){
        int n = Rank(temp);
        RBTreeNode* y = Select(root, n++);
        while(y->key <= b and y!=nil){
            cout<<y->key<<" ";
            y = Select(root, n++);
        }
    }
    else{
        RBTreeNode* t = new RBTreeNode(a,-1);
        RBTreeInsert(t);
        int n = Rank(t) + 1;
        RBTreeNode* y = Select(root, n++);
        while(y->key <= b and y!=nil){
            cout<<y->key<<" ";
            y = Select(root, n++);
        }
        RBTreeDelete(t);
        
    }
    
}
