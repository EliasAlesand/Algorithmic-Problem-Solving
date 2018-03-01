//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <tuple>
#include <queue>
#include <set>
using namespace std;

/*
    Object to store distance from source to object, if it is visited or not, its neighbors and its index.
*/
struct node{
    node(int index, int dist):index{index}, dist{dist}{}
    int index;
    int dist;
    bool visited = false;
    vector<pair<int,int>> neighbors; 
};
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N;
    while(cin>>N){
        set<node*> updated;
        //Input
        int M,Q,S;
        cin>>M>>Q>>S;
        vector<node*> nodes(N);
        //Initialize source node to 0;
        if (N>0){
            nodes[S]= new node(S,0);
        }
        auto cmp = [](node * left, node * right){return left->dist>right->dist;};
        priority_queue<node*, vector<node*>,decltype(cmp)> unvisited(cmp); //Priority queue to keep track of shortest distance

        int max_dist{1000*N+1};
        for (int i=0;i<N;i++){//Initialize nodes to maximum weight
            if (i!=S){
                nodes[i]=new node(i,max_dist);
            }
            unvisited.push(nodes[i]);
        }
        for (int i=0;i<M;i++){//Adds the neighbors, essentially building the graph
            int u,v,w;
            cin>>u>>v>>w;
            nodes[u]->neighbors.push_back({v,w});
        }
        
        while(!unvisited.empty()){//Main dijkstra loop
            node * best;
            node * top = unvisited.top();
            /*
                Since the priority queue does not automatically update when values in it change, i had to find a way to see if the updated
                distances are shorter than the top of the priority queue. I store updated nodes in a set and find the minimum in it and compares it to the top of the queue.
                It is not that effective, i am aware of that but this is what i could come up with and it works.
            */
            if (updated.size()>0){
                node * min_updated;
                int min_dist = max_dist;
                for_each(updated.begin(),updated.end(),[&min_updated, &min_dist](node * n){
                    if (n->dist<min_dist){
                        min_dist = n->dist;
                        min_updated = n;
                    }
                });
                if (top->dist<min_updated->dist){
                    unvisited.pop();
                    best = top;
                }
                else {
                    best = min_updated;
                    updated.erase(min_updated);
                }
            }
            else{
                unvisited.pop();
                best = top;
            }
            
            if (!best->visited){//Updates weights of neighbors
                for_each(best->neighbors.begin(),best->neighbors.end(),[&updated,&best, &nodes, &unvisited](pair<int,int> p){
                    if (!nodes[p.first]->visited){
                        int tmp = best->dist+p.second;
                        if (tmp<nodes[p.first]->dist){
                            nodes[p.first]->dist = tmp;
                            updated.insert(nodes[p.first]);
                        }
                    }
                });
            }
            best->visited=true;
        }
        //Output
        int q_index;
        for (int i=0;i<Q;i++){
            cin>>q_index;
            int d = nodes[q_index]->dist;
            if (d!=max_dist){
                cout << nodes[q_index]->dist;
            }
            else {
                cout << "impossible";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}