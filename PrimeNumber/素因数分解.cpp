#include <bits/stdc++.h>
using namespace std;


/*
正整数nを素因数分解して、因数を要素としたsetを返す関数
*/
template <typename T>
set<T> prime_factor_ver_set(T n) {
    set<T> ans;
    if (n <= 1) return ans;

    for (T i=2; i*i<=n; i++) {
        while (n%i == 0) {
            ans.insert(i);
            n /= i;
        }
    }

    if (n != 1) ans.insert(n);

    return ans;
}

/*
正整数nを素因数分解して、因数をkey、指数部をvalueとしたmapを返す関数
*/
template <typename T>
map<T, T> prime_factor_ver_map(T n) {
    map<T, T> ans;
    if (n <= 1) return ans;

    for (T i=2; i*i<=n; i++) {
        while (n%i == 0) {
            if (!ans.count(i)) ans[i] = 0;
            ans.at(i)++;
            n /= i;
        }
    }

    if (n != 1) ans[n] = 1;

    return ans;
}


void test(){
    map<long long, long long> mp;

    /* 300を因数分解する */
    mp = prime_factor_ver_map<long long>(300);
    for (pair<long long, long long> p : mp) {
        long long key = p.first;
        long long value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // key:2 value:2
    // key:3 value:1
    // key:5 value:2
    cout << "===" << endl;


    /* 25を因数分解する */
    mp = prime_factor_ver_map<long long>(25);
    for (pair<long long, long long> p : mp) {
        long long key = p.first;
        long long value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // key:5 value:2
    cout << "===" << endl;


    /* 2を因数分解する */
    mp = prime_factor_ver_map<long long>(2);
    for (pair<long long, long long> p : mp) {
        long long key = p.first;
        long long value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // key:2 value:1
    cout << "===" << endl;


    /* 1を因数分解する */
    mp = prime_factor_ver_map<long long>(1);
    for (pair<long long, long long> p : mp) {
        long long key = p.first;
        long long value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // (出力なし)
    cout << "===" << endl;


    /* 0を因数分解する */
    mp = prime_factor_ver_map<long long>(0);
    for (pair<long long, long long> p : mp) {
        long long key = p.first;
        long long value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // (出力なし)
    cout << "===" << endl;


    /* -1を因数分解する */
    mp = prime_factor_ver_map<long long>(-1);
    for (pair<long long, long long> p : mp) {
        long long key = p.first;
        long long value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // (出力なし)
    cout << "===" << endl;

}


int main(int argc, char const *argv[]) {
    test();
    return 0;
}