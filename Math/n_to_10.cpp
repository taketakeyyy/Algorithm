#include <bits/stdc++.h>
using namespace std;
using ll = long long;

/*** n進数で表現された文字列を、10進数の値にして返すライブラリ
 *   ※ ただしSに使っていい文字は'0'~'9'までの文字
 ***/
template<typename T>
T n_to_10(const T n, const string& S) {
    // n進数で表現された文字列Sを、10進数の値にして返す
    T base = 1;
    T v = 0;  // 10進数の値
    for(int i=S.size()-1; i>=0; i--) {
        T a = S[i]-'0';
        v += a*base;
        base *= n;
    }
    return v;
}

template<typename T>
T n_to_10_snuke(const T n, const string& S) {
    // snukeさんがやってた方法
    T v = 0;
    for (char c: S) {
        v = v*n + (T)c-'0';
    }
    return v;
}

void test(){
    cout << "===test===" << endl;
    // 2進数表現の文字列を、10進数の値にする
    ll n = 2;
    string S = "101101101"s;
    cout << S << endl;
    ll ans = n_to_10<ll>(n, S);
    cout << ans << endl;
    // 365
}

void test2(){
    cout << "===test2===" << endl;
    // 8進数表現の文字列を、10進数の値にする
    ll n = 8;
    string S = "555"s;
    cout << S << endl;
    ll ans = n_to_10<ll>(n, S);
    cout << ans << endl;
    // 365
}

void test3(){
    cout << "===test3===" << endl;
    // 16進数表現の文字列を、10進数の値にする
    ll n = 16;
    string S = "123"s;
    cout << S << endl;
    ll ans = n_to_10<ll>(n, S);
    cout << ans << endl;
    // 291
}


void test_snuke(){
    cout << "===test_snuke===" << endl;
    // 2進数表現の文字列を、10進数の値にする
    ll n = 2;
    string S = "101101101"s;
    cout << S << endl;
    ll ans = n_to_10_snuke<ll>(n, S);
    cout << ans << endl;
    // 365
}

void test2_snuke(){
    cout << "===test2_snuke===" << endl;
    // 8進数表現の文字列を、10進数の値にする
    ll n = 8;
    string S = "555"s;
    cout << S << endl;
    ll ans = n_to_10_snuke<ll>(n, S);
    cout << ans << endl;
    // 365
}

void test3_snuke(){
    cout << "===test3_snuke===" << endl;
    // 16進数表現の文字列を、10進数の値にする
    ll n = 16;
    string S = "123"s;
    cout << S << endl;
    ll ans = n_to_10_snuke<ll>(n, S);
    cout << ans << endl;
    // 291
}


int main() {
    test();
    test2();
    test3();
    test_snuke();
    test2_snuke();
    test3_snuke();
    return 0;
}