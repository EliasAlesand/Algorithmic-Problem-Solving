//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
using namespace std;

/*
    This problem can be seen as a maxflow problem. The goal is to distribute the points such that no team gets more points than team N.
    From the sink there are an edge to each match that can carry two points. From each match there are an edge to each team in that match. From every team there is an edge to the sink
    that can carry the maximum points without that team getting more than the maximum for team N. If all points can be distributed it means that the matches can be played so that team N wins.
*/
int main(){
    
    
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int n_of_teams;
    string o{""};
    while (cin>>n_of_teams){
        
        if (n_of_teams == -1){
            cout<< o;
            
            return 0;
        }
        int n_of_matches; //Total number of matches
        cin>>n_of_matches;
        int n_of_matches_for_N = 0; //Number of matches that N participates in
        int N,M,S,T;
        N = n_of_teams+n_of_matches+1; //Number of nodes
        M = n_of_matches+2*(n_of_teams-1); //Number of edges
        S=0; //Source
        T=N-1; //Sink
        const long long MAX_FLOW{2147483648};
        long long total_flow{0};
        vector<vector<int>> neighbors(N);
        vector<vector<long long>> caps(N,vector<long long>(N,0));//Capacity of each edge. Does not change
        vector<vector<long long>> edgeflows(N,vector<long long>(N,0));//Current flow in an edge, will change over time
        
        vector<int> points(n_of_teams);
        vector<pair<int,int>> matches(n_of_matches);
        for (int i=0;i<n_of_teams;i++){
            int p;
            cin>>p;
            points[i]=p;
        }
        //team N points if the team wins all remaining matches
        int team_N_max = points[n_of_teams-1];
        
        for (int i=0;i<n_of_matches;i++){
            
            int a,b;
            cin>>a>>b;
            matches[i].first = a;
            matches[i].second = b;
            
            if (a == n_of_teams || b == n_of_teams){ //If team N is playing in the match, don't include it in the graph.
                team_N_max +=2; // Assume it wins the match.
                n_of_matches_for_N++;
                if (a == n_of_teams){ //Used to print the results
                    edgeflows[i+1][n_of_matches+a] = 0;
                }
                else{
                    edgeflows[i+1][n_of_matches+a] = 2;
                }
            }
            else{
                //Give 2 points to each match
                caps[S][i+1]=2;
                edgeflows[S][i+1]=2;
                neighbors[S].push_back(i+1);
                neighbors[i+1].push_back(S);
                //Distribute the 2 points between the 2 teams playing the match
                caps[i+1][n_of_matches+a] = 1000;
                caps[i+1][n_of_matches+b] = 1000;
                edgeflows[i+1][n_of_matches+a] = 2;
                edgeflows[i+1][n_of_matches+b] = 2;
                neighbors[i+1].push_back(n_of_matches+a);
                neighbors[n_of_matches+a].push_back(i+1);
                neighbors[i+1].push_back(n_of_matches+b);
                neighbors[n_of_matches+b].push_back(i+1);
            }
        }
        for (int i=n_of_matches+1;i<N-1;i++){
            caps[i][T] = team_N_max-points[i-(n_of_matches+1)] -1; //Every team is allowed to get maximum 1 point less than team N.
            edgeflows[i][T] = team_N_max-points[i-(n_of_matches+1)] -1;
            neighbors[i].push_back(T);
            neighbors[T].push_back(i);
            
        }
        if (n_of_matches==0){//Special case for M=0
            bool N_highest = true;
            for (int i=0;i<n_of_teams;i++){
                if(points[i]>=points[n_of_teams-1]){
                    N_highest = false;
                }
            }
            if (!N_highest){
                o+="NO\n";
                continue;
            }
            else {
                o+="\n";
                continue;
            }
        }
        long long sub_flow{-1};
        int test = 0;
        while(sub_flow != 0){//Edmonds-Karps algorithm
            bool easy_path_found = false;

            for (int i=0;i<(n_of_matches-n_of_matches_for_N);i++){//First try to find a quick path in the flow graph with cost 2.
                if (edgeflows[S][i+1]==2){
                    if (edgeflows[i+1][n_of_matches+matches[i].first] == 2 && edgeflows[n_of_matches+matches[i].first][T] >= 2){
                        sub_flow = 2;
                        edgeflows[i+1][n_of_matches+matches[i].first]-=2;
                        edgeflows[n_of_matches+matches[i].first][i+1]+=2;
                        edgeflows[n_of_matches+matches[i].first][T]-=2;
                        edgeflows[T][n_of_matches+matches[i].first]-=2;
                        edgeflows[S][i+1]-=2;
                        edgeflows[i+1][S]+=2;
                        easy_path_found = true;
                        total_flow+=sub_flow;
                        break;
                    }
                    if (edgeflows[i+1][n_of_matches+matches[i].second] == 2 && edgeflows[n_of_matches+matches[i].second][T] >= 2){
                        sub_flow = 2;
                        edgeflows[i+1][n_of_matches+matches[i].second]-=2;
                        edgeflows[n_of_matches+matches[i].second][i+1]+=2;
                        edgeflows[n_of_matches+matches[i].second][T]-=2;
                        edgeflows[T][n_of_matches+matches[i].second]-=2;
                        edgeflows[S][i+1]-=2;
                        edgeflows[i+1][S]+=2;
                        easy_path_found = true;
                        total_flow+=sub_flow;
                        break;
                    }
                }
            }
            if (easy_path_found == false){ //Otherwise use dijkstra
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
        }
        //Output. Uses the flow in the graph to print the results.
        
        if (total_flow == (n_of_matches-n_of_matches_for_N)*2){
           for (int i=1;i<n_of_matches+1;i++){
               o+=to_string(edgeflows[i][n_of_matches+matches[i-1].first])+" ";
           }
        }
        else {
            o+="NO";
        }
        o+='\n';
        
    } 
    
    return 0;
}