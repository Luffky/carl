//
//  main.cpp
//  脱机最小值(思考题21-1)
//
//  Created by 伏开宇 on 2017/4/11.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//不相交集合森林
class Node{
public:
    int key;
    Node* p;
    int rank;
    Node(int x){
        key = x;
        p = nullptr;
        rank = -1;
    }
    void MakeSet(){
        p = this;
        rank = 0;
    }
    static Node* FindSet(Node* x){
        if(x->p->rank != -1 and x->p != x){
            x->p = FindSet(x->p);
            return x->p;
        }
        else
            return x;
    }
    static void Union(Node* x, Node* y, Node* j){
        Node* r1 = FindSet(x);
        Node* r2 = FindSet(y);
        if(r1->rank < r2->rank){
            r2->p = j;    //根结点指向集合结点
            j->p = r2;    //集合结点指向根结点
            r1->p = r2;
        }
        else{
            r1->p = j;
            j->p = r1;
            r2->p = r1;
            if(r1->rank == r2->rank){
                r1->rank++;
            }
        }
    }
};
void print(Node** x, int n){
    for(int i = 0; i < n; i++){
        cout<<x[i]->p->rank<<" "<<x[i]->p->key<<endl;
    }
}
//脱机最小值
int* OffLineMinimum(int m, int n){
    cout<<"请输入"<<endl;
    Node** r = new Node*[n];//元素结点
    Node** k = new Node*[m];//集合结点
    for(int i = 0 ; i < n; i++){
        r[i] = new Node(i + 1);
        r[i]->MakeSet();
    }
    //初始化k
    for(int i = 0; i < m; i++){
        int j,a,b;
        k[i] = new Node(i + 1);
        cin>>j;
        if(j == 1){
            cin>>a;
            r[a - 1]->p = k[i]; //根结点指向集合结点
            k[i]->p = r[a - 1]; //集合结点指向根结点
        }
        else if(j != 0){
            while(j != 1){
                cin>>a>>b;
                Node::Union(r[a - 1], r[b - 1], k[i]);//k[i]为最终并入的集合
                j--;
            }
        }
    }
    //算法开始
    int* extracted = new int[m];
    for(int i = 1 ; i <= n; i++){
        int j = Node::FindSet(r[i - 1])->p->key;
        if(j != m){
            extracted[j] = i;
            int l = j - 1;
            do{
                l++;
            }while(k[l] == nullptr);
            if(k[l]->p != nullptr)
                Node::Union(k[l]->p, k[j - 1]->p, k[l]); //将集合l的根与集合j - 1的根并入集合l
            else{
                k[j - 1]->p->p = k[l];
                k[l]->p = k[j - 1]->p;
            }
            delete k[j - 1]; 
            k[j - 1] = nullptr;
        }
        
    }
    return extracted;

}
int main(int argc, const char * argv[]) {
    
    int* ex = nullptr;
    ex = OffLineMinimum(7, 9);
    for(int i = 1 ; i < 7; i++)
        cout<<ex[i]<<" ";
    cout<<endl;
    return 0;
}
