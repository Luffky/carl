//
//  main.cpp
//  挂接点、桥以及双联通分支(思考题22-2)
//
//  Created by 伏开宇 on 2017/4/17.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include "Graph.hpp"
#include <iostream>
using namespace std;
//计算low
void DFS_Visit_Articulation(LinkGraph* G, int i, int* time, int* low){
    G->v[i]->color = 1; //结点u发现
    (*time) ++;
    Vertex* u = G->v[i];
    u->d = *time;
    Edge* edge = u->head;
    low[i] = u->d;
    while(edge != nullptr){
        if(G->v[edge->end]->color == 0){
            G->v[edge->end]->p = u;
            DFS_Visit_Articulation(G, edge->end, time, low);
            if(low[i] > low[edge->end]) //若子孙存在有指向某个真祖先的反向边
                low[i] = low[edge->end];
        }
        else if(u->p != G->v[edge->end]){//如果该边的尾结点不是头结点的父亲，则该边为后向边
            if(low[i] > G->v[edge->end]->d) //若当前low 小于后向边指向的祖先的d值
                low[i] = G->v[edge->end]->d;
        }
        edge = edge->next;
    }
    G->v[i]->color = 2; //结点u结束
    (*time) ++;
    u->f = *time;
}
//计算挂接点和桥
ListNode1* FindArticulation(LinkGraph* G, int* low, ListNode1* Bridge){
    int n = G->NumOfVertex;
    ListNode1* Articulation = new ListNode1; //记录所有的挂接点
    ListNode1** Child = new ListNode1*[n + 1];
    for(int i = 1; i <= n; i++){
        Child[i] = new ListNode1;
    }
    //构造深度优先树数据结构
    for(int i = 1; i <= n; i++){
        if(G->v[i]->p != nullptr){
            Node* node = new Node(i);
            Child[G->v[i]->p->key]->ListInsert(node);
        }
    }
    for(int i = 1; i <= n; i++){
        if(G->v[i]->p == nullptr){//如果是根节点
            if(Child[i]->n >= 2){//如果根节点儿子树大于等于2则为挂接点
                Node* node1 = new Node(i);
                Articulation->ListInsert(node1);
                Node* node = Child[i]->Sentinel->next;
                while(node != Child[i]->Sentinel){//扫描所有儿子
                    if(low[node->key] > G->v[i]->d){ //如果儿子结点low值大于本结点，则该两个结点之间的边为桥。因为这说明以儿子为根的子树，没有后向边连向父节点或者父节点的祖先，去掉该边将会使图不连通。
                        Node* Node2 = new Node(node->key);//将头和尾均加入Bridge链表中
                        Node* Node3 = new Node(i);
                        Bridge->ListInsert(Node2);
                        Bridge->ListInsert(Node3);
                    }
                    node = node->next;
                }
            }
        }
        else{//如果是非根节点
            Node* node = Child[i]->Sentinel->next;
            int flag = 0;
            while(node != Child[i]->Sentinel){//扫描所有儿子
                if(low[node->key] >= G->v[i]->d){//如果儿子low值大于等于本节点d值，说明儿子为根的子树中没有反向边指向本节点的祖先，则去掉本节点将会去连通化该图
                    if(flag == 0){//保证同一个挂接点只记录一次
                        Node* node1 = new Node(i);
                        Articulation->ListInsert(node1);
                    }
                    if(low[node->key] > G->v[i]->d){//同上，但是要扫描所有的儿子，因为一个挂接点可能有好几个桥
                        Node* Node2 = new Node(node->key);
                        Node* Node3 = new Node(i);
                        Bridge->ListInsert(Node2);
                        Bridge->ListInsert(Node3);
                    }
                    flag = 1;
                }
                node = node->next;
            }
        }
    }
    return Articulation;//返回挂接点
}
//22-2h暂时无思路
void DFS_Articulation(LinkGraph* G){
    int n = G->NumOfVertex;
    int time = 0;
    int* low = new int[n + 1];
    for(int i = 1; i<= n; i++){
        if(G->v[i]->color == 0){
            DFS_Visit_Articulation(G, i, &time, low);//DFS，维护low值
        }
    }
    ListNode1* Bridge = new ListNode1;
    ListNode1* Articulation = FindArticulation(G, low, Bridge); //找到所有挂接点和桥
    Articulation->Print();//打印所有挂接点
    Node* node1 = Bridge->Sentinel->next;
    while(node1 != Bridge->Sentinel){//打印所有桥,并且从图中删除所有桥，以便接下来的寻找双联通分支
        cout<<node1->key<<"一"<<node1->next->key<<endl;
        G->DeleteDoubleEdge(node1->key, node1->next->key);
        node1 = node1->next->next;
    }
    cout<<endl;
    G->Initial();
    Node* node = Articulation->Sentinel->next;
    time = 0;
    while(node != Articulation->Sentinel){
        if(G->v[node->key]->color == 0){
            DFS_Visit_Articulation(G, node->key, &time, low);
        }
        node = node->next;
    }
    delete Articulation;
    Articulation = FindArticulation(G, low, Bridge);
    Articulation->Print();
    int bcc = 0;
    for(int i = 1; i <= n; i++){
        if(G->v[i]->color == 0){
            bcc++;
        }
    }
    ListNode1** Child = new ListNode1*[n + 1];
    for(int i = 1; i <= n; i++){
        Child[i] = new ListNode1;
    }
    //构造深度优先树数据结构
    for(int i = 1; i <= n; i++){
        if(G->v[i]->p != nullptr){
            Node* node = new Node(i);
            Child[G->v[i]->p->key]->ListInsert(node);
        }
    }
    for(int i = 1; i <= n; i++){
        if(G->v[i]->p == nullptr){
            Node* node = Child[i]->Sentinel->next;
            
        }
    }
}
int main(int argc, const char * argv[]) {
    int N = 23;
    int E = 33;
    LinkGraph* l1 = new LinkGraph(N);
    //MatrixGraph* m1 = new MatrixGraph(N);
    for(int i = 0 ; i < E; i++){
        int s,e;
        cin>>s>>e;
        l1->AddDoubleEdge(s, e);
    }
    DFS_Articulation(l1);
    cout<<endl;
    return 0;
}
