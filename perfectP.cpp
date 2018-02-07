//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    long long in;
    string o{""};
    while (cin>>in){
        if (in==0){
            break;
        }
        int decrement=1;
        int max_p;
        if (in<0){ //If input is negative i can make it positive and only check odd p, since only odd powers can result in a negative answer.
            in = -in;
            max_p=(log2(in)); //Maximum possible p
            decrement = 2; //Skip even p
            if (max_p%2 == 0){
                max_p--; //Make initial p odd
            }         
        }
        else{
            max_p=(log2(in));
        }
        bool found_integer = false;
        int p{0};
        for(int i=max_p;(found_integer==false&&i>0);i-=decrement){ //Starting with the highest possible power, decrement it and see if the ith root of the input is an integer, if it is we have found the largest p
            double tmp{0};
            tmp = pow(in,(double)1/i);
            if ((tmp-round(tmp)) < 0.000001 && (tmp-round(tmp)) > -0.000001){
                p=i;
                found_integer = true;
            }
        }
        o+=to_string(p);
        o+='\n';
        
    }
    cout << o;
    return 0;
}