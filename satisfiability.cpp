//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iostream>
#include <bitset>
/*
    For my solution i try every combination of negated and non-negated variable until i find a combination that satisfies the clauses.
    If no combination satisfies all clauses, print "unsatisfiable"
*/
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int T;
    cin>>T;
    for (int l=0;l<T;l++){
        //Input
        int N,M;
        cin>>N>>M;
        string dummy;
        getline(cin,dummy);//Eat newline
        vector<vector<int>> clauses(M);
        vector<vector<int>> sign(M);//Keeps track of negations
        for (int i=0;i<M;i++){
            string line;
            getline(cin,line);
            //Parse line into clause
            int c = 0;
            while (c<line.size()){
                if (line[c]=='~'){
                    sign[i].push_back(-1);
                    c++;
                }
                else{
                    sign[i].push_back(1);
                }
                c++;
                string val = {""};
                int w = c;
                while (line[w]!= ' '&&w<line.size()){
                    val += to_string(line[w]-48);
                    w++;
                    c++;
                }
                clauses[i].push_back(stoi(val));
                c+=3;
            }
        }
        //Try every possible combination of variable values by using a binary representation and counting up. 0 represents an inverted variable and 1 a non-inverted variable
        int gen = 0;
        bool possible = false;
        for (int i=0;i<pow(2,N);i++){//For every combination
            string bin = std::bitset<20>(gen).to_string();
            bool p = true;
            for (int j=0;j<M;j++){//For every clause
                bool clause_ok = false;
                for (int k=0;k<clauses[j].size();k++){//For every variable in the clause
                    if (sign[j][k] == 1 && bin[20-clauses[j][k]] == '1'){//Check if the variable in the clause and the corresponding variable in the current combination match
                        clause_ok = true;
                        break;
                    }
                    if (sign[j][k] == -1 && bin[20-clauses[j][k]] == '0'){
                        clause_ok = true;
                        break;
                    }
                }
                if (clause_ok == false){
                    p = false;
                    break;
                }
            }
            if (p==true){
                possible = true;
                break;
            }
            gen++;
        }
        //Output
        if (possible){
            cout << "satisfiable"<<endl;
        }
        else{
            cout << "unsatisfiable"<<endl;
        }
    }
    return 0;
}