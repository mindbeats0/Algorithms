#include <bits/stdc++.h>
using namespace std;

string divisionToString(int A, int B){

    stringstream ss;
    ss<<A/B;
    if(A%B == 0)return ss.str();

    ss<<".";

    vector<int>decimals;
    int remainder = A%B;
    map<int,int>remainders;
    int index=0;
    while(remainders.find(remainder) == remainders.end()){

          // equivalent to the third one
        //remainders.emplace(remainder,index++);
        //remainders.insert(pair<int,int>(remainder,index++));

        remainders[remainder] = index++;
        decimals.push_back((remainder*10)/B);
        remainder = (remainder*10)%B;
    }

    int startPeriod = remainders[remainder];
    int endPeriod = index;


    for(int i=0;i<decimals.size();i++){
        if(i == startPeriod)ss<<"(";
        ss << decimals[i];
    }
    ss<<")";

    return ss.str();
}

int main(){

  int A = 3227;
  int B = 555;

 // cin>>A>>B;

  cout << divisionToString(A, B); // 5,8(144)

  return 0;
}
