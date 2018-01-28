//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
vector<vector<int>> values;

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    double C_in;
    int N,C;

    //Inputs
    while (cin>>C_in>>N){
        string o={""};
        C = (int)C_in;
        int w[N+1];
        int v[N+1];
        for (int i=0;i<N;i++){
            int value, weight;
            cin >> value>>weight;
            v[i+1]=value;
            w[i+1]=weight;
        } 
                

        values = vector<vector<int> >(N+1,vector<int>(C+1));
        for (int i = 0;i<C;i++){
            values[0][i] = 0;
        }
        //Updates maximized values from 0...i for weights less than or equal to j
        for (int i = 1;i<=N;++i){
            for (int j = 0;j<=C;++j){
                if (w[i] > j){
                    values[i][j] = values[i-1][j];
                }
                else{
                    values[i][j]=max(values[i-1][j],values[i-1][j-w[i]] + v[i]);
                }
            }
        }
        
        //Fetches the chosen indexes by checking how much the values change in each weight increase in the matrix which were calculated previously
        vector<int> chosen_indexes;
        int tmp = C;
        for (int i = N;i>0;i--){
            if (values[i][tmp] - values[i-1][tmp - w[i]] == v[i]){
                tmp = tmp - w[i];
                chosen_indexes.push_back(i-1);
            }
        }

        //Printouts
        o += to_string(chosen_indexes.size());
        o += "\n";
        for (int i = 0;i<chosen_indexes.size();i++){
            o += to_string(chosen_indexes[i]);
            o += " ";
        }
        o += "\n";
        cout <<o;
        
    }
}