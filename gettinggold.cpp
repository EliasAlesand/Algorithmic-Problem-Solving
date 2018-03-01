//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
using namespace std;
struct node{
    char type;
    bool draft = false;
    bool visited = false;
};
void print_map(vector<vector<node>> m){
    for (int i=0;i<m.size();i++){
        for (int j=0;j<m[0].size();j++){
            cout <<m[i][j].draft;
        }
        cout << endl;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    //Input
    int W,H;
    cin>>W>>H;
    vector<vector<node>> world(H,vector<node>(W)); //True world
    queue<pair<int,int>> to_visit;
    int n_of_gold{0};
    //Setting up the map
    for (int i=0;i<H;i++){
        string s;
        cin>>s;
        for (int j=0;j<W;j++){
            world[i][j].type = s[j];
            if (s[j]== 'P'){
                to_visit.push(make_pair(i,j));
                world[i][j].visited = true;
            }
            if (s[j]== 'T'){
                if (j>0) world[i][j-1].draft = true;
                if (j<W-1) world[i][j+1].draft = true;
                if (i>0) world[i-1][j].draft = true;
                if (i<H-1) world[i+1][j].draft = true;
            }
        }
    }
    while (!to_visit.empty()){ //Main loop searching through the map
        pair<int,int> curr = to_visit.front();
        to_visit.pop();
        int x = curr.first;
        int y = curr.second;
        if (world[x][y].type == 'G'){
            n_of_gold++;
        }
        if (!world[x][y].draft){
            if (y>0){
                if (!world[x][y-1].visited && world[x][y-1].type != '#') {
                    world[x][y-1].visited = true;
                    to_visit.push(make_pair(x,y-1));
                }
            }
            if (y<W-1){
                if (!world[x][y+1].visited && world[x][y+1].type != '#') {
                    world[x][y+1].visited = true;
                    to_visit.push(make_pair(x,y+1));
                }
            }
            if (x>0){
                if (!world[x-1][y].visited && world[x-1][y].type != '#') {
                    world[x-1][y].visited = true;
                    to_visit.push(make_pair(x-1,y));
                }
            }
            if (x<H-1){
                if (!world[x+1][y].visited && world[x+1][y].type != '#') {
                    world[x+1][y].visited = true;
                    to_visit.push(make_pair(x+1,y));
                }
            }
        }
    }
    //Output
    cout << n_of_gold;
    return 0;
}