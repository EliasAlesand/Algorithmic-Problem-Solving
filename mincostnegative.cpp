//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <tuple>
using namespace std;
/*
    Solution uses the Bellman-Ford algorithm to find minimum cost in a graph with negative weights. It is less efficient than dijkstra but is more flexible since it can handle negative
    weights and detect cycles. 
*/
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N, M, Q, S;
    while(cin>>N){
        cin>>M>>Q>>S;
        if (N==0 && M==0 && Q==0 && S==0){
            break;
        }
        int max_weight = 2000*M+1;

        vector<tuple<int,int,int>> edges(M);
        vector<int> weights(N, max_weight);
        weights[S]=0;
        
        for (int i=0;i<M;i++){
            int u,v,w;
            cin>>get<0>(edges[i]);
            cin>>get<1>(edges[i]);
            cin>>get<2>(edges[i]);
        }
        /*
            Since there can be negative edges i have to search through all edges N times to be sure to find the optimum. When there are no negative weights you can greedily find the
            optimal solution like in dijkstra's algorithm but in this case o have to search through the graph multiple times.
            If an edge from node u to v gives a lower weight than the current weight at v, update weight at v. If this is done for all edges once for every node, the optimum is found.
        */
        for(int i=0;i<N;i++){ //Main Bellman-Ford algorithm loop
            for(tuple<int,int,int> edge : edges){
                int u = get<0>(edge);
                int v = get<1>(edge);
                int w = get<2>(edge);
                if (weights[u]+w < weights[v] && weights[u] != max_weight){ 
                    weights[v] = weights[u] + w;
                }
            }
        }
        /*  
            Detecting cycles:
            If i can still lower the weight at some node, there must exist a cycle which gives a negative weight. This is because the above loop should have made it impossible
            to lower weights more if there does not exist a cycle of negative weight. By doing this N times i can set all weights that can be reached through a negative cycle to -max_weight.
        */
        vector<int> cycle;
        for (int i=0;i<N;i++){
            for(tuple<int,int,int> edge : edges){
                int u = get<0>(edge);
                int v = get<1>(edge);
                int w = get<2>(edge);
                if (weights[u]+w < weights[v] && weights[u]!=max_weight){ 
                    weights[v] = -max_weight;
                }
            }
        }
        
        for (int i=0;i<Q;i++){
            int query;
            cin >> query;
            if (weights[query]==-max_weight){
                cout <<"-Infinity"<<endl;
            }
            else if (weights[query]==max_weight){
                cout <<"Impossible"<<endl;
            }
            else{
                cout << weights[query]<<endl;
            }
        }
        cout << endl;
    }
    return 0;
}