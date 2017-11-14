//
//  main.cpp
//  practice
//
//  Created by 伏开宇 on 2017/6/27.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <map>
#include <fstream>
#include <stack>
#define MAXINT 0x7fffffff
#define MININT 0x80000000
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define UNKNOWN -1
#define TREE 0
#define BACKWARD 1
#define FORWARD 2
#define HORIZONTAL 3
#define FRONT 0
#define BACK 1
using namespace std;
class minVertexHeap;
class edge{
public:
    int start;
    int end;
    int value;
    edge* next;
    edge* next2;
    edge* edgeLink;
    map<string, int> m;
    edge(int s, int e, int v){
        start = s;
        end = e;
        value = v;
        next = nullptr;
        edgeLink = nullptr;
        next2 = nullptr;
        m["type"] = UNKNOWN;
    }
};

class vertex{
public:
    edge* head;
    edge* head2;
    edge* p;
    int index;
    map<string, int> m;
    vertex* parent;
    vertex(int i){
        index = i;
        head = nullptr;
        parent = nullptr;
    }
};

class Graph{
public:
    int vSize;
    int eSize;
    vertex** v;
    Graph(int n){
        vSize = n;
        v = new vertex*[n + 1];
        for (int i = 0; i <= n; i++) {
            v[i] = new vertex(i);
        }
        eSize = 0;
    }
    ~Graph(){
        delete v;
    }
    edge* AddSingleEdge(int s, int e, int value = 1, bool flag = FRONT){
        eSize++;
        edge* eg = new edge(s, e, value);
        eg->m["direct"] = flag;
        eg->next = v[s]->head;
        v[s]->head = eg;
        eg->next2 = v[e]->head2;
        v[e]->head2 = eg;
        return eg;
    }
   
    void AddDoubleEdge(int s, int e, int value = 1){
        AddSingleEdge(s, e, value);
        AddSingleEdge(e, s, value);
        eSize--;
    }
    void DeleteSingleEdge(int s, int e){
        eSize--;
        edge* cur = v[s]->head;
        if(cur == nullptr){
            cout<<"this edge is not existed"<<endl;
            exit(-1);
        }
        if (cur->end == e) {
            v[s]->head = cur->next;
        }
        else {
            for (; cur->next != nullptr; cur = cur->next) {
                if (cur->next->end == e) {
                    cur->next = cur->next->next;
                    break;
                }
            }
        }
        //********
        cur = v[e]->head2;
        if (cur == nullptr) {
            cout<<"this edge is not existed"<<endl;
            exit(-1);
        }
        if (cur->start == s) {
            v[e]->head2 = cur->next2;
        }
        else {
            for (; cur->next2 != nullptr; cur = cur->next2) {
                if (cur->next2->start == s) {
                    cur->next2 = cur->next2->next2;
                    break;
                }
            }
        }
    }
    
    void DeleteDoubleEdge(int s, int e){
        DeleteSingleEdge(s, e);
        DeleteSingleEdge(e, s);
        eSize++;
    }
    
    void InitializeSingleSource(int s){
        for (int i = 1; i <= vSize; i++) {
            v[i]->m["distance"] = MAXINT;
            v[i]->m["parent"] = -1;
        }
        v[s]->m["distance"] = 0;
    }
    
    void Relax(int u, int v, int w){
        int sum = this->v[u]->m["distance"] + w;
        if (this->v[u]->m["distance"] == MAXINT or w == MAXINT)
            sum = MAXINT;
        if(this->v[v]->m["distance"] > sum){
            this->v[v]->m["distance"] = sum;
            this->v[v]->m["parent"] = u;
        }
    }
    
    void Relax(int u, int v, int w, minVertexHeap* H);
    
    Graph* Reverse(){
        Graph* pRet = new Graph(this->vSize);
        for (int i = 1; i <= this->vSize; i++) {
            edge* pCurEdge = v[i]->head;
            while (pCurEdge != nullptr) {
                pRet->AddSingleEdge(pCurEdge->end, pCurEdge->start, pCurEdge->value);
                pCurEdge = pCurEdge->next;
            }
        }
        return pRet;
    }
    
    void Print(int mode){
        if (mode == 0) {
            for (int i = 1; i <= vSize; i++) {
                cout<<i<<": ";
                for (edge* cur = v[i]->head; cur != nullptr; cur = cur->next) {
                    cout<<cur->start<<"->"<<cur->end<<":"<<cur->m["f"]<<" ";//cur->m["c"]<<" "<<
                }
                cout<<endl;
                
            }
        }
        else {
            for (int i = 1; i <= vSize; i++) {
                cout<<i<<": ";
                for (edge* cur = v[i]->head2; cur != nullptr; cur = cur->next2) {
                    cout<<cur->start<<"->"<<cur->end<<"  ";
                }
                cout<<endl;
            }
        }
    }
    
