//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N;
    cin>>N;
    for (int i=0;i<N;i++){
        string in;
        cin>>in;
        pair<int,int> startpos;
        startpos.first = in[0]-96;
        startpos.second = in[1]-48;
        cout <<startpos.first<<" "<<startpos.second<<endl;
        queue<pair<pair<int,int>, int> bfs;
        
    }
    return 0;
}