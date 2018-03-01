//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
#include <unordered_map>

/*
    My solution implements the Edmonds-Karp algorithm to find the maximum flow of a graph with a single source and a single sink.
    I use dijkstras to find the shortest augmenting path each iteration.
*/
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N,M,S,T;
    cin>>N>>M>>S>>T;
    const long long MAX_FLOW{2147483648};
    long long total_flow{0};
    vector<vector<int>> neighbors(N);
    vector<vector<long long>> caps(N,vector<long long>(N,0));//Capacity of each edge. Does not change
    vector<vector<long long>> edgeflows(N,vector<long long>(N,0));//Current flow in an edge, will change over time
    vector<tuple<int,int,int>> result;

    //Input
    for (int i=0;i<M;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edgeflows[u][v]=w;
        caps[u][v]=w;
        neighbors[u].push_back(v);
        neighbors[v].push_back(u);
    }
    long long sub_flow{-1};

    while(sub_flow != 0){//Edmonds-Karps algorithm
        vector<long long> flow(N,0);
        vector<long long> maxFlowNeighbor(N,-1);
        flow[S]=MAX_FLOW;
        auto cmp = [flow](long long left, long long right) { return flow[left] < flow[right]; };
        priority_queue<long long, vector<long long>, decltype(cmp)> unvisited(cmp);
        unvisited.push(S);
        while(!unvisited.empty()){//Dijkstra loop
            int best = unvisited.top();
            unvisited.pop();
            for_each(neighbors[best].begin(),neighbors[best].end(),[&maxFlowNeighbor, &best, &edgeflows, &flow, &unvisited](int neighbor){
                int tmpflow = min(flow[best], edgeflows[best][neighbor]);
                if (tmpflow>flow[neighbor]){
                    //Update flows at neighbor node, save the current node to backtrack later.
                    flow[neighbor] = tmpflow;
                    maxFlowNeighbor[neighbor]=best;
                    unvisited.push(neighbor);
                }
            });
        }
        sub_flow = flow[T];
        total_flow += sub_flow;
        int n = T;
        //Update edgeflows
        while(maxFlowNeighbor[n]!=-1){
            int adj = maxFlowNeighbor[n];
            edgeflows[adj][n] -= sub_flow;
            edgeflows[n][adj] += sub_flow;
            n = adj;
        }
    }
    //Output
    for (int i=0;i<N;i++)
    	for (int j=0;j<N;j++)
    		if (edgeflows[i][j] < caps[i][j] && caps[i][j] > 0)
    			result.push_back({i,j,caps[i][j]-edgeflows[i][j]});
    cout <<N<<" "<< total_flow<<" "<<result.size()<<endl;
    for(const auto & n : result ) {
        cout << get<0>(n) << " " << get<1>(n) << " " << get<2>(n) << endl;
    }
    return 0;
}