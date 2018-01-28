
#include <iostream>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    long long M, N;
    cin>>M>>N;
    vector<long long> wanted_candy(N);
    for(int i=0;i<N;i++){
        cin>>wanted_candy[i];
    }
    sort(wanted_candy.begin(), wanted_candy.end());
    //Accumulate assumed int when third argument is a literal 0. Thus i need to create a larger data type to handle large computations.
    long long cast=0;
    long long diff = accumulate(begin(wanted_candy), end(wanted_candy), cast)-M;
    
    /*Since wanted_candy is sorted, the kids from which one can take away the least candy will be handled first.
    Ideally i would remove equal amount of candy for each child but this is not always possible since some kids
    want too few candy. Thus these are handled first and then i remove equal amount of candy from the rest(+1 or -1 depending on how many have to be removed)
    */
    long long anger = 0;
    for (int i=0; i<N;i++){
        long long anger_i;
        if (diff/(N-i)>wanted_candy[i]){
            anger_i = wanted_candy[i];
        }
        else{
            anger_i = diff/(N-i);
        }
        diff-=anger_i;
        anger+=anger_i*anger_i;
    }
    cout << anger;
    return 0;
}