#include <bits/stdc++.h>
using namespace std;


/*
正整数nを素因数分解して、因数を要素としたsetを返す関数
*/
set<int64_t> prime_factor_ver_set(int64_t n) {
    set<int64_t> ans;
    if (n <= 1) return ans;

    for (int64_t i=2; i*i<=n; i++) {
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
map<int64_t, int64_t> prime_factor_ver_map(int64_t n) {
    map<int64_t, int64_t> ans;
    if (n <= 1) return ans;

    for (int64_t i=2; i*i<=n; i++) {
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
    map<int64_t, int64_t> mp;

    /* 300を因数分解する */
    mp = prime_factor_ver_map(300);
    for (pair<int64_t, int64_t> p : mp) {
        int64_t key = p.first;
        int64_t value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // key:2 value:2
    // key:3 value:1
    // key:5 value:2
    cout << "===" << endl;


    /* 25を因数分解する */
    mp = prime_factor_ver_map(25);
    for (pair<int64_t, int64_t> p : mp) {
        int64_t key = p.first;
        int64_t value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // key:5 value:2
    cout << "===" << endl;


    /* 2を因数分解する */
    mp = prime_factor_ver_map(2);
    for (pair<int64_t, int64_t> p : mp) {
        int64_t key = p.first;
        int64_t value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // key:2 value:1
    cout << "===" << endl;


    /* 1を因数分解する */
    mp = prime_factor_ver_map(1);
    for (pair<int64_t, int64_t> p : mp) {
        int64_t key = p.first;
        int64_t value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // (出力なし)
    cout << "===" << endl;


    /* 0を因数分解する */
    mp = prime_factor_ver_map(0);
    for (pair<int64_t, int64_t> p : mp) {
        int64_t key = p.first;
        int64_t value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // (出力なし)
    cout << "===" << endl;


    /* -1を因数分解する */
    mp = prime_factor_ver_map(-1);
    for (pair<int64_t, int64_t> p : mp) {
        int64_t key = p.first;
        int64_t value = p.second;
        cout << "key:" << key << " value:" << value << endl;
    }
    // (出力なし)
    cout << "===" << endl;

}


int main(int argc, char const *argv[]) {
    test();
    return 0;
}