    void PrintTime(){
        for (int i = 1; i <= vSize; i++) {
            cout<<i<<": start at "<<v[i]->m["start"]<<" finish at "<<v[i]->m["finish"]<<endl;
        }
    }
    
};

//
//BFS(图指针G，起始顶点s)
//
//
void BFS(Graph* G, int s){
    for (int i = 1; i <= G->vSize; i++) {
        G->v[i]->parent = nullptr;
        G->v[i]->m["color"] = WHITE;
        G->v[i]->m["distance"] = MAXINT;
    }
    G->v[s]->parent = nullptr;
    G->v[s]->m["color"] = GRAY;
    G->v[s]->m["distance"] = 0;
    queue<vertex*> pQueue;
    pQueue.push(G->v[s]);
    while (pQueue.empty() == 0) {
        vertex* pCurVertex = pQueue.front();
        pQueue.pop();
        for (edge* pCurEdge = pCurVertex->head; pCurEdge != nullptr; pCurEdge = pCurEdge->next) {
            vertex* pNextVertex = G->v[pCurEdge->end];
            if (pNextVertex->m["color"] == WHITE) {
                pNextVertex->m["color"] = GRAY;
                pNextVertex->parent = pCurVertex;
                pNextVertex->m["distance"] = pCurVertex->m["distance"] + 1;
                pQueue.push(pNextVertex);
            }
        }
        pCurVertex->m["color"] = BLACK;
    }
}
//
//PrintPath(图指针G，起点s，终点v
//
//
int PrintPath(Graph* G, int s, int v){
    vertex* pCurVertex = G->v[v]->parent;
    if(v == s){
        cout<<s;
        return 0;
    }
    else if(pCurVertex == nullptr){
        cout<<"There is no path from s to v"<<endl;
        return MININT;
    }
    else{
        int iRet = PrintPath(G, s, pCurVertex->index) + 1;
        cout<<"→"<<v;
        return iRet;
    }
}
//
//PrintAllPath(图指针G,起点s)
//
//
void PrintAllPath(Graph* G, int s){
    for (int i = 1; i <= G->vSize; i++) {
        int dis = PrintPath(G, s, i);
        cout<<": "<<dis<<endl;
    }
}
//
//DFSvisit(图指针G，当前顶点curVertex,）
//
//
void DFSvisit(Graph* G, vertex* curVertex, int &curTime){
    curTime += 1;
    curVertex->m["color"] = GRAY;
    curVertex->m["start"] = curTime;
    for (edge* curEdge = curVertex->head; curEdge != nullptr; curEdge = curEdge->next) {
        vertex* nextVertex = G->v[curEdge->end];
        if(curEdge->m["type"] == UNKNOWN){
            if (nextVertex->m["color"] == WHITE) {
                curEdge->m["type"] = TREE;
            }
            else if (nextVertex->m["color"] == GRAY){
                curEdge->m["type"] = BACKWARD;
            }
            else {
                if (curVertex->m["start"] > nextVertex->m["start"])
                    curEdge->m["type"] = HORIZONTAL;
                else
                    curEdge->m["type"] = FORWARD;
            }
        }
        if (nextVertex->m["color"] == WHITE) {
            nextVertex->parent = curVertex;
            DFSvisit(G, nextVertex, curTime);
        }
        
    }
    curVertex->m["color"] = BLACK;
    curTime += 1;
    curVertex->m["finish"] = curTime;
}

//
//DFS(图指针G)
//
//
void DFS(Graph* G){
    int vNum = G->vSize;
    int curTime = 0;
    for (int i = 1; i <= vNum; i++) {
        vertex* curVertex = G->v[i];
        if(curVertex->m["color"] == WHITE)
            DFSvisit(G, curVertex, curTime);
    }
}

