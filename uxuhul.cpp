//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <bitset>
using namespace std;

/*
    Solution is based on the fact that the votes are easily converted to binary numbers.
*/
bool diff_by_one(int n1,int n2){
    int differing_bits{0};
    for (int i = 0;i<3;i++){// Count the differing bits in the votes
        if (bitset<3>(n1).to_string()[i]!=bitset<3>(n2).to_string()[i]){
            differing_bits++;
        }
    }
    if (differing_bits == 1){
        return true; 
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    string o{""};
    int N, M;
    cin>>N;
    for (int i=0;i<N;i++){//For every voting round
        cin>>M;
        int pref[M][8];
        int optimal[M][8];
        for (int j=0;j<M;j++){// For every priest
            for (int k=0;k<8;k++){// For every possible vote in the priority list
                int in;
                cin>>in;
                pref[j][k]=in-1;
                
            }
        }
        for (int j=0;j<8;j++){ //Decices the optimal vote for the last priest for every possible voting state.
            int highest_priority{8};
            for (int k=0;k<8;k++){
                if (diff_by_one(j,k)){
                    if (pref[M-1][k]<highest_priority){
                        highest_priority = pref[M-1][k];
                        optimal[M-1][j]=k;
                    }
                }
            }
        }
        for (int j=M-2;j>=0;j--){//Starting from the second to last priest, decide the optimal choice based on how the next priest will vote
            for (int k=0;k<8;k++){
                int highest_priority{8};
                for (int l=0;l<8;l++){
                    if (diff_by_one(k,l)){
                        if (pref[j][optimal[j+1][l]]<highest_priority){
                            highest_priority = pref[j][optimal[j+1][l]];
                            optimal[j][k]=optimal[j+1][l];
                        }
                    }
                }
            }
        }
        //Output
        string vote_to_bits = bitset<3>(optimal[0][0]).to_string();
        for (int j=0;j<3;j++){
            if (vote_to_bits[j]=='0'){
                o+="N";
            }
            else{
                o+="Y";
            }
        }
        o+='\n';
    }
    cout << o;
    return 0;
}