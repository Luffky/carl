//
//  main.cpp
//  最小生成树
//
//  Created by 伏开宇 on 2017/4/21.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <queue>
#include "Graph.hpp"
//练习23.1-11

//二叉堆
class Heap{
public:
    Edge** data;
    int heap_size;
    int length;
    Heap(Vertex** vertex, int length, int n){
        this->length = length;
        heap_size = length;
        data = new Edge*[length + 1];
        for(int i = 1, j = 1; i <= n; i++){//存储相关指针，便于交换
            Edge* edge = vertex[i]->head;
            while (edge != nullptr) {
                if(edge->IsDouble == 0)
                    data[j++] = new Edge(edge->start, edge->end, edge->value);
                edge = edge->next;
            }
        }
    }
    void MiniHeapify(int i){
        int l = 2 * i;//左儿子下标
        int r = 2 * i + 1;//右儿子下标
        int smallest = i;
        if(l <= heap_size and data[smallest]->value > data[l]->value){
            smallest = l;
        }
        if(r <= heap_size and data[smallest]->value > data[r]->value){
            smallest = r;
        }
        if(smallest != i){
            Edge* edge = data[smallest];
            data[smallest] = data[i];
            data[i] = edge;
            MiniHeapify(smallest);
        }
    }
    void BuildHealp(){
        for(int i = heap_size / 2; i > 0; i--){
            MiniHeapify(i);
        }
    }
    
    Edge* ExtracMin(){
        if(heap_size < 1)
            return nullptr;
        Edge* edge = data[1];
        data[1] = data[heap_size];
        heap_size--;
        MiniHeapify(1);
        return edge;
    }
    
    void HeapDecrease(int i, int value){
        if(value >= data[i]->value){
            cout<<"新值比原值大"<<endl;
            return;
        }
        data[i]->value = value;
        while(i > 1 and data[i]->value < data[i / 2]->value){
            Edge* edge = data[i];
            data[i] = data[i / 2];
            data[i / 2] = edge;
            i = i / 2;
        }
    }
    
    void Insert(Edge* edge){
        int value = edge->value;
        edge->value = INT32_MAX;
        heap_size++;
        length++;
        data[heap_size] = edge;
        HeapDecrease(heap_size, value);
    }
};

class Heap1{
public:
    Vertex** data;
    int heap_size;
    int length;
    Heap1(Vertex** vertex, int n){
        this->length = n;
        heap_size = n;
        data = new Vertex*[n + 1];
        for(int i = 1; i <= n; i++){//存储相关指针，便于交换
            data[i] = vertex[i];
            data[i]->num = i;
        }
    }
    void MiniHeapify(int i){
        int l = 2 * i;//左儿子下标
        int r = 2 * i + 1;//右儿子下标
        int smallest = i;
        if(l <= heap_size and data[smallest]->key > data[l]->key){
            smallest = l;
        }
        if(r <= heap_size and data[smallest]->key > data[r]->key){
            smallest = r;
        }
        if(smallest != i){
            Vertex* vertex = data[smallest];
            data[smallest] = data[i];
            data[i] = vertex;
            data[i]->num = i;
            data[smallest]->num = smallest;
            MiniHeapify(smallest);
        }
    }
    void BuildHealp(){
        for(int i = heap_size / 2; i > 0; i--){
            MiniHeapify(i);
        }
    }
    
    Vertex* ExtracMin(){
        if(heap_size < 1)
            return nullptr;
        Vertex* vertex = data[1];
        data[1] = data[heap_size];
        data[1]->num = 1;
        heap_size--;
        MiniHeapify(1);
        return vertex;
    }
    
    void HeapDecrease(int i, int key){
        if(key >= data[i]->key){
            cout<<"新值比原值大"<<endl;
            return;
        }
        data[i]->key = key;
        while(i > 1 and data[i]->key < data[i / 2]->key){
            Vertex* vertex = data[i];
            data[i] = data[i / 2];
            data[i / 2] = vertex;
            data[i]->num = i;
            data[i / 2]->num = i / 2;
            i = i / 2;
        }
    }
    
