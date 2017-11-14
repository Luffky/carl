//
//  main.cpp
//  VLSI-CHIP-TEST-4-6
//
//  Created by 伏开宇 on 2017/3/4.
//  Copyright © 2017年 伏开宇. All rights reserved.
//

#include <iostream>
using namespace std;
//芯片类
class Chip{
private:
    int goodness;
    int number;
public:
    int GetGoodness(){
        return goodness;
    }
    int GetNumber(){
        return number;
    }
    void SetGoodness(int a){
        goodness = a;
    }
    void SetNumber(int a){
        number = a;
    }
};
//芯片互测
int Judge(Chip a, Chip b){
    int ResultA = 0;
    int ResultB = 0;
    if(a.GetGoodness() == 1){
        ResultA = b.GetGoodness();
    }
    else{
        ResultA = arc4random_uniform(2);
    }
    if(b.GetGoodness() == 1){
        ResultB = a.GetGoodness();
    }
    else{
        ResultB = arc4random_uniform(2);
    }
    
    return ResultA and ResultB;
    
}
//搜索芯片递归步骤
Chip * Search(Chip * a, int n){
    if(n > 1){
        Chip *b = new Chip[n];
        int j = 0;
        int i = 0;
        for(; i+1 < n; i = i + 2){
            if(Judge(a[i], a[i+1]) == 1){
                b[j] = a[i];
                j++;
            }
        }
        if(i < n){
            if(j % 2 == 0){
                b[j] = a[i];
                j++;
            }
        }
        return Search(b, j);
    }
    else
        return a;

}


int main(int argc, const char * argv[]) {
    //srand((unsigned)time(NULL));
    int n = 20;
    int NumberoOfBad = n/2-1;
    Chip *a = new Chip[n];
   
    for(int i = 0; i<n; i++){
        a[i].SetNumber(i);
        if(NumberoOfBad != 0){
            a[i].SetGoodness(arc4random_uniform(2));
            if(a[i].GetGoodness() == 0)
                NumberoOfBad --;
        }
        else
            a[i].SetGoodness(1);
    }
    for(int i = 0; i<n; i++){
        cout<<a[i].GetNumber()<<" "<<a[i].GetGoodness()<<endl;
    }
    cout<<endl;
    Chip *b;
    b = Search(a, n);
    cout<<b[0].GetNumber()<<" "<<b[0].GetGoodness()<<endl;
    
//
//    for(int i = 0; i<n; i++){
//        cout<<b[i].GetNumber()<<" "<<b[i].GetGoodness()<<endl;
//    }
    return 0;
}
