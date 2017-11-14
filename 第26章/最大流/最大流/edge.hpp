//
//  edge.hpp
//  最大流
//
//  Created by 伏开宇 on 2017/5/10.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#ifndef edge_hpp
#define edge_hpp

#include <stdio.h>
class Edge{//边数据结构
public:
    int start;
    int end;
    int value;
    Edge* next;
    int type;//边类型
    int IsDouble;
    double r;//可靠性
    int f;//通过的流量
    bool Is_in_E;//是否属于E
    Edge(int s, int e, int v, int flag = 0, int E = 1){
        next = nullptr;
        value = v;
        start = s;
        end = e;
        type = -1;
        IsDouble = flag;//若为1则代表是无向图的逆边
        f = 0;
        Is_in_E = E;
    }
};
#endif /* edge_hpp */
