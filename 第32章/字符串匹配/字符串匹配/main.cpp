//
//  main.cpp
//  字符串匹配
//
//  Created by 伏开宇 on 2017/5/16.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
#include <vector>
#include <math.h>
#include <map>
using namespace std;
//字符串分割
vector<std::string> split(std::string str,std::string pattern)  //按指定字符分割字符串
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str+=pattern;//扩展字符串以方便操作
    int size = (int)str.size();
    
    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            std::string s=str.substr(i,pos-i);
            if(s.compare("?") == 0){//如果该数据有缺失值，则丢弃
                std::vector<std::string> temp;
                temp.push_back("");
                return temp;
            }
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}
//字符串比较
int Compare(string a, string b){
    int n = (int) a.length();
    int i = 0;
    for (; i < n; i++) {
        if(a[i] != b[i]){
            if(i == 0)
                return i;
            return i - 1;
        }
    }
    return i - 1;
}
//朴素字符串匹配算法
void NaiveStringMatcher(string T, string P){
    int n = (int) T.length();
    int m = (int) P.length();
    for (int i = 0; i <= n - m; i++) {
        string u = T.substr(i, m);
        if (u.compare(P) == 0) {
            cout<<P<<"在"<<T<<"以偏移"<<i<<"出现"<<endl;
        }
    }
}
//练习32.1-2
void NaiveStringMatcher1(string T, string P){
    int n = (int) T.length();
    int m = (int) P.length();
    for (int i = 0; i <= n - m; i++) {
        string u = T.substr(i, m);
        int flag = Compare(P, u);
        if (flag == m - 1) {
            cout<<P<<"在"<<T<<"以偏移"<<i<<"出现"<<endl;
        }
        i += flag;
    }
}

