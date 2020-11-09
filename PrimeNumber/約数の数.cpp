#include <bits/stdc++.h>
using namespace std;


vector<long long> divisor(long long n) {
    /***
     * 正整数nの約数を列挙する
     *
     * Args
     *  n(long long): nの約数を列挙する
     *
     * Return
     *  vector<long long> 約数を格納したvector
     *
     * Note
     *  ソートされていないので注意
     ***/
    vector<long long> ans;
    for (long long i=1LL; i*i<=n; i++) {
        if (n%i==0) {
            ans.push_back(i);
            if (i!=n/i) ans.push_back(n/i);
        }
    }
    return ans;
}


int main(int argc, char const *argv[]){
    vector<long long> divs;

    divs = divisor(100);
    sort(divs.begin(), divs.end());
    for (int i=0; i<divs.size(); i++) {
        cout << divs[i] << endl;
    }
/*
1
2
4
5
10
20
25
50
100
*/
    return 0;
}