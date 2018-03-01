//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <set>
#include <queue>
#include <iomanip>
#include <unordered_map>
using namespace std;

/*
    Euclidian distance between islands with coordinates (x1,y1) and (x2,y2)
*/
double distance(double x1, double y1, double x2, double y2){
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

/*
    Solution uses Prim's method to find a minimal spanning tree handling the islands as a complete graph
*/
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N;
    cin>>N;
    for (int l=0;l<N;l++){
        int M;
        cin>>M;
        vector<pair<double,double>> points(M);
        vector<bool> used(M,false);
        vector<double> minCosts(M, 999999999);
        for (int i=0;i<M;i++){
            cin>>points[i].first;
            cin>>points[i].second;
        }
        
        auto cmp = [](pair<double,double> left, pair<double,double> right) { return left.second > right.second;};
        priority_queue<pair<double,double>, vector<pair<double,double>>, decltype(cmp)> available(cmp);

        //Start at some node
        minCosts[0] = 0;
        available.push(make_pair(0,0));
        while (!available.empty()){//Main Prim's algorithm loop
            pair<double,double> current = available.top();
            available.pop();
            used[current.first] = true;
            for (int i=0;i<M;i++){
                if (i!=current.first){
                    if(!used[i]) {
                        double dist = distance(points[current.first].first,points[current.first].second, points[i].first, points[i].second);
                        if (dist <minCosts[i]){
                            available.push(make_pair(i,dist));
                            minCosts[i]=dist;
                        }
                    }
                }
            }
        }
        //Output
        double totaldist{0};
        for (int i=0;i<M;i++){
            totaldist += minCosts[i];
        }
        cout << fixed;
        cout <<std::setprecision(3)<<totaldist<<endl;
    }
    return 0;
}