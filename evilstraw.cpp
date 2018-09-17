//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

/*
    First i determine if a palindrome is possible.
    Then i start with the first letter and then find the first letter that is the same starting from the end. Swap that letter to the end. Then go to the next letter and search starting from the end minus one and so on...
    The special case is if i find a letter with no other copy of that letter, then add the amount of swaps needed to get it to the middle. This only happens if the word has an uneven number of letters.
*/


//Check if it is possible to create a palindrome from a string s. If there are an even number of letters in s there can only be an even number of every letter that is in s. 
//Otherwise, if the number of letters in s are uneven, there have to be one letter that appears an uneven number of times.
bool possible(string s){
    vector<int> n_of_occurrences(26,0);
    for (int i=0; i<s.size();i++){
        n_of_occurrences[s[i]-97]++;
    }
    int n_of_uneven = 0;
    for (int i=0;i<n_of_occurrences.size();i++){
        if (n_of_occurrences[i]%2 != 0){
            n_of_uneven++;
        }
    }
    if (s.size()%2 == 0){
        if (n_of_uneven == 0){
            return true;
        }
        else return false;
    }
    else{
        if (n_of_uneven == 1){
            return true;
        }
        else return false;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    //Input
    int N;
    cin>>N;
    for (int i=0;i<N;i++){
        string s;
        cin>>s;
        if (!possible(s)){
            cout << "impossible"<<endl;
            continue;
        }
        int n_of_swaps=0;
        int uneven_letter = -1;
        for(int i=0;i<s.size()/2;i++){
            char front = s[i];
            int j=s.size()-1-i;
            int extra=0;
            if (uneven_letter != -1){//If a letter with uneven amount has been found, start searching one step further to the end.
                j++;
                extra=1;
            }
            int same_pos =-1;
            while (j>i){//Find the first letter that is the same as position i, starting from the end.
                if (s[j]==front){
                    same_pos = j;
                    break;
                }
                j--;
            }
            if (same_pos == -1){//Letter with uneven amount has been found, add the number of swaps to get it to the middle.
                uneven_letter = i;
                n_of_swaps += s.size()/2-uneven_letter;
                continue;
            } 
            for(int k=0;k<(s.size()-1-i+extra)-same_pos;k++){//Swap the found letter to the end.
                int tmp = s[same_pos+k];
                s[same_pos+k]=s[same_pos+k+1];
                s[same_pos+k+1]=tmp;
                n_of_swaps++;
            }  
        }
        //Output
        cout << n_of_swaps<<endl;
    }
    return 0;
}