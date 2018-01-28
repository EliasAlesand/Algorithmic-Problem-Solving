#include <iostream>
using namespace std;

static int N,Q;

//Resets the rightmost bit to get a path to the root expressed in binary
int reset_right_bit(int n){
    return n&(n-1);
}
/*Updates the tree at node index. Also updates the parent if it is to the right of the current index
So adding to index 7 will update 7 and 8 imagining a tree looking like this:
                8
              /   \
            4       10
          /   \    /
        2      6  9
       / \    / \
      1   3  5   7
*/
void add(int index,long sumtree[], long delta){
    while(index < N){
        sumtree[index] += delta;
        index = index + (index & -index);
    }
}

/*
Since adding also updates parts of the tree it is faster to calculate the sums.
Adds index to answer and also it's parent if it is to the left of the current index.
Using above tree, calculating the sums at index 7 only have to sum 7, 6 and 4.
*/
long sum(int index, long sumtree[]){
    long ans = 0;
    while(index != 0){
        ans += sumtree[index];
        index = reset_right_bit(index);
    }
return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    cin >>N>>Q;
    N = N+1;
    string o;
    long sumtree[N]{};
    for (int i = 0; i<Q;i++){
        string operation;
        int index;
        cin >> operation>>index;
        index++;
        if (operation == "+"){
            long value;
            cin>>value;
            add(index, sumtree, value);
        }
        else{
            if (index == 0){o+="0\n";}
            else{
                o+=to_string(sum(index-1, sumtree));
                o+="\n";
            }
        }
    }
    cout << o;
    return 0;
}
