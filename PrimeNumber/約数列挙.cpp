#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> divisor(T n) {
    /***
     * 正整数nの約数を列挙する
     *
     * Args
     *  n(int): nの約数を列挙する
     *
     * Return
     *  vector<int> 約数を格納したvector
     *
     * Note
     *  ソートされていないので注意
     ***/
    vector<T> ans;
    for (T i=1LL; i*i<=n; i++) {
        if (n%i==0) {
            ans.push_back(i);
            if (i!=n/i) ans.push_back(n/i);
        }
    }
    return ans;
}


void test1() {
    vector<long long> divs = divisor<long long>(100);
    sort(divs.begin(), divs.end());
    for (int i=0; i<divs.size(); i++) {
        cout << divs[i] << endl;
    }
    // 1
    // 2
    // 4
    // 5
    // 10
    // 20
    // 25
    // 50
    // 100
}
int main() {
    test1();

    return 0;
}