    void Insert(Vertex* vertex){
        int key = vertex->key;
        vertex->key = INT32_MAX;
        heap_size++;
        length++;
        data[heap_size] = vertex;
        data[heap_size]->num = heap_size;
        HeapDecrease(heap_size, key);
    }
};

class Heap3{
public:
    Edge** data;
    int heap_size;
    int length;
    Heap3(Vertex** vertex, int length, int n){
        this->length = length;
        heap_size = length;
        data = new Edge*[length + 1];
        for(int i = 1, j = 1; i <= n; i++){//存储相关指针，便于交换
            Edge* edge = vertex[i]->head;
            while (edge != nullptr) {
                if(edge->IsDouble == 0)
                    data[j++] = new Edge(edge->start, edge->end, edge->value);
                edge = edge->next;
            }
        }
    }
    void MaxHeapify(int i){
        int l = 2 * i;//左儿子下标
        int r = 2 * i + 1;//右儿子下标
        int largest = i;
        if(l <= heap_size and data[largest]->value < data[l]->value){
            largest = l;
        }
        if(r <= heap_size and data[largest]->value < data[r]->value){
            largest = r;
        }
        if(largest != i){
            Edge* edge = data[largest];
            data[largest] = data[i];
            data[i] = edge;
            MaxHeapify(largest);
        }
    }
    void BuildHealp(){
        for(int i = heap_size / 2; i > 0; i--){
            MaxHeapify(i);
        }
    }
    
    Edge* ExtracMax(){
        if(heap_size < 1)
            return nullptr;
        Edge* edge = data[1];
        data[1] = data[heap_size];
        heap_size--;
        MaxHeapify(1);
        return edge;
    }
    
    void HeapIncrease(int i, int value){
        if(value <= data[i]->value){
            cout<<"新值比原值小"<<endl;
            return;
        }
        data[i]->value = value;
        while(i > 1 and data[i]->value > data[i / 2]->value){
            Edge* edge = data[i];
            data[i] = data[i / 2];
            data[i / 2] = edge;
            i = i / 2;
        }
    }
    
    void Insert(Edge* edge){
        int value = edge->value;
        edge->value = INT32_MIN;
        heap_size++;
        length++;
        data[heap_size] = edge;
        HeapIncrease(heap_size, value);
    }
};