//练习32.1-4
void NaiveStringMatcherGap(string T, string P){
    vector<string> sub = split(P, "/");
    int n = (int) T.length();
    int k = 0;
    for (int i = 0; i <= n; i++) {
        int m = (int) sub[k].length();
        for (int j = i; j <= n - m; j++, i++) {
            string u = T.substr(j, m);
            if(sub[k].compare(u) == 0){
                i = j + m - 1;
                k++;
                break;
            }
        }
        if(k == sub.size()){
            cout<<"P在T中出现"<<endl;
            return;
        }
    }
    cout<<"P未在T中出现"<<endl;
}
//32.2 RabinKarp算法**********
int CharToInt(char a){
    return (int) a - 97;
}
void RabinKarp(string T, string P, int d, int q){
    int n = (int) T.length();
    int m = (int) P.length();
    int h = (int) pow(d, m - 1) % q;
    int p = 0;
    int t = 0;
    for (int i = 0 ; i < m; i++) {
        p = (d * p + CharToInt(P[i])) % q;
        t = (d * t + CharToInt(T[i])) % q;
    }
    for (int i = 0; i <= n - m; i++) {
        if(p == t){
            string u = T.substr(i, m);
            if(u.compare(P) == 0)
                cout<<"Pattern occurs with shift"<<i<<endl;
        }
        if(i < n - m)
            t = (d * (t - CharToInt(T[i]) * h) + CharToInt(T[i + m])) % q;
    }
}
//练习32.3 //未测试
void RabinKard2D(vector<string> T, vector<string> P, int d, int q){
    int n = (int) T.size();
    int m = (int) P.size();
    map<string, int*> h;
    int* temp = new int[m];
    for (int i = 0; i < m; i++) {
        temp[i] = (int) pow(d , m * m - m * i - 1) % q;
    }
    int* temp1 = new int[m];
    for (int i = 0; i < m; i++) {
        temp[i] = (int) pow(d , m * m - i - 1) % q;
    }
    int* temp2 = new int[m];
    for (int i = 0; i < m; i++) {
        temp[i] = (int) pow(d , m * m - i * m) % q;
    }
    int* temp3 = new int[m];
    for (int i = 0; i < m; i++) {
        temp[i] = (int) pow(d , m - 1 - i) % q;
    }
    h["left"] = temp;
    h["up"] = temp1;
    h["right"] = temp2;
    h["down"] = temp3;
    int p = 0;
    int t = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            p = (d * p + CharToInt(P[i][j])) % q;
            t = (d * t + CharToInt(T[i][j])) % q;
        }
    }
    for (int i = 0; i <= n - m; i++) {
        if(i % 2 == 0){//右移
            for (int j = 0; j <= n - m; j++) {
                if(p == t){
                    int flag = 0;
                    for (int k = 0; k < m; k++) {
                        string u = T[i + k].substr(j, m);
                        if(u.compare(P[k]) != 0){
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                        cout<<"Pattern occurs with shift"<<i<<","<<j<<endl;
                }
                if(j < n - m){
                    for (int k = 0; k < m; k++) {
                        t = (d * (t - h["left"][k] * CharToInt(T[i + k][j])) + h["right"][k] * CharToInt(T[i + k][j + m - 1]));
                    }
                }
            }
            for (int j = 0; j < m; j++) {
                t = ((int) pow(d, m) * (t - h["up"][j] * CharToInt(T[i][j])) + h["down"][j] * CharToInt(T[i + m - 1][j]));
            }
        }
        else{ //左移中
            for (int j = n - m; j >= 0; j--) {
                if(p == t){
                    int flag = 0;
                    for (int k = 0; k < m; k++) {
                        string u = T[i + k].substr(j, m);
                        if(u.compare(P[k]) != 0){
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 0)
                        cout<<"Pattern occurs with shift"<<i<<","<<j<<endl;
                }
                if(j > 0){
                    for (int k = 0; k < m; k++) {
                        t = ((t - h["right"][k] * CharToInt(T[i + k][j + m - 1])) / d + h["left"][k] * CharToInt(T[i + k][j]));
                    }
                }
            }
            for (int j = 0; j < m; j++) {
                t = ((int) pow(d, m) * (t - h["up"][j] * CharToInt(T[i][j])) + h["down"][j] * CharToInt(T[i + m - 1][j]));
            }
        }
    }
    
}
//32.3 有限自动机字符串匹配******
class Trans{
public:
    vector<map<char, int>> f;
    int m; //模式长度
    int d; //字符个数
    char* form; //字符表
    string P; //模式
    Trans(int m, int d, char* form, string P){
        this->m = m;
        this->d = d;
        this->form = form;
        this->P = P;
    }
    static bool Is_Tail(string P, int k ,int q, char a){
        if(k == 0)
            return 1;
        string u = P.substr(0, k);
        string v = P.substr(0, q);
        v = v + a;
        v = v.substr(q - k + 1, k);
        if(v.compare(u) == 0)
            return 1;
        else
            return 0;
    }
    void Train(){ //构造P的自动机
        for (int q = 0; q <= m; q ++) {
            map<char, int> temp;
            for (int i = 0; i < d; i++) {
                char a = form[i];
                int k = min(m + 1, q + 2);
                while (1) {
                    k = k - 1;
                    if(Is_Tail(P, k, q, a))
                        break;
                }
                temp[a] = k;
            }
            f.push_back(temp);
        }
    }
    
    void FiniteAutomatonMatcher(string T){//匹配
        int n = T.length();
        int q = 0;
        for (int i = 0; i < n; i++) {
            q = f[q][T[i]];
            if(q == m)
                cout<<"Patter occurs with shift "<<i - m + 1<<endl;
        }
    }
};
//练习32.3-4 匹配两个模式的自动机
class TransDouble{
public:
    vector<map<char, vector<int>>> f;
    int m1;
    int m2;
    int d; //字符个数
    char* form; //字符表
    string P1; //模式1
    string P2; //模式2
    TransDouble(int m1, int m2, int d, char* form, string P1, string P2){
        this->form = form;
        this->d = d;
        this->P1 = P1;
        this->P2 = P2;
        this->m1 = m1;
        this->m2 = m2;
        
    }
    static bool Is_Tail(string P, int k ,int q, char a){
        if(k == 0)
            return 1;
        string u = P.substr(0, k);
        string v = P.substr(0, q);
        v = v + a;
        v = v.substr(q - k + 1, k);
        if(v.compare(u) == 0)
            return 1;
        else
            return 0;
    }
    void Train(){ //假设m1 >= m2
        for (int q = 0; q <= m1; q ++) {
            map<char, vector<int>> temp;
            for (int i = 0; i < d; i++) {
                char a = form[i];
                int k = min(m1 + 1, q + 2);
                while (1) {
                    k = k - 1;
                    if(Is_Tail(P1, k, q, a))
                        break;
                }
                vector<int> v;
                v.push_back(k);
                temp[a] = v;
            }
            f.push_back(temp);
        }
        for (int q = 0; q <= m2; q ++) {
            for (int i = 0; i < d; i++) {
                char a = form[i];
                int k = min(m2 + 1, q + 2);
                while (1) {
                    k = k - 1;
                    if(Is_Tail(P2, k, q, a))
                        break;
                }
                f[q][a].push_back(k);
            }
        }
    }
    void FiniteAutomatonMatcher(string T){//匹配
        int n = T.length();
        int q1 = 0;
        int q2 = 0;
        for (int i = 0; i < n; i++) {
            q1 = f[q1][T[i]][0];
            q2 = f[q2][T[i]][1];
            if(q1 == m1)
                cout<<"Patter1 occurs with shift "<<i - m1 + 1<<endl;
            if(q2 == m2)
                cout<<"Patter2 occurs with shift "<<i - m2 + 1<<endl;
        }
    }
};
//练习32.3-5 带有间隔字符的模式
class Trans1{
public:
    vector<vector<map<char, int>>> f;
    int d; //字符个数
    char* form; //字符表
    vector<string> Ps;
    Trans1(int d, char* form, string P){
        this->d = d;
        this->form = form;
        this->Ps = split(P, "/");
    }
    static bool Is_Tail(string P, int k ,int q, char a){
        if(k == 0)
            return 1;
        string u = P.substr(0, k);
        string v = P.substr(0, q);
        v = v + a;
        v = v.substr(q - k + 1, k);
        if(v.compare(u) == 0)
            return 1;
        else
            return 0;
    }
    void Train(){ //构造P的自动机
        for (int i = 0; i < Ps.size(); i++) {
            string P = Ps[i];
            vector<map<char, int>> temp1;
            int m = (int) P.length();
            for (int q = 0; q <= m; q ++) {
                map<char, int> temp;
                for (int i = 0; i < d; i++) {
                    char a = form[i];
                    int k = min(m + 1, q + 2);
                    while (1) {
                        k = k - 1;
                        if(Is_Tail(P, k, q, a))
                            break;
                    }
                    temp[a] = k;
                }
                temp1.push_back(temp);
            }
            f.push_back(temp1);
        }
    }
    
    void FiniteAutomatonMatcher(string T){//匹配
        int n = (int) T.length();
        int q = 0;
        int k = 0;
        int start = 0;
        for (int i = 0; i < n; i++) {
            q = f[k][q][T[i]];
            if(q == f[k].size() - 1){
                if(k == 0)
                    start = i - f[k].size() + 2;
                q = 0;
                k++;
                
                if(k == f.size()){
                    cout<<"Pattern P occurs with shift  "<<start<<endl;
                    break;
                }
            }
                
        }
    }
};
//kmp算法************************************
int* ComputePrefixFunction(string P){
    int m = (int) P.length();
    int* pai = new int[m + 1];
    pai[1] = 0;
    int k = 0;
    for (int q = 1; q < m; q++) {
        while (k > 0 and P[k] != P[q]) {
            k = pai[k];
        }
        if(P[k] == P[q])
            k = k + 1;
        
        pai[q + 1] = k;
    }
    return pai;
}
int KmpMatcher(string T, string P){
    int n = (int) T.length();
    int m = (int) P.length();
    int* pai = ComputePrefixFunction(P);
    int q = 0;
    int flag = 0;
    for (int i = 0; i < n; i++) {
        while (q > 0 and P[q] != T[i]) {
            q = pai[q];
        }
        if(P[q] == T[i])
            q = q + 1;
        if(q == m){
            cout<<"Patter occurs with shift"<<i - m + 1<<endl;
            q = pai[q];
            flag = 1;
        }
    }
    return flag;
}
//练习32.4-3
void KmpMatcher2(string T, string P){
    string u = P + T;
    int* pai = ComputePrefixFunction(u);
    for (int i = 1; i <= u.length(); i++) {
        if(pai[i] == P.length())
            cout<<i - P.length()<<endl;
    }
}
//练习32.4-7 判断循环旋转
int IsIterateRotate(string T, string P){
    string u = T + T;
    if(T.length() == P.length())
        return KmpMatcher(u, P);
    else
        return 0;
}
//练习32.4-8 线性时间预处理自动机
class TransModified{
public:
    vector<map<char, int>> f;
    int m; //模式长度
    int d; //字符个数
    char* form; //字符表
    string P; //模式
    TransModified(int m, int d, char* form, string P){
        this->m = m;
        this->d = d;
        this->form = form;
        this->P = P;
    }
    static bool Is_Tail(string P, int k ,int q, char a){
        if(k == 0)
            return 1;
        string u = P.substr(0, k);
        string v = P.substr(0, q);
        v = v + a;
        v = v.substr(q - k + 1, k);
        if(v.compare(u) == 0)
            return 1;
        else
            return 0;
    }
    void Train(){ //构造P的自动机
        int* pai = new int[m + 1];
        pai[1] = 0;
        int k = 0;
        for (int q = 1; q < m; q++) {
            while (k > 0 and P[k] != P[q]) {
                k = pai[k];
            }
            if(P[k] == P[q])
                k = k + 1;
            pai[q + 1] = k;
        }
        for (int q = 0; q <= m; q ++) {
            map<char, int> temp;
            for (int i = 0; i < d; i++) {
                char a = form[i];
                if(q != 0){
                    if(P[q] == a and q != m)
                        temp[a] = q + 1;
                    else{
                        temp[a] = f[pai[q]][a];
                    }
                }
                else{
                    if(P[q] == a)
                        temp[a] = q + 1;
                    else{
                        temp[a] = q;
                    }
                }
            }
            f.push_back(temp);
        }
    }
    
    void FiniteAutomatonMatcher(string T){//匹配
        int n = T.length();
        int q = 0;
        for (int i = 0; i < n; i++) {
            q = f[q][T[i]];
            if(q == m)
                cout<<"Patter occurs with shift "<<i - m + 1<<endl;
        }
    }
};
//思考题32-1  基于重复因子的字符串匹配
bool If_repeat(string a, string b){
    string u;
    for (int i = 0; i < a.length() / b.length(); i++) {
        u += b;
    }
    if(a.compare(u) == 0)
        return 1;
    else
        return 0;
}
int FindLargestRepeat(string P){
    int m = P.length();
    int* pai = new int[m + 1];
    pai[1] = 0;
    int k = 0;
    for (int q = 1; q < m; q++) {
        if(k > 0 and P[k] != P[q])
            k = pai[k];
        if(P[k] == P[q])
            k++;
        pai[q + 1] = k;
    }
    int max = 1;
    for (int i = 2; i < m ; i++) {
        int k = i - pai[i];
        if(i % k == 0 and If_repeat(P.substr(0, i), P.substr(0, k))){
            if(max < i / k)
                max = i / k;
          
        }
    }
    return max;
}
//32-1.c //暂未解决
void RepetitionMatcher(string T, string P){
    int m = P.length();
    int n = T.length();
    int k = FindLargestRepeat(P);
    int q = 0;
    int s = 0;
    while (s <= n - m) {
        if(T[s + q] == P[q]){
            q++;
            if(q == m )
                cout<<"Pattern occur with shift "<<s;
        }
        if(q == m  or T[s + q] != P[q]){
            s = s + max(1, (int)ceil(q / k));
            q = 0;
        }
    }
}
int main(int argc, const char * argv[]) {
    string T = "baababacababacabaa";
    string P = "ababaca";
    char* form = new char[3];
    form[0] = 'a';
    form[1] = 'b';
    form[2] = 'c';
    RepetitionMatcher(T, P);
    return 0;
}
