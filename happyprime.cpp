//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

//Primality test
bool is_prime(int n){
    if (n<=1){
        return false;
    }
    else if (n<= 3){
        return true;
    }
    else if (n%2 == 0 || n%3 == 0){
        return false;
    }
    int i=5;
    while(i*i<=n){
        if (n%i == 0 || n%(i+2) == 0){
            return false;
        }
        i+=6;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int T;
    cin>>T;
    vector<int> happy(10001,0);//Memory of previously found numbers. -1 means not happy, 1 mean happy, 0 means unsure.
    for(int k=0;k<T;k++){
        //Input
        int K,M;
        cin>>K>>M;
        vector<bool> has_used(10001,false);//Used to lookup if some number has been used in this test case
        vector<int> used_numbers;//Used to update happiness of all used numbers. If A is happy and B is the sum of squared digits of A, B is also happy.
        int tmp = M;
        if (!is_prime(M)){
            cout << K<<" "<<M<<" "<<"NO"<<endl;
        }
        else{
            while(tmp!=1 && !has_used[tmp] && happy[tmp]==0){
                used_numbers.push_back(tmp);
                has_used[tmp]=true;
                string s = to_string(tmp);
                tmp = 0;
                for(int i=0;i<s.size();i++){
                    tmp+=pow(s[i]-48, 2);
                }
            }
            //Output
            if (tmp == 1 || happy[tmp] == 1){
                cout << K<<" "<<M<<" "<<"YES"<<endl;
                for(int i=0;i<used_numbers.size();i++){
                    happy[used_numbers[i]]=1;
                }
            }
            else{
                cout << K<<" "<<M<<" "<<"NO"<<endl;
                for(int i=0;i<used_numbers.size();i++){
                    happy[used_numbers[i]]=-1;
                }
            }
        }
    }
    return 0;
}