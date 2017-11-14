//
//  Function.cpp
//  INTERVALTREE
//
//  Created by 伏开宇 on 2017/3/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//
#include "Function.hpp"
Int* zero = new Int(INT32_MIN,INT32_MIN);
IntervalTreeNode* IntervalTree::nil = new IntervalTreeNode(zero,1); //静态成员nil
IntervalTree::IntervalTree(){
    root = nil;
    root->left = nil;
    root->right = nil;
    n = 0;
    bh = 0;
}
IntervalTree::IntervalTree(IntervalTreeNode *x){
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
bool IntervalTree::Overlap(IntervalTreeNode*t, Int* i){
    if(i->low <= t->interval->high and t->interval->low <= i->high)//重叠,若为开区间，则这儿改为 i->low < t->interval->high and t->interval->low <  i->high.
        return true;
    else
        return false;
}
bool IntervalTree::ExactOverlap(IntervalTreeNode*t, Int* i){
    if(i->low == t->interval->low and t->interval->high == i->high)
        return true;
    else
        return false;
}
IntervalTreeNode* IntervalTree::IntervalSearch(Int* i){
    IntervalTreeNode* t = root;
    while(t != nil and !Overlap(t, i)){
        if(t->left != nil and t->left->Max >= i->low) //若为开区间则这儿改为 t->left->max > i->low
            t = t->left;
        else
            t = t->right;
    }
    return t;
}
void IntervalTree::IntervalSearchAll(IntervalTreeNode* t, Int* i, int* n){
    if(Overlap(t, i)){
        cout<<"("<<t->interval->low<<","<<t->interval->high<<")";
        (*n)++;
    }
    if(t->left != nil and t->left->Max >= i->low)
        IntervalSearchAll(t->left, i, n);
    if(t->right != nil and t->key <= i->high)
        IntervalSearchAll(t->right, i, n);
}
IntervalTreeNode* IntervalTree::IntervalMiniLowSearch(IntervalTreeNode*t, Int* i){
    if(t->left != nil and t->left->Max >= i->low){
        IntervalTreeNode*x = IntervalMiniLowSearch(t->left, i);
        if(x != nil)
            return x;
        else if(Overlap(t, i))
            return t;
        else
            return nil;
    }
    else{
        if(Overlap(t, i))
            return t;
        else{
            if(t->right != nil)
                return IntervalMiniLowSearch(t->right, i);
            else
                return nil;
        }
    }

}
IntervalTreeNode* IntervalTree::IntervalExactSearch(Int* i){
    IntervalTreeNode* t = root;
    while(t != nil and !ExactOverlap(t, i)){
        if(t->key < i->low)
            t = t->right;
        else
            t = t->left;
    }
    return t;
}
void IntervalTree::SetRoot(IntervalTreeNode *x){
    root = x;
    bh = 1;
    x->color = 1;
    x->p = nil;
    x->left = nil;
    x->right = nil;
    //nil->left = root;
    //nil->right = root;
}
void IntervalTree::InorderTreeWalk(IntervalTreeNode *x){
    if(x != nil){
        InorderTreeWalk(x->left);
        cout<<"("<<x->interval->low<<","<<x->interval->high<<")";
        InorderTreeWalk(x->right);
    }
}
IntervalTreeNode* IntervalTree::IntervalTreeMinimum(IntervalTreeNode *x){
    IntervalTreeNode *tree = x;
    while(tree->left != nil){
        tree = tree->left;
    }
    return tree;
}
IntervalTreeNode* IntervalTree::IntervalTreeSuccessor(IntervalTreeNode *x){
    IntervalTreeNode *tree = x->right;
    if(tree != nil){
        return IntervalTreeMinimum(tree);
    }
    IntervalTreeNode * parent = x->p;
    while(parent->left != x and parent != nil){
        x = parent;
        parent = parent->p;
    }
    return parent;
}
void IntervalTree::LeftRotate(IntervalTreeNode *x){
    if(x->right != nil){
        IntervalTreeNode *temp = x->right;
        x->right = temp->left;
        if(temp->left != nil)
            temp->left->p = x;
        temp->left = x;
        temp->p = x->p;
        if(x->p == nil){
            root = temp;
        }
        else if(x->p->left == x)
            x->p->left = temp;
        else
            x->p->right = temp;
        
        x->p = temp;
        //维护Max域
        temp->Max = x->Max;
        x->Max = max(x->interval->high, max(x->left->Max, x->right->Max));
    }
    else{
        cout<<"右子树为空，左旋失败"<<endl;
        exit(0);
    }
}
void IntervalTree::RightRotate(IntervalTreeNode *x){
    if(x->left != nil){
        IntervalTreeNode *temp = x->left;
        x->left = temp->right;
        if(temp->right != nil)
            temp->right->p = x;
        temp->right = x;
        temp->p = x->p;
        if(x->p == nil){
            root = temp;
        }
        else if(x->p->left == x)
            x->p->left = temp;
        else
            x->p->right = temp;
        
        x->p = temp;
        //维护Max域
        temp->Max = x->Max;
        x->Max = max(x->interval->high, max(x->left->Max, x->right->Max));
    }
    else{
        cout<<"左子树为空，右旋失败"<<endl;
        exit(0);
    }
}
void IntervalTree::IntervalTreeInsert(IntervalTreeNode *z){
    n++;
    IntervalTreeNode *y = nil;
    IntervalTreeNode *x = root;
    while(x != nil){
        y = x;
        if(z->Max > x->Max)   //自顶向下维护Max
            x->Max = z->Max;
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
        IntervalInsertFixup(z);
    }
}
void IntervalTree::IntervalInsertFixup(IntervalTreeNode *x){
    while(x->p->color == 0){//如果x的父亲是红色，则迭代
        if(x->p == x->p->p->left){ //如果x的父亲是左孩子
            IntervalTreeNode *y = x->p->p->right; //x的叔叔
            if(y->color == 0){  //x的叔叔如果是红色
                y->color = 1;
                x->p->color = 1;  //将x的父亲和叔叔都置为黑色
                x = x->p->p;
                x->color = 0; //x的爷爷置为红色，以其爷爷为当前节点再次迭代
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
            IntervalTreeNode *y = x->p->p->left; //x的叔叔
            if(y->color == 0){ //同上
                y->color = 1;
                x->p->color = 1;  //将x的父亲和叔叔都置为黑色
                x = x->p->p;
                x->color = 0; //x的爷爷置为红色，以其爷爷为当前节点再次迭代
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
void IntervalTree::IntervalTreeDelete(IntervalTreeNode *z){
    IntervalTreeNode *y = nil;
    IntervalTreeNode *x = nil;
    int flag = 0;//flag为1表示不进行回复红黑性质
    if(z->left == nil or z->right == nil){
        y = z;
        IntervalTreeNode *temp = z->p;
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
        while(temp != nil){ //自底向上维护Max
            temp->Max = max(temp->Max, max(temp->left->Max, temp->right->Max));
            temp = temp->p;
        }
        n--;
    }
    else {
        y = IntervalTreeSuccessor(z);
        IntervalTreeDelete(y);
        //不完全交换
        //z->Copy(y);
        //完全交换两个结点（包括地址）
        if(z->p != nil){
            if(z->p->left == z)
                z->p->left = y;
            else
                z->p->right = y;
        }
        else
            root = y;
        y->p = z->p;
        y->left = z->left;
        y->right = z->right;
        if(y->left != nil)
            y->left->p = y;
        if(y->right != nil)
            y->right->p = y;
        y->Max = max(y->interval->high, max(y->left->Max, y->right->Max));
        
        
        flag = 1;
    }
    if(flag == 0 and y->color == 1)
        IntervalDeleteFixup(x);
    
}
void IntervalTree::IntervalDeleteFixup(IntervalTreeNode *x){
    while(x != root and x->color == 1){
        if(x->p->left == x){ //如果x是左子树
            IntervalTreeNode *w = x->p->right;  //设置x的兄弟
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
                x = root; //跳出循环
            }
        }
        else{//如果x是右子树
            IntervalTreeNode *w = x->p->left; //设置x的兄弟
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

