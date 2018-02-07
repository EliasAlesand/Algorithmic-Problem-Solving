#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>
#include <sstream>
#include <map>
#include <random>
#include <experimental/random>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N=100000;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd());
    gen.seed(1);
     //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<int> distr(0,2147483647);
    for (int i=0;i<N;i++){
        cout << distr(gen)<<endl;
    }
    cout << 0;
}