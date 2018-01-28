//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

struct obj{
    obj() = default;
    obj *parent;
};
struct UnionFind{
    UnionFind(vector<obj> tree):tree{tree}{}
    vector<obj> tree;
    //"adds" the given integers to the tree and makes the root of b point to the root of a
    void merge(int a, int b){
        if (tree[a].parent == nullptr){
            tree[a].parent = &tree[a];
        }
        if (tree[b].parent == nullptr){
            tree[b].parent = &tree[b];
        }
        root(tree[b])->parent = root(tree[a]);
    }
    //Checks if the roots of the trees of a and b are the same, if so, they are in the same set.
    bool same(int a, int b){
        if (tree[a].parent == nullptr || tree[b].parent == nullptr){
            return false;
        }
        else
        if (root(tree[a])==root(tree[b])){
            return true;
        }
        else {
            return false;
        }
    }
    //Updates parent of a to point directly to the root in it's tree, returns the root.
    obj * root(obj & a){
        if (a.parent != &a){
            a.parent = root(*a.parent);
        }
        return a.parent;
    }
};
int main(){
    //Input
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N,Q;
    cin >> N>>Q;
    string o{""};
    UnionFind uf{UnionFind(vector<obj>(N))};
    for (int i= 0;i<Q;i++){
        char operation;
        int a, b;
        cin>>operation>>a>>b;
        if (operation == '='){
            uf.merge(a,b);
        }
        else{
            //Output
            if (a==b) {o+= "yes\n";}
            else{
                if (uf.same(a,b)){
                    o+= "yes\n";
                }
                else{
                    o+= "no\n";
                }
            }
        }
    }
    cout << o;
    return 0;
}

