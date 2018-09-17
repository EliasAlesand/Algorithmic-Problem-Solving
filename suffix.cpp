//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

/*
    For every suffix in each test case i loop through the characters in the suffix. Before encountering an '*' i compare the beggining of the currently found output to the suffix.
    After a '*' is found i check the end of the output and compare to the suffix.
*/

//Print the found output
void print_output(vector<char> o){
    for (int i=0;i<o.size();i++){
        cout << o[i];
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int T;
    cin>>T;
    bool possible = true;
    for(int k=0;k<T;k++){
        //Input
        int L,S;
        cin>>L>>S;
        vector<char> output(L,' ');
        possible = true;
        for (int i=0;i<S;i++){//For every suffix
            int start;
            string suffix;
            cin>>start>>suffix;
            start--;
            bool phfound = false;
            for(int j=0;j<suffix.size();j++){//For every character in the suffix
                if (!phfound){
                    if (suffix[j]=='*'){
                        phfound = true;
                        continue;
                    }
                    else if (output[start+j] == ' '){//Nothing currently in the corresponding output position
                        output[start+j] = suffix[j];
                    }
                    else if(output[start+j] != suffix[j]){//Output differs from suffix, therefore it is impossible
                        possible = false;
                        break;
                    }
                }
                else{//Placeholder found, check the ending of the output
                    if (output[L-(suffix.size()-j)] == ' '){
                        output[L-(suffix.size()-j)] = suffix[j];
                    }
                    else if (output[L-(suffix.size()-j)] != suffix[j]){
                        possible = false;
                        break;
                    }
                }
            }
            if (!possible){//Eat the rest of the input, does not matter since it has been concluded to be impossible
                for(int j=0;j<S-i-1;j++){
                    int dummy_i;
                    string dummy_s;
                    cin>>dummy_i>>dummy_s;
                }
                break;
            }
        }
        //Output
        for (int i=0;i<L;i++){
            if (output[i]==' '){//Nothing has been found for this position
                possible = false;
            }
        }
        if (!possible){
            cout << "IMPOSSIBLE"<<endl;
        }
        else{
            print_output(output);
            cout << endl;
        } 
    }
    return 0;
}