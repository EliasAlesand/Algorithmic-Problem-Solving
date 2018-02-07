//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

// O(n log(n)) Solution using binary search


//Has a value and a pointer to the preceeding obj (number) in a sequence
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    
    int N;
    string o{""};
    while(cin>>N){
        int length = 0; //Keeps track of the longest currently found subsequence-1
        vector<int> input(N);
        vector<int> subseq(N); //subseq(k) keeps the indeces of the increasing subsequence of length k with the lowest ending point
        vector<int> parents(N,-1); //parents keeps track of the preceeding value of a certain input value to be able to be able to find the full sequence through backtrack
        for (int i = 0;i<N;i++){
            int val;
            cin>>val;
            input[i]=val;
            if (i == 0){
                subseq[length] = i;
            }
            else{
                //If we find a higher value than the highest value in the currently longest subsequence, we have found a longer sequence
                if (val > input[subseq[length]]){
                    length++;
                    subseq[length] = i;
                    parents[i] = subseq[length-1];
                    
                }
                //Else, update subsek(k) such that k is the index for the lowest value larger than val, thus keeeping the sequences values as low as possible to be able to find the longest increasing one
                //Done with a binary search. low will be the index in subseq for which the value should be updated
                else {
                    if (val<=input[subseq[0]]){
                        subseq[0]=i;
                    }
                    else{
                        int low = 1;
                        int high = length;
                        while (low <= high){
                            int mid = ceil((high+low)/2);
                            if (input[subseq[mid]] < val){
                                low = mid+1;
                            }
                            else{
                                high = mid-1;
                            }
                        }
                        subseq[low]=i;
                        parents[i]=subseq[low-1];
                    }
                }
            }
        }
        //Output
        vector<int> output(length+1);
        int n = subseq[length];
        for (int i = length;i>=0;i--){
            output[i] = n;
            n = parents[n];
        }
        cout << length+1<<endl;
        for (int i = 0;i<output.size();i++){
            cout << output[i]<<" ";
        }
        cout << endl;
        
    }
    return 0;
}

