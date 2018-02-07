//Code written by Elias Alesand, elial148@student.liu.se

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <tuple>
using namespace std;
/*
    Solution works by sorting the intervals by values of their lower bound. Then iterating through and finding the largest covering subinterval of the 
    target interval that covers A. When the largest covering is found, increase the lower bound from A to the amount covered by the found subinterval, keep going
    until all subintervals have been checked.
*/
int main(){
    ios_base::sync_with_stdio(false);
    std::ios::sync_with_stdio(false);
    string o{""};
    double A,B;
    while (cin>>A){
        cin>>B;
        int N;
        cin>>N;
        vector<tuple<double,double,int>> intervals(N);
        for (int i=0;i<N;i++){//Stores A,B and the index for each subinterval
            cin>>get<0>(intervals[i]);
            cin>>get<1>(intervals[i]);
            get<2>(intervals[i])=i;
        }
        sort(intervals.begin(), intervals.end(),[](tuple<double,double,int> & a, tuple<double,double,int> & b){ //Sort the intervals by lower bound
            return get<0>(a)< get<0>(b);
        });
        
        double lower_bound = A;
        bool covered = false;
        int n_of_intervals = 0;
        string indices{""};
        /*
          Iterate through the intervals. Find all intervals with lower bound lower or equal to A. Add the one with the largest coverage to the result.
          Increase A(lower_bound) to a new point equal to the higher bound of the interval added, continue until interval covers B or end of list.
          If no interval exists with lower bound lower or equal to A, it is impossible to cover the target interval
        */
        for (int i=0;i<N;i++){
           
            double max_coverage = -1;
            int max_index = -1;
            int j{i};
            while(get<0>(intervals[j])<=lower_bound&&j<N){
                double coverage = get<1>(intervals[j])-lower_bound;
                if (coverage>max_coverage){ //Increase the maximum coverage if the current interval covers larger span of numbers
                    max_coverage=coverage;
                    max_index = j;
                    
                }
                j++;
            }
            n_of_intervals++;
            indices+=to_string(get<2>(intervals[max_index]))+" ";
            if (max_coverage == -1){//No intervals cover the lower bound
                break;
            }
            else if(get<1>(intervals[max_index])>= B){//Solution found
                covered = true;
                break;
            }
            lower_bound = get<1>(intervals[max_index]);
            i=j-1;
        }
        //Output
        if (covered){
            o += to_string(n_of_intervals)+'\n';
            o +=indices+'\n';
        }
        else {
            o+="impossible\n";
        }
    }
    cout << o;
    return 0;
}