//
//DFSiterative(图指针G）
//
//
void DFSiterative(Graph* G){
    int vNum = G->vSize;
    vector<edge*> record(vNum + 1, nullptr);
    for (int i = 1; i <= vNum; i++) {
        record[i] = G->v[i]->head;
    }
    stack<vertex*> unCompleteVertex;
    int curTime = 0;
    for (int i = 1; i <= vNum; i++) {
        if (G->v[i]->m["color"] == WHITE) {
            vertex* curVertex = G->v[i];
            unCompleteVertex.push(curVertex);
            while (unCompleteVertex.empty() == 0) {
                curVertex = unCompleteVertex.top();
                if (curVertex->m["color"] == WHITE) {
                    curTime++;
                    curVertex->m["color"] = GRAY;
                    curVertex->m["start"] = curTime;
                }
                edge* curEdge = nullptr;
                for (curEdge = record[curVertex->index]; curEdge != nullptr; curEdge = curEdge->next) {
                    vertex* nextVertex = G->v[curEdge->end];
                    if (nextVertex->m["color"] == WHITE) {
                        curEdge->m["type"] = TREE;
                        break;
                    }
                    else if (nextVertex->m["color"] == GRAY){
                        curEdge->m["type"] = BACKWARD;
                    }
                    else {
                        if (curVertex->m["start"] > nextVertex->m["start"])
                            curEdge->m["type"] = HORIZONTAL;
                        else
                            curEdge->m["type"] = FORWARD;
                    }
                }
                if (curEdge != nullptr) {
                    record[curVertex->index] = curEdge->next;
                    unCompleteVertex.push(G->v[curEdge->end]);
                    G->v[curEdge->end]->parent = curVertex;
                }
                else {
                    curTime++;
                    curVertex->m["color"] = BLACK;
                    curVertex->m["finish"] = curTime;
                    unCompleteVertex.pop();
                }
            }
        
        }
    }
}
//
//TopologicalSort版DFS
//
//
void DFSvisitForTopological(Graph* G, vertex* curVertex, int &curTime, vector<vertex*> &Topolist){
    curTime += 1;
    curVertex->m["color"] = GRAY;
    curVertex->m["start"] = curTime;
    for (edge* curEdge = curVertex->head; curEdge != nullptr; curEdge = curEdge->next) {
        vertex* nextVertex = G->v[curEdge->end];
        if(curEdge->m["type"] == UNKNOWN){
            if (nextVertex->m["color"] == WHITE) {
                curEdge->m["type"] = TREE;
            }
            else if (nextVertex->m["color"] == GRAY){
                curEdge->m["type"] = BACKWARD;
            }
            else {
                if (curVertex->m["start"] > nextVertex->m["start"])
                    curEdge->m["type"] = HORIZONTAL;
                else
                    curEdge->m["type"] = FORWARD;
            }
        }
        if (nextVertex->m["color"] == WHITE) {
            nextVertex->parent = curVertex;
            DFSvisitForTopological(G, nextVertex, curTime, Topolist);
        }
        
    }
    curVertex->m["color"] = BLACK;
    curTime += 1;
    curVertex->m["finish"] = curTime;
    Topolist.insert(Topolist.begin(), curVertex);
}
//
//TopologicalSort(图指针G）
//
//
vector<vertex*> TopologicalSort(Graph* G){
    vector<vertex*> Topolist;
    int curTime = 0;
    for (int i = 1; i <= G->vSize; i++) {
        if (G->v[i]->m["color"] == WHITE) {
            DFSvisitForTopological(G, G->v[i], curTime, Topolist);
        }
    }
//    for (int i = 1; i <= G->vSize; i++) {
//        for (edge* curEdge = G->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
//            if (curEdge->m["type"] == BACKWARD) {
//                cout<<"该图存在反向边，无法进行拓补排序"<<endl;
//                exit(-1);
//            }
//        }
//    }
    return Topolist;
}
//
//StronglyConnectedComponent版DFS
//
//
void DFSvisitForSCC(Graph* G, vertex* curVertex, int &curTime, int scc){
    curTime += 1;
    curVertex->m["scc"] = scc;
    curVertex->m["color"] = GRAY;
    curVertex->m["start"] = curTime;
    for (edge* curEdge = curVertex->head; curEdge != nullptr; curEdge = curEdge->next) {
        vertex* nextVertex = G->v[curEdge->end];
        if(curEdge->m["type"] == UNKNOWN){
            if (nextVertex->m["color"] == WHITE) {
                curEdge->m["type"] = TREE;
            }
            else if (nextVertex->m["color"] == GRAY){
                curEdge->m["type"] = BACKWARD;
            }
            else {
                if (curVertex->m["start"] > nextVertex->m["start"])
                    curEdge->m["type"] = HORIZONTAL;
                else
                    curEdge->m["type"] = FORWARD;
            }
        }
        if (nextVertex->m["color"] == WHITE) {
            nextVertex->parent = curVertex;
            DFSvisitForSCC(G, nextVertex, curTime, scc);
        }
        
    }
    curVertex->m["color"] = BLACK;
    curTime += 1;
    curVertex->m["finish"] = curTime;
}
//
//StronglyGCC(Garph* G)
//
//
Graph* StronglyCC(Graph* G){
    vector<vertex*> Topolist = TopologicalSort(G);
    Graph* GT = G->Reverse();
    int curTime = 0;
    int scc = 0;
    for (auto iter = Topolist.begin(); iter != Topolist.end(); iter++) {
        if (GT->v[(*iter)->index]->m["color"] == WHITE) {
            scc++;
            DFSvisitForSCC(GT, GT->v[(*iter)->index], curTime, scc);
        }
    }
    
    vector<int> SCC;
    Graph* GSCC = new Graph(scc);
    int** edgeRecord = new int*[GSCC->vSize + 1];
    for (int i = 1; i <= GSCC->vSize; i++) {
        edgeRecord[i] = new int[GSCC->vSize + 1];
        for (int j = 1; j <= GSCC->vSize; j++) {
            edgeRecord[i][j] = 0;
        }
    }
    vector<vector<int>> SCCs(scc + 1, SCC);
    for (int i = 1; i <= GT->vSize; i++) {
        SCCs[GT->v[i]->m["scc"]].push_back(i);
        for (edge* curEdge = GT->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
            if(edgeRecord[GT->v[i]->m["scc"]][GT->v[curEdge->end]->m["scc"]] == 0 and GT->v[i]->m["scc"] != GT->v[curEdge->end]->m["scc"]){
                GSCC->AddSingleEdge(GT->v[curEdge->end]->m["scc"], GT->v[i]->m["scc"]);
                edgeRecord[GT->v[i]->m["scc"]][GT->v[curEdge->end]->m["scc"]] = 1;
            }
        }
    }
//    for (int i = 1; i < SCCs.size(); i++) {
//        for (int j = 0; j < SCCs[i].size(); j++) {
//            cout<<SCCs[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    return GSCC;
}
//
//IsSemiConnected(图指针G)
//
//
bool IsSemiConnected(Graph* G){
    Graph* GSCC = StronglyCC(G);
    vector<vertex*> Topolist = TopologicalSort(GSCC);
    for (auto iter = Topolist.begin(); iter != Topolist.end() - 1; iter++) {
        int flag = 0;
        for (edge* curEdge = (*iter)->head; curEdge != nullptr; curEdge = curEdge->next) {
            if (curEdge->end == (*(iter + 1))->index) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            return false;
        }
    }
    return true;
}
//
//并查集
//
//
class DisjoinedNode{
public:
    DisjoinedNode* parent;
    vertex* key;
    int rank;
    DisjoinedNode(vertex* v){
        rank = -1;
        key = v;
        parent = nullptr;
    }
    void makeSet(){
        parent = this;
        rank = 0;
    }
    static DisjoinedNode* findSet(DisjoinedNode* targetVertex){
        if (targetVertex != targetVertex->parent) {
            targetVertex->parent = findSet(targetVertex->parent);
        }
        return targetVertex->parent;
    }
    static void UnionSet(DisjoinedNode* VertexA, DisjoinedNode* VertexB){
        DisjoinedNode* indexA = findSet(VertexA);
        DisjoinedNode* indexB = findSet(VertexB);
        if (indexA->rank < indexB->rank) {
            indexA->parent = indexB;
        }
        else {
            indexB->parent = indexA;
            if (indexB->rank == indexA->rank) {
                indexA->rank++;
            }
        }
    }
};
//
//最小优先队列
//
//
class minHeap{
public:
    vector<edge*> data;
    int length;
    int heap_size;
    minHeap(vertex** V, int length, int vSize){
        length = length;
        heap_size = length;
        int k = 0;
        for (int i = 1; i <= vSize; i++) {
            for (edge* curEdge = V[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
                data.push_back(curEdge);
                curEdge->m["heapIndex"] = k++;
            }
        }
    }
    
    void minimizeHeap(int index){
        int min = index;
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        if (left < heap_size and data[min]->value > data[left]->value) {
            min = left;
        }
        if (right < heap_size and data[min]->value > data[right]->value) {
            min = right;
        }
        if (min != index) {
            edge* temp = data[index];
            data[index] = data[min];
            data[min] = temp;
            data[index]->m["heapIndex"] = index;
            data[min]->m["heapIndex"] = min;
            minimizeHeap(min);
        }
    }
    
    void buildHeap(){
        for (int i = heap_size / 2 - 1; i >= 0; i--) {
            minimizeHeap(i);
        }
    }
    
    edge* extracMin(){
        if (heap_size < 1) {
            return nullptr;
        }
        edge* ret = data[0];
        data[0]->m["heapIndex"] = -1;
        data[0] = data[heap_size - 1];
        data[0]->m["heapIndex"] = 0;
        heap_size--;
        minimizeHeap(0);
        return ret;
    }
    
    void heapDecrease(edge* targetEdge, int newValue){
        if (newValue >= targetEdge->value) {
            cout<<"newValue is large than the original value"<<endl;
            return;
        }
        targetEdge->value = newValue;
        int index = targetEdge->m["heapIndex"];
        while (index != 0 and data[index]->value < data[(index - 1) / 2]->value) {
            edge* temp = data[index];
            data[index] = data[(index - 1) / 2];
            data[(index - 1) / 2] = temp;
            index = (index - 1) / 2;
        }
        
    }
    
    void insertNode(edge* newEdge){
        int temp = newEdge->value;
        newEdge->value = MAXINT;
        data[heap_size++] = newEdge;
        heapDecrease(newEdge, temp);
    }
};
class minVertexHeap{
public:
    vector<vertex*> data;
    int length;
    string key;
    int heap_size;
    minVertexHeap(vertex** V, int vSize, string key = "key"){
        length = vSize;
        this->key = key;
        heap_size = vSize;
        for (int i = 1; i <= vSize; i++) {
            data.push_back(V[i]);
            V[i]->m["heapIndex"] = i - 1;
        }
    }
    
