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
    
    //Inputs numbers into vector v
    int N;
    cin >> N;
    string o{""};
    vector<int> v(N);
    vector<int> n_of_vertices(N+1);
    bool error = false;
    //Using a priority queue that puts the smallest number on top. The node on top is the one to be cut.
    //This makes sure the lowest valued node always is the one to be cut, regardless of in which order they are pushed to the queue
    priority_queue<int,vector<int>,std::greater<int>> q;
    
    for (int i = 0;i<N;i++){
        int num;
        cin >> num;
        v[i]=num;
        //Everytime a node appears in the input list it means that another node is connected to it and has to be removed before it. 
        //Count the number of vertices that has to be removed before node num can be removed to determine which ones are leaves from the start
        n_of_vertices[num-1]++;
    }
    //If the number of vertices (that should be removed before node i) of a node i is equal to 0 it is a leaf and is a candidate for being removed first. 
        for (int i = 0;i<N+1;i++){
            if (n_of_vertices[i]==0){
                q.push(i+1);
            }
        }
    //Since a tree has no cycles, there will always be at least two leaves. Therefore the highest valued node definetely has to be left until last.
    if (v[N-1]!=N+1){
        error = true;
        o = "Error";
    }
    if(!error){
        //For every node in the input,pop the stack. Also update the number of nodes that should be removed before it. If it is 0, add it to the queue since it is now a candidate for being removed.
        for (int i = 0;i<N;i++){
            o+=to_string(q.top());
            o+="\n";
            q.pop();
            n_of_vertices[v[i]-1]--;
            if (n_of_vertices[v[i]-1] == 0){
                q.push(v[i]);
            }
        }
    }
    cout << o;

    return 0;
}