//kruscal算法
LinkGraph* MST_Kruscal(LinkGraph* G){
    ForestNode** node = new ForestNode*[G->NumOfVertex + 1];
    LinkGraph* A = new LinkGraph(G->NumOfVertex);//A是一个最小生成树森林
    for (int i = 1; i <= G->NumOfVertex; i++) {
        node[i] = new ForestNode(i);
        node[i]->MakeSet();
    }
    Heap* h = new Heap(G->v, G->NumOfEdge, G->NumOfVertex);
    h->BuildHealp();
    while(h->heap_size != 0){
        Edge* edge = h->ExtracMin();
        if(ForestNode::FindSet(node[edge->start]) != ForestNode::FindSet(node[edge->end])){
            A->AddDoubleEdge(edge->start, edge->end);
            ForestNode::Union(node[edge->start], node[edge->end]);
        }
    }
    return A;
}
//prim算法
LinkGraph* MST_Prim(LinkGraph* G, int r){
    for(int i = 1; i <= G->NumOfVertex; i++){
        G->v[i]->key = INT32_MAX;
        G->v[i]->L = 0;
    }
    int* p = new int[G->NumOfVertex];
    for(int i = 1; i <= G->NumOfVertex; i++)
        p[i] = -1;
    G->v[r]->key = 0;
    LinkGraph* A = new LinkGraph(G->NumOfVertex);
    Heap1* h = new Heap1(G->v, G->NumOfVertex);
    h->BuildHealp();
    while(h->heap_size != 0){
        Vertex* u = h->ExtracMin();
        u->L = 1;
        Edge* edge = u->head;
        while (edge != nullptr) {
            int v = edge->end;
            if(G->v[v]->L == 0 and edge->value < G->v[v]->key){
                h->HeapDecrease(G->v[v]->num, edge->value);
                p[v] = edge->start;
            }
            edge = edge->next;
        }
    }
    for(int i = 1; i <= G->NumOfVertex; i++){
        if(i != r){
            A->AddDoubleEdge(i, p[i], G->v[i]->key);
            A->v[i]->p = A->v[p[i]];
        }
    }
    return A;
}
//prim算法 邻接矩阵练习23.2-2
class PrimNode{//辅助类
public:
    int p;
    int key;
    int i;
    int Is_in_H;
    int num;
    PrimNode(int num){
        this->num = num;
        this->p = -1;
        this->key = INT32_MAX;
        this->Is_in_H = 0;
    }
};
class Heap2{
public:
    PrimNode** data;
    int heap_size;
    int length;
    Heap2(PrimNode** node, int n){
        this->length = n;
        heap_size = n;
        data = new PrimNode*[n + 1];
        for(int i = 1; i <= n; i++){//存储相关指针，便于交换
            data[i] = node[i];
            data[i]->i = i;
            data[i]->Is_in_H = 1;
        }
    }
    void MiniHeapify(int i){
        int l = 2 * i;//左儿子下标
        int r = 2 * i + 1;//右儿子下标
        int smallest = i;
        if(l <= heap_size and data[smallest]->key > data[l]->key){
            smallest = l;
        }
        if(r <= heap_size and data[smallest]->key > data[r]->key){
            smallest = r;
        }
        if(smallest != i){
            PrimNode* vertex = data[smallest];
            data[smallest] = data[i];
            data[i] = vertex;
            data[i]->i = i;
            data[smallest]->i = smallest;
            MiniHeapify(smallest);
        }
    }
    void BuildHealp(){
        for(int i = heap_size / 2; i > 0; i--){
            MiniHeapify(i);
        }
    }
    
    PrimNode* ExtracMin(){
        if(heap_size < 1)
            return nullptr;
        PrimNode* vertex = data[1];
        data[1] = data[heap_size];
        data[1]->i = 1;
        heap_size--;
        MiniHeapify(1);
        return vertex;
    }
    
    void HeapDecrease(int i, int key){
        if(key >= data[i]->key){
            cout<<"新值比原值大"<<endl;
            return;
        }
        data[i]->key = key;
        while(i > 1 and data[i]->key < data[i / 2]->key){
            PrimNode* vertex = data[i];
            data[i] = data[i / 2];
            data[i / 2] = vertex;
            data[i]->i = i;
            data[i / 2]->i = i / 2;
            i = i / 2;
        }
    }
    
    void Insert(PrimNode* vertex){
        int key = vertex->key;
        vertex->key = INT32_MAX;
        heap_size++;
        length++;
        data[heap_size] = vertex;
        data[heap_size]->i = heap_size;
        HeapDecrease(heap_size, key);
    }
};

MatrixGraph* MST_Prim(MatrixGraph* G, int r){
    PrimNode** V = new PrimNode*[G->n + 1];
    for(int i = 1; i <= G->n; i++){
        V[i] = new PrimNode(i);
    }
    int n = G->n;
    V[r]->key = 0;
    Heap2* H = new Heap2(V, G->n);
    H->BuildHealp();
    while(H->heap_size != 0){
        PrimNode* u = H->ExtracMin();
        u->Is_in_H = 0;
        for(int i = 1; i <= n; i++){
            if(G->M[u->num][i] != 0 and V[i]->Is_in_H == 1 and G->M[u->num][i] < V[i]->key){
                V[i]->p = u->num;
                H->HeapDecrease(V[i]->i, G->M[u->num][i]);
            }
        }
    }
    MatrixGraph* A = new MatrixGraph(n);
    for(int i = 1; i <= n; i++){
        if(i != r)
            A->AddDoubleEdge(i, V[i]->p, G->M[i][V[i]->p]);
    }
    return A;
}

