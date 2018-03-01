// you can use includes, for example:
// #include <algorithm>
#include <vector>
#include <algorithm>
#include <sstream>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(int N) {
    // write your code in C++14 (g++ 6.2.0)
    vector<int> digits{};
    string n_to_s = to_string(N);
    for_each(n_to_s.begin(), n_to_s.end(),[& digits](char & c){
        digits.push_back(c);
    });
    sort(n_to_s.begin(), n_to_s.end());
    
    string chars_to_s="";
    for_each(n_to_s.begin(), n_to_s.end(),[& chars_to_s](char & c){
        chars_to_s=c+chars_to_s;
    });
    int ret;
    istringstream(chars_to_s)>>ret;
    return ret;
}




#include <algorithm>
// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

    int n_of_consecutive(int i, vector<int> &A, int diff){
        int index = i-1;
        int n{};
        while ((A[index]-A[index-1]) == diff && index>0){
            n++;
            index--;
        }
        return n;
    }
    int solution(vector<int> &A){
        int n_of_slices{0};
        
        for (int i = 2; i < A.size();i++){
            if ((A[i]-A[i-1]) == (A[i-1]-A[i-2])){
                n_of_slices += n_of_consecutive(i,A, (A[i]-A[i-1]));
            }
        }
        return n_of_slices;
        
        // write your code in Java SE 8
    }
    