    void minimizeHeap(int index){
        int min = index;
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        if (left < heap_size and data[min]->m[key] > data[left]->m[key]) {
            min = left;
        }
        if (right < heap_size and data[min]->m[key] > data[right]->m[key]) {
            min = right;
        }
        if (min != index) {
            vertex* temp = data[index];
            data[index] = data[min];
            data[min] = temp;
            data[index]->m["heapIndex"] = index;
            data[min]->m["heapIndex"] = min;
            minimizeHeap(min);
        }
    }
    
    void buildHeap(){
        for (int i = heap_size / 2 - 1; i >= 0; i--) {
            minimizeHeap(i);
        }
    }
    
    vertex* extracMin(){
        if (heap_size < 1) {
            return nullptr;
        }
        vertex* ret = data[0];
        data[0]->m["heapIndex"] = -1;
        data[0] = data[heap_size - 1];
        data[0]->m["heapIndex"] = 0;
        heap_size--;
        minimizeHeap(0);
        return ret;
    }
    
    void heapDecrease(vertex* targetVertex, int newValue){
        if (newValue >= targetVertex->m[key]) {
            cout<<"newValue is large than the original value"<<endl;
            return;
        }
        targetVertex->m[key] = newValue;
        int index = targetVertex->m["heapIndex"];
        while (index != 0 and data[index]->m[key] < data[(index - 1) / 2]->m[key]) {
            data[index]->m["heapIndex"] = (index - 1) / 2;
            data[(index - 1) / 2]->m["heapIndex"] = index;
            vertex* temp = data[index];
            data[index] = data[(index - 1) / 2];
            data[(index - 1) / 2] = temp;
            index = (index - 1) / 2;
        }
        
    }
    