//更新最小生成树 练习23.2-7
void Refresh(LinkGraph* G, Vertex* V, int root){
    int i = INT32_MAX;
    int minedge = 0;
    Edge* edge = V->head;
    while (edge != nullptr) {
        if(i > edge->value){
            minedge = edge->end;
            i = edge->value;
        }
        edge = edge->next;
    }
    G->AddVertice();
    G->AddDoubleEdge(V->key, minedge, i);//加入轻边
    G->v[V->key]->p = G->v[minedge];
    ListNode1* u = new ListNode1;
    ListNode1* v = new ListNode1;
    edge = V->head;
    while (edge != nullptr) {
        if(edge->end != minedge){//寻找环中最小边,设另外增加的边为(u, v)
            G->AddDoubleEdge(edge->start, edge->end, edge->value);
            Vertex* temp = G->v[edge->start];
            while(temp != nullptr){//回溯至根
                Node* m = new Node(temp->key);
                u->ListInsert(m);//记录沿途结点
                temp = temp->p;
            }
            Node* m = new Node(edge->start);
            v->ListInsert(m);
            temp = G->v[edge->end];
            while(temp != nullptr){//回溯至根
                m = new Node(temp->key);
                v->ListInsert(m);
                temp = temp->p;
            }
            Node* p = v->Sentinel->next;
            Node* q = u->Sentinel->next;
            while(p->next->key == q->next->key){//找到回路起点
                p = p->next;
                q = q->next;
            }
            int max = -1;
            Edge* maxIndex = nullptr;
            while(p != nullptr and p->key != INT32_MAX){//扫描回路一侧
                Edge* edge = G->v[p->key]->head;
                while(edge != nullptr){
                    if(edge->end == p->next->key){
                        if(max < edge->value){
                            max = edge->value;
                            maxIndex = edge;
                        }
                        break;
                    }
                    edge = edge->next;
                }
                p = p->next;
            }
            while (q != nullptr and q->key != INT32_MAX) {//扫描回路另一侧
                Edge* edge = G->v[q->key]->head;
                while(edge != nullptr){
                    if(edge->end == q->next->key){
                        if(max < edge->value){
                            max = edge->value;
                            maxIndex = edge;
                        }
                        break;
                    }
                    edge = edge->next;
                }
                q = q->next;
            }
            G->DeleteDoubleEdge(maxIndex->start, maxIndex->end);//删除回路中最大权边
        }
        edge = edge->next;
    }
}
//思考题23-1 次优最小生成树
void DFSFindMax(LinkGraph* G, int i, Edge*** max, int head){
    Edge* edge = G->v[i]->head;
    while(edge != nullptr){
        if(max[head][edge->end] == 0 and head != edge->end){//如果当前结点为头结点，或者当前边值大于head到当前结点的最大边值，则跟新max,if判断防止逆边
            if(i == head or edge->value > max[head][edge->start]->value)
                max[head][edge->end] = edge;
            else
                max[head][edge->end] = max[head][edge->start];//否则max为之前路径上的最大值
            DFSFindMax(G, edge->end, max, head);
        }
        
        edge = edge->next;
    }
}
Edge*** FindMax(LinkGraph* G){
    Edge*** max = new Edge**[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        max[i] = new Edge*[G->NumOfVertex + 1];
        for(int j = 1; j <= G->NumOfVertex + 1;j++)
            max[i][j] = 0;
        DFSFindMax(G, i, max, i);
    }
    return max;
}
Edge*** BFSFindMax(LinkGraph* G){//BFS方法
    Edge*** max = new Edge**[G->NumOfVertex + 1];
    for(int i = 1; i <= G->NumOfVertex; i++){
        max[i] = new Edge*[G->NumOfVertex + 1];
        for(int j = 1; j <= G->NumOfVertex + 1;j++)
            max[i][j] = 0;
        queue<int> Q;
        Q.push(i);
        while(!Q.empty()){
            Vertex* v = G->v[Q.front()];
            Q.pop();
            Edge* edge = v->head;
            while (edge != nullptr) {
                if(i != edge->end and max[i][edge->end] == 0){
                    if(v->key == i or edge->value > max[i][edge->start]->value){
                        max[i][edge->end] = edge;
                    }
                    else
                        max[i][edge->end] = max[i][edge->start];
                    Q.push(edge->end);
                }
                edge = edge->next;
            }
        }
    }
    return max;
}
void MakeSecondBestTree(LinkGraph* G){
    Edge*** max = BFSFindMax(G);
    //遍历G图中所有不在最小生成树T中的边（u，v），并且计算w(u, v) - max[u][v];找到最小的一对边u,v用他们替换掉max[u][v]中的边即可
    //ps:暂时没有能够较好的遍历所有不在T中的G中的边的好办法。
}
//思考题23-3 瓶颈生成树
//判断瓶颈生成树的值是否最大不超过b
void DFSBottle(LinkGraph* G, int i){
    G->v[i]->color = 1;
    Edge* edge = G->v[i]->head;
    while (edge != nullptr) {
        if(G->v[edge->end]->color == 0 and edge->Uneffective == 0){
            DFSBottle(G, edge->end);
        }
        edge = edge->next;
    }
    G->v[i]->color = 2;
}
//判断主函数
bool Is_larger_than(LinkGraph* G, int b){
    int n = G->NumOfVertex;
    G->Initial();
    int decrease = 0;
    for(int i = 1; i <= n; i++){//OE
        Edge* prev = nullptr;
        Edge* edge = G->v[i]->head;
        while(edge != nullptr){
            if(edge->Uneffective == 0 and edge->value > b){
                edge->Uneffective = 1;
                decrease++;
            }
            prev = edge;
            edge = edge->next;
            
        }
    }
    G->NumOfEdge -= decrease / 2;
    DFSBottle(G, 1);//遍历全图
    for(int i = 1; i <= n; i++){//若有结点未被遍历，则说明不连通，返回false
        if(G->v[i]->color == 0)
            return false;
    }
    return true;
}
//生成瓶颈树
LinkGraph* BottleTree(LinkGraph* G){
    int b = 0;
    for(int i = 1; i <= G->NumOfVertex; i++){//O(V + E)
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(b < edge->value)
                b = edge->value;
            edge = edge->next;
        }
    }
    while(Is_larger_than(G, b)){//找到最大的b值，使存在瓶颈树的最大权重为b
        b--;
    }
    b++;
    int time = 0;
    G->Initial();
    for (int i = 1; i <= G->NumOfVertex; i++) {//O(V+E)，遍历图，找到一个瓶颈树
        if(G->v[i]->color == 0)
            Function::DFS_Visit(G, i, &time, 0, b);
    }
    cout<<b<<endl;
    LinkGraph* A = new LinkGraph(G->NumOfVertex);
    for(int i = 1; i <= G->NumOfVertex; i++){//O(V)，构造瓶颈树新图
        if(G->v[i]->p != nullptr)
            A->AddDoubleEdge(i, G->v[i]->p->num, G->v[i]->key);
    }
    return A;
}
//思考题23-4 第三种最小生成树算法
LinkGraph* MaybeMSTA(LinkGraph* G, MatrixGraph* M){
    Heap3* h = new Heap3(G->v, G->NumOfEdge, G->NumOfVertex);
    h->BuildHealp();
    LinkGraph* A = new LinkGraph(G->NumOfVertex);
    while(h->heap_size != 0){
        Edge* edge = h->ExtracMax();
        edge->Uneffective = 1;
        DFSBottle(G, 1);//遍历全图
        int flag = 0;
        for(int i = 1; i <= G->NumOfVertex; i++){//若有结点未被遍历，则说明不连通
            if(G->v[i]->color == 0)
                flag = 1;
        }
        if(flag == 1)
            edge->Uneffective = 0;//说明此边不能去掉
        else{
            G->DeleteDoubleEdge(edge->start, edge->end);
            G->DeleteDoubleEdge(edge->end, edge->start);
        }
    }
    for(int i = 1; i <= M->n; i++){
        for(int j = 1; j <= M->n; j++)
            if(M->M[i][j] != 0)
                A->AddDoubleEdge(i, j, M->M[i][j]);
    }
    
    
    return A;
}//未完成
LinkGraph* MaybeMSTB(LinkGraph* G){
    LinkGraph* A = new LinkGraph(G->NumOfVertex);
    ForestNode** node = new ForestNode*[G->NumOfVertex + 1];
    for (int i = 1; i <= G->NumOfVertex; i++) {
        node[i] = new ForestNode(i);
        node[i]->MakeSet();
    }
    for (int i = 1; i <= G->NumOfVertex; i++) {
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            if(ForestNode::FindSet(node[edge->start]) != ForestNode::FindSet(node[edge->end])){
                A->AddDoubleEdge(edge->start, edge->end, edge->value);
                ForestNode::Union(node[edge->start], node[edge->end]);
            }
            edge = edge->next;
        }
    }
    return A;
}
LinkGraph* MaybeMSTC(LinkGraph* G){
    LinkGraph* A = new LinkGraph(G->NumOfVertex);
    for(int i = 1; i <= G->NumOfVertex; i++){
        Edge* edge = G->v[i]->head;
        while (edge != nullptr) {
            while(edge != nullptr and edge->IsDouble != 0){
                edge = edge->next;
            }
            if(edge == nullptr)
                break;
            A->AddDoubleEdge(edge->start, edge->end, edge->value);
            int time = 0;
            Vertex** v = new Vertex*[2];
            v[0] = nullptr;
            v[1] = nullptr;
            for(int i = 1; i <= G->NumOfVertex; i++){
                if(A->v[i]->color == 0)
                    Function::DFS_Visit(A, i, &time, 0, INT32_MAX, v);
            }
            int largest = 0;
            Edge* lar = nullptr; 
            Vertex* temp = v[0];
            if(temp != nullptr){//如果存在回路
                while(temp != v[1]){
                    Edge* edge = temp->head;
                    while(edge != nullptr){
                        if(edge->end == temp->p->num and edge->value > largest){
                            largest = edge->value;
                            lar = edge;
                        }
                        edge = edge->next;
                    }
                    temp = temp->p;
                }
                Edge* edge = v[1]->head;
                while (edge != nullptr) {
                    if(edge->end == v[0]->num and edge->value > largest){
                        largest = edge->value;
                        lar = edge;
                    }
                    edge = edge->next;
                }
                A->DeleteDoubleEdge(lar->start, lar->end);
            }
            for(int i = 1; i <= A->NumOfVertex; i++){
                Edge* edge = A->v[i]->head;
                while (edge != nullptr) {
                    edge->type = -1;
                    edge = edge->next;
                }
            }
            edge = edge->next;
            A->Initial();
        }
    }
    
    return A;

}
int main(int argc, const char * argv[]) {
    int V = 9;
    int E = 14;
    ifstream in("/program/文件流/cin.txt");
    if(in.is_open()){
        //cout<<"请输入边"<<endl;
        LinkGraph* G = new LinkGraph(V);
        MatrixGraph* G2 = new MatrixGraph(V);
        for(int i = 0; i < E; i++){
            int s, e, v;
            in>>s>>e>>v;
            G->AddDoubleEdge(s, e, v);
            G2->AddDoubleEdge(s, e, v);
        }
        LinkGraph* A2 = MaybeMSTC(G);
        A2->Print();
    }
    in.close();
    return 0;
}
