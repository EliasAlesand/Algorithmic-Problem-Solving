//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
using namespace std;

/*
    I calculate the distance between every point on each polygon to every line segment on the other polygon.
    The lowest distance will be the answer.
*/

//Calculating the distance between the point (p1,p2) and the line that is defined by points (a1,a2) and (b1,b2)
double distance(int p1,int p2,int a1,int a2,int b1,int b2){
    double l_sq = pow(a1-b1,2)+pow(a2-b2,2);
    double t =max(0.0, min(1.0, ((p1-a1)*(b1-a1)+(p2-a2)*(b2-a2))/l_sq));
    double proj_x = a1+t*(b1-a1);
    double proj_y = a2+t*(b2-a2);
    return sqrt(pow(p1-proj_x,2)+pow(p2-proj_y,2));
}

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int T;
    cin>>T;
    for(int k=0;k<T;k++){
        //Input
        int N1;
        cin>>N1;
        double min_dist=3000;
        vector<pair<int,int>> p_inner(N1);
        for(int i=0;i<N1;i++){
            int a,b;
            cin>>a>>b;
            p_inner[i].first = a;
            p_inner[i].second = b;
        }
        int N2;
        cin>>N2;
        vector<pair<int,int>> p_outer(N2);
        for(int i=0;i<N2;i++){
            int a,b;
            cin>>a>>b;
            p_outer[i].first = a;
            p_outer[i].second = b;
        }
        // Check all distances
        for(int i=0;i<N1;i++){
            for(int j=0;j<N2;j++){
                int next_i = i+1;
                int next_j = j+1;
                if (i==(N1-1))
                    next_i = 0;
                if (j==(N2-1))
                    next_j = 0;
                double d1 = distance(p_inner[i].first, p_inner[i].second, p_outer[j].first, p_outer[j].second, p_outer[next_j].first, p_outer[next_j].second);
                double d2 = distance(p_outer[j].first, p_outer[j].second, p_inner[i].first, p_inner[i].second, p_inner[next_i].first, p_inner[next_i].second);
                if (d1<min_dist){
                    min_dist = d1;
                }
                if (d2<min_dist){
                    min_dist = d2;
                }
            }
        }
        //Output. Divide by 2 since i want the radius.
        cout <<fixed<<setprecision(8)<< min_dist/2<<endl;
    }
    return 0;
}