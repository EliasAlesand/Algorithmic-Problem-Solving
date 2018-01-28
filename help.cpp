//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iterator>
#include <sstream>
#include <map>
using namespace std;

bool is_placeholder(string s){
    return s[0]=='<';
}
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    int N;
    cin >> N;
    string dummy;
    getline(cin,dummy);
    for (int i = 0; i<N;i++){
        //Collect first pattern
        string s1;
        getline(cin,s1);
        istringstream word1(s1);
        vector<string> p1((std::istream_iterator<string>(word1)), istream_iterator<string>());
        //Collect second pattern
        string s2;
        getline(cin,s2);
        istringstream word2(s2);
        vector<string> p2((std::istream_iterator<string>(word2)), istream_iterator<string>());

        if (p1.size() != p2.size()){
            cout <<"-"<<endl;
            continue;
        }
        if (p1.empty() || p2.empty()){
            cout <<"-"<<endl;
            continue;
        }
        map<string,string> dict1;
        map<string,string> dict2;

        bool possible = true;
        vector<string> phrase(p1.size());
        
        for (int j=0;j<phrase.size();j++){
            //No placeholders
            if (!is_placeholder(p1[j])&&!is_placeholder(p2[j])){
                if (p1[j]!=p2[j]){possible = false;break;}
                phrase[j]=p1[j];
            }
            //First word placeholder
            else if (is_placeholder(p1[j])&&!is_placeholder(p2[j])){
                if (dict1.count(p1[j])>0){
                    if (dict1.at(p1[j])!=p2[j]){
                        
                        possible = false;
                        break;
                    }
                }
                dict1.insert(make_pair(p1[j],p2[j]));
                phrase[j]=p2[j];
            }
            //Second word placeholder
            else if (!is_placeholder(p1[j])&&is_placeholder(p2[j])){
                if (dict2.count(p2[j])>0){
                    if (dict2.at(p2[j])!=p1[j]){
                        
                        possible = false;
                        break;
                    }
                }
                dict2.insert(make_pair(p2[j],p1[j]));
                phrase[j]=p1[j];
            }
        }
        for (int k = 0;k<p1.size();k++){
            for (int j=0;j<phrase.size();j++){
                //Both placeholders, one is assigned, the other is not.
                if (is_placeholder(p1[j])&&is_placeholder(p2[j])){
                    if (dict1.count(p1[j])>0){
                        if (dict2.count(p2[j])>0){
                            if (dict1.at(p1[j])!=dict2.at(p2[j])){
                                possible = false;
                                break;
                            }
                        }
                        phrase[j]=dict1.at(p1[j]);
                        dict2.insert(make_pair(p2[j],dict1.at(p1[j])));
                    }
                    else if (dict2.count(p2[j])>0){
                        if (dict1.count(p1[j])>0){
                            if (dict1.at(p1[j])!=dict2.at(p2[j])){
                                possible = false;
                                break;
                            }
                        }
                        phrase[j]=dict2.at(p2[j]);
                        dict1.insert(make_pair(p1[j],dict2.at(p2[j])));
                    }
                }
            }
        }
        for (int j=0;j<phrase.size();j++){
            //both placeholders
            if (is_placeholder(p1[j])&&is_placeholder(p2[j])){
                //both is assigned
                if (dict1.count(p1[j])>0 && dict2.count(p2[j])>0){
                    if (dict1.at(p1[j])!=dict2.at(p2[j])){
                            possible = false;
                            break;
                        }
                    phrase[j]=dict1.at(p1[j]);
                }
                //one is assigned
                else if (dict1.count(p1[j])>0){
                    phrase[j]=dict1.at(p1[j]);
                    dict2.insert(make_pair(p2[j],dict1.at(p1[j])));
                }
                else if (dict2.count(p2[j])>0){
                    phrase[j]=dict2.at(p2[j]);
                    dict1.insert(make_pair(p1[j],dict2.at(p2[j])));
                }
                //None is assigned
                else {
                    phrase[j]="a";
                    dict1.insert(make_pair(p1[j],"a"));
                    dict2.insert(make_pair(p2[j],"a"));
                }
            }
        }
        bool first = true;
        if (possible){
            for (string s : phrase){
                if (first){
                    cout << s;
                    first = false;
                }
                else cout<< " "<<s;
            }
        }
        else {cout << "-";}
        cout <<endl;

    }
    return 0;
}