    void insertNode(vertex* newVertex){
        int temp = newVertex->m[key];
        newVertex->m[key] = MAXINT;
        data[heap_size++] = newVertex;
        data[heap_size - 1]->m["heapIndex"] =  heap_size - 1;
        heapDecrease(newVertex, temp);
    }
};
//
//最小生成树(图指针G)
//
//
Graph* MST_Kruscal(Graph* G){
    DisjoinedNode** vertex = new DisjoinedNode*[G->vSize + 1];
    Graph* retG = new Graph(G->vSize);
    for (int i = 1; i <= G->vSize; i++) {
        vertex[i] = new DisjoinedNode(G->v[i]);
        vertex[i]->makeSet();
    }
    minHeap* H = new minHeap(G->v, G->eSize, G->vSize);
    H->buildHeap();
    int min = 0;
    while (H->heap_size) {
        edge* curEdge = H->extracMin();
        if (DisjoinedNode::findSet(vertex[curEdge->start]) != DisjoinedNode::findSet(vertex[curEdge->end])) {
            retG->AddDoubleEdge(curEdge->start, curEdge->end, curEdge->value);
            min += curEdge->value;
            DisjoinedNode::UnionSet(vertex[curEdge->start], vertex[curEdge->end]);
        }
    }
    cout<<min<<endl;
    return retG;
}
//
//PRIME(图指针G)
//
//
Graph* MST_Prim(Graph* G, int r){
    for (int i = 1; i <= G->vSize; i++) {
        G->v[i]->m["parent"] = -1;
        G->v[i]->m["key"] = MAXINT;
    }
    Graph* retG = new Graph(G->vSize);
    G->v[r]->m["parent"] = -1;
    G->v[r]->m["key"] = 0;
    minVertexHeap* H = new minVertexHeap(G->v, G->vSize);
    H->buildHeap();
    int min = 0;
    while (H->heap_size) {
        vertex* curVertex = H->extracMin();
        if (curVertex->m["parent"] != -1) {
            retG->AddDoubleEdge(curVertex->m["parent"], curVertex->index, curVertex->m["key"]);
            min += curVertex->m["key"];
        }
        for (edge* curEdge = curVertex->head; curEdge != nullptr; curEdge = curEdge->next) {
            if (G->v[curEdge->end]->m["heapIndex"] != -1 and G->v[curEdge->end]->m["key"] > curEdge->value) {
                H->heapDecrease(G->v[curEdge->end], curEdge->value);
                G->v[curEdge->end]->m["parent"] = curVertex->index;
                
            }
        }
    }
    cout<<min<<endl;
    return retG;
}
//
//BellmanFord(图指针G， 源点编号s)
//
//
bool BellmanFord(Graph* G, int s){
    G->InitializeSingleSource(s);
    for (int j = 0; j < G->vSize - 1; j++) {
        for (int i = 1; i <= G->vSize; i++) {
            for (edge* curEdge = G->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
                G->Relax(curEdge->start, curEdge->end, curEdge->value);
            }
        }
    }
    
    for (int i = 1; i <= G->vSize; i++) {
        for (edge* curEdge = G->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
            if (G->v[curEdge->end]->m["distance"] > G->v[curEdge->start]->m["distance"] + curEdge->value) {

                return false;
            }
        }
    }
    return true;
}
//
//DAG(图指针G，源点编号s)
//
//
void DagShortestPath(Graph* G, int s){
    vector<vertex*> Topolist = TopologicalSort(G);
    G->InitializeSingleSource(s);
    for (auto iter = Topolist.begin(); iter != Topolist.end(); iter++) {
        for (edge* curEdge = (*iter)->head; curEdge != nullptr; curEdge = curEdge->next) {
            G->Relax(curEdge->start, curEdge->end, curEdge->value);
        }
    }
}
//
//Djkstra(图指针，源点编号s)
//
//
void Graph::Relax(int u, int v, int w, minVertexHeap* H){
    if(this->v[v]->m["distance"] > this->v[u]->m["distance"] + w){
        H->heapDecrease(this->v[v], this->v[u]->m["distance"] + w);
        this->v[v]->m["parent"] = u;
        
    }
}
void Djkstra(Graph* G, int s){
    G->InitializeSingleSource(s);
    minVertexHeap* H = new minVertexHeap(G->v, G->vSize, "distance");
    while (H->heap_size) {
        vertex* curVertex = H->extracMin();
        for (edge* curEdge = curVertex->head; curEdge != nullptr; curEdge = curEdge->next) {
            G->Relax(curEdge->start, curEdge->end, curEdge->value);
        }
    }
}
//
//所有节点对的最短路径(关联矩阵图指针G)
//
//
int** Floyd_Warshall(int G[5][5], int n){
    int*** p = new int**[n + 1];
    int*** D = new int**[n + 1];
    for (int i = 0; i <= n ; i++) {
        D[i] = new int*[n + 1];
        p[i] = new int*[n + 1];
        for (int j = 1; j <= n ; j++) {
            D[i][j] = new int[n + 1];
            p[i][j] = new int[n + 1];
            if (i == 0){
                for (int k = 1; k <= n; k++) {
                    D[i][j][k] = G[j - 1][k - 1];
                    if (G[j - 1][k - 1] == MAXINT or j == k) {
                        p[i][j][k] = -1;
                        
                    }
                    else {
                        p[i][j][k] = j;
                        
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout<<D[0][i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                int sum = D[i - 1][j][i] + D[i - 1][i][k];
                if (D[i - 1][j][i] == MAXINT or D[i - 1][i][k] == MAXINT) {
                    sum = MAXINT;
                }
                if (D[i - 1][j][k] <= sum) {
                    D[i][j][k] = D[i - 1][j][k];
                    p[i][j][k] = p[i - 1][j][k];
                    //cout<<D[i][j][k]<<endl;
                }
                else {
                    D[i][j][k] = sum;
                    p[i][j][k] = p[i - 1][i][k];
                    //cout<<D[i][j][k]<<endl;
                }
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cout<<D[n][i][j]<<" ";
        }
        cout<<endl;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= n; k++) {
                cout<<p[i][j][k]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<"-------------------"<<endl;
    }
    return D[n];
}
//
//Johanson算法
//
//
int** Johnson(Graph* G){
    Graph* newGraph = new Graph(G->vSize + 1);
    for (int i = 1; i <= G->vSize; i++) {
        newGraph->AddSingleEdge(G->vSize + 1, i, 0);
        for (edge* curEdge = G->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
            newGraph->AddSingleEdge(curEdge->start, curEdge->end, curEdge->value);
        }
    }
    
    if (BellmanFord(newGraph, G->vSize + 1) == false) {
        cout<<"there is negative circle in the graph"<<endl;
        return nullptr;
    }
    for (int i = 1; i <= G->vSize; i++) {
        newGraph->v[i]->m["h"] = newGraph->v[i]->m["distance"];
    }
    
    for (int i = 1; i <= G->vSize; i++) {
        for (edge* curEdge = newGraph->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
            curEdge->value += newGraph->v[i]->m["h"] - newGraph->v[curEdge->end]->m["h"];
        }
    }
    int** D = new int*[G->vSize + 1];
    for (int i = 1; i <= G->vSize; i++) {
        D[i] = new int[G->vSize + 1];
        Djkstra(newGraph, i);
        for (int j = 1; j <= G->vSize; j++) {
            D[i][j] = newGraph->v[j]->m["distance"] + newGraph->v[j]->m["h"] - newGraph->v[i]->m["h"];
        }
    }
    return D;
}
//
//最大流
//
//
int FindAugmentedPath(Graph* G, int s, int t, vector<edge*> &Augment){
    for (int i = 1; i <= G->vSize; i++) {
        G->v[i]->m["d"] = MAXINT;
        G->v[i]->m["color"] = WHITE;
        G->v[i]->parent = nullptr;
        G->v[i]->p = nullptr;
    }
    G->v[s]->m["d"] = 0;
    G->v[s]->m["color"] = GRAY;
    queue<vertex*> Q;
    Q.push(G->v[s]);
    int flag = 0;
    while (Q.empty() == 0) {
        vertex* curVertex = Q.front();
        Q.pop();
        if (curVertex->index == t) {
            flag = 1;
            break;
        }
        for (edge* curEdge = curVertex->head; curEdge != nullptr; curEdge = curEdge->next) {
            vertex* nextVertex = G->v[curEdge->end];
            if (nextVertex->m["color"] == WHITE and curEdge->m["c"] > 0) {
                nextVertex->m["color"] = GRAY;
                nextVertex->parent = curVertex;
                nextVertex->p = curEdge;
                nextVertex->m["d"] = curVertex->m["d"] + 1;
                Q.push(nextVertex);
            }
        }
        curVertex->m["color"] = BLACK;
    }
    if (flag == 0) {
        return 0;
    }
    else{
        int i = t;
        while (i != s) {
            Augment.push_back(G->v[i]->p);
            i = G->v[i]->p->start;
        }
        return 1;
    }
}
int FordFulkerson(Graph* G, int s, int t){
    Graph* GC = new Graph(G->vSize);
    for (int i = 1; i <= G->vSize; i++) {
        for (edge* curEdge = G->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
            edge* front = GC->AddSingleEdge(curEdge->start, curEdge->end, curEdge->value, FRONT);
            edge* back = GC->AddSingleEdge(curEdge->end, curEdge->start, curEdge->value, BACK);
            front->m["c"] = front->value;
            back->m["c"] = 0;
            front->m["f"] = 0;
            front->edgeLink = back;
            back->edgeLink = front;
        }
    }
    vector<edge*> Augment;
    while (FindAugmentedPath(GC, s, t, Augment)) {
        int min = MAXINT;
        for (auto iter = Augment.begin(); iter != Augment.end(); iter++) {
            if (min > (*iter)->value) {
                min = (*iter)->value;
            }
        }
        for (auto iter = Augment.begin(); iter != Augment.end(); iter++) {
            if ((*iter)->m["direct"] == FRONT) {
                (*iter)->m["f"] += min;
                (*iter)->m["c"] = (*iter)->value - (*iter)->m["f"];
                (*iter)->edgeLink->m["c"] = (*iter)->m["f"];
            }
            else {
                (*iter)->edgeLink->m["f"] -= min;
                (*iter)->m["c"] = (*iter)->edgeLink->m["f"];
                (*iter)->edgeLink->m["c"] = (*iter)->value - (*iter)->edgeLink->m["f"];
            }
        }
        GC->Print(0);
        cout<<endl;
        Augment.clear();
    }
    int ret = 0;
    for (edge* curEdge = GC->v[s]->head; curEdge != nullptr; curEdge = curEdge->next) {
        ret += curEdge->m["f"];
    }
    return ret;
}
//
//重贴标签
//
//
void initializePush(Graph* G, int s, queue<vertex*> &overflowV){
    int n = G->vSize;
    for (int i = 1; i <= n; i++) {
        G->v[i]->m["h"] = 0;
        G->v[i]->m["e"] = 0;
    }
    G->v[s]->m["h"] = G->vSize;
    for (edge* curEdge = G->v[s]->head; curEdge != nullptr; curEdge = curEdge->next) {
        curEdge->m["f"] = curEdge->value;
        curEdge->m["c"] = 0;
        curEdge->edgeLink->m["c"] = curEdge->value;
        G->v[s]->m["e"] -= curEdge->value;
        G->v[curEdge->end]->m["e"] = curEdge->value;
        overflowV.push(G->v[curEdge->end]);
    }
}

void Push(vertex* u, vertex* v, edge* curEdge, queue<vertex*> &overflowV, int t){
    int deltaf = min(u->m["e"], curEdge->m["c"]);
    if (curEdge->m["direct"] == FRONT) {
        curEdge->m["c"] -= deltaf;
        curEdge->m["f"] += deltaf;
        curEdge->edgeLink->m["c"] = curEdge->m["f"];
    }
    else {
        curEdge->m["c"] -= deltaf;
        curEdge->edgeLink->m["f"] -= deltaf;
        curEdge->edgeLink->m["c"] = curEdge->value - curEdge->edgeLink->m["f"];
    }
    u->m["e"] -= deltaf;
    v->m["e"] += deltaf;
    if (u->m["e"] > 0) {
        overflowV.push(u);
    }
    if (v->m["e"] > 0 and v->index != t) {
        overflowV.push(v);
    }
}

void Relabel(vertex* u, int min){
    u->m["h"] = min + 1;
}

int Generic_Push_relabel(Graph* G, int s, int t){
    Graph* GC = new Graph(G->vSize);
    for (int i = 1; i <= G->vSize; i++) {
        for (edge* curEdge = G->v[i]->head; curEdge != nullptr; curEdge = curEdge->next) {
            edge* front = GC->AddSingleEdge(curEdge->start, curEdge->end, curEdge->value, FRONT);
            edge* back = GC->AddSingleEdge(curEdge->end, curEdge->start, curEdge->value, BACK);
            front->m["c"] = front->value;
            back->m["c"] = 0;
            front->m["f"] = 0;
            front->edgeLink = back;
            back->edgeLink = front;
        }
    }
    queue<vertex*> overflowV;
    initializePush(GC, s, overflowV);
    int flag = 0;
    int min = MAXINT;
    while (overflowV.empty() == 0) {
        vertex* curVertex = overflowV.front();
        overflowV.pop();
        flag = 0;
        min = MAXINT;
        for (edge* curEdge = curVertex->head; curEdge != nullptr; curEdge = curEdge->next) {
            vertex* nextVertex = GC->v[curEdge->end];
            if (curEdge->m["c"] > 0 ) {
                if (curVertex->m["h"] == nextVertex->m["h"] + 1) {
                    Push(curVertex, nextVertex, curEdge, overflowV, t);
                    flag = 1;
                    break;
                }
                if (min > nextVertex->m["h"]) {
                    min = nextVertex->m["h"];
                }
            }
        }
        if (flag == 0) {
            overflowV.push(curVertex);
            Relabel(curVertex, min);
        }
    }
    int ret = 0;
    for (edge* curEdge = GC->v[s]->head; curEdge != nullptr; curEdge = curEdge->next) {
        ret += curEdge->m["f"];
    }
    return ret;
}
void print(vector<vector<int>> a){
    for (int i = 0; i < a.size(); i++) {
        cout<<a[i][0]<<" "<<a[i][1]<<endl;
    }
    cout<<endl;
    cout<<endl;
}
int main(int argc, const char * argv[]) {
    ifstream in("input.txt");
    if (in.is_open()) {
        vector<vector<int>> a;
        int ng;
        int ne;
        in>>ng>>ne;
        Graph* G = new Graph(ng);
        for (int i = 0; i < ne; i++) {
            vector<int> temp;
            int s,e,v;
            in>>s>>e>>v;
            temp.push_back(s);
            temp.push_back(e);
            temp.push_back(v);
            a.push_back(temp);
            G->AddSingleEdge(a[i][0], a[i][1], a[i][2]);
        }
        cout<<Generic_Push_relabel(G, 1, 4)<<endl;
        //cout<<FordFulkerson(G, 1, 4)<<endl;
    }
    else{
        cout<<"fail to open the file!"<<endl;
        exit(-1);
    }
    return 0;
}
