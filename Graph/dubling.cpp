#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

/**
 * @brief ダブリングの作成
 *
 * @param N T グラフの頂点数
 * @param D T ダブリングの個数。2^60あれば十分なら、D=60
 * @param A vector<T> A[i] := 頂点iの遷移先
 * @return vector<vector<T>>
 *
 * @example
 *  // ダブリングのグラフ構築
 *  ll D = 60;
 *  vector doubling = make_doubling<ll>(N, D, A);
 *
 *  // ダブリングを使ってK回の遷移先を求める
 *  ll now = 0;  // 開始の頂点番号
 *  for(ll k=D-1; k>=0; k--) {
 *      if ((K>>k)&1) {
 *          now = doubling[k][now];
 *      }
 *  }
 *  cout << now << endl;  // K回の遷移後の頂点番号
 */
template<typename T>
vector<vector<T>> make_doubling(T N, T D, vector<T> const &A) {
    // ダブリングのグラフ構築
    vector doubling(D, vector<ll>(N));  // doubling[k][i] := 頂点iから2^k辿った先の頂点は？
    for(ll i=0; i<N; i++) {
        doubling[0][i] = A[i];
    }
    for(ll k=1; k<D; k++) {
        for(ll i=0; i<N; i++) {
            doubling[k][i] = doubling[k-1][doubling[k-1][i]];  // 2^{k}辿った先は、「2^{k-1}辿った先」を2回辿ればよい
        }
    }
    return doubling;
}

void test1() {
    // https://atcoder.jp/contests/abc167/tasks/abc167_d
    ll N = 4;
    ll K = 5;  // K回辿った先を知りたい
    vector<ll> A(N);
    A[0] = 2;
    A[1] = 1;
    A[2] = 3;
    A[3] = 0;

    // ダブリングのグラフ構築
    ll D = 60;
    vector doubling = make_doubling<ll>(N, D, A);

    // ダブリングを使ってK回の遷移先を求める
    ll now = 0;  // 開始の頂点番号
    for(ll k=D-1; k>=0; k--) {
        if ((K>>k)&1) {
            now = doubling[k][now];
        }
    }
    cout << now << endl;  // K回の遷移後の頂点番号
    // 3
}


int main() {
    test1();
    return 0;
}
