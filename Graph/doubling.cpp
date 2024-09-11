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
 * @brief ダブリング
 *
 * @tparam T int, long long
 *
 * @example
 *   // ダブリング作成
 *   const ll D = 64;
 *   Doubling<ll> dbl(N, D, G);
 *
 *   // 頂点0からK回辿った先の頂点は？
 *   cout << dbl.query(0, K) << endl;
 */
template<typename T>
class Doubling {
private:

public:
    T mN, mD;
    vector<T> mG;
    vector<vector<T>> m_doubling; // m_doubling[u][d] := 頂点uから2^d辿った先の頂点

    /**
     * @brief コンストラクタ
     * 計算量O(ND)
     *
     * @param N 頂点数
     * @param D 2^Dまで辿る
     * @param G G[u] := 頂点uの遷移先。Functional Graphであること
     */
    Doubling(T N, T D, const vector<T> &G): mN(N), mD(D), mG(G), m_doubling(mN, vector<T>(mD, -1)) {
        // ダブリングのグラフ構築
        for(ll i=0; i<N; i++) {
            m_doubling[i][0] = mG[i];
        }
        for(ll d=1; d<D; d++) {
            for(ll i=0; i<N; i++) {
                m_doubling[i][d] = m_doubling[m_doubling[i][d-1]][d-1]; // 2^{d}辿った先は、「2^{d-1}辿った先」を2回辿ればよい
            }
        }
    }

    /**
     * @brief 「頂点uをk回辿る」クエリに応答する
     * 計算量O(D)
     *
     * @param u 頂点u
     * @param k 頂点uをk回辿る
     * @return T 頂点uをk回辿ったときの頂点
     */
    T query(T u, T k) {
        ll now = u;
        for(ll d=mD-1; d>=0; d--) {
            if ((k>>d)&1) now = m_doubling[now][d];
        }
        return now;
    }
};


void test1() {
    // https://atcoder.jp/contests/abc167/tasks/abc167_d
    ll N = 4;
    ll K = 5;  // K回辿った先を知りたい
    vector<ll> A(N);
    A[0] = 2;
    A[1] = 1;
    A[2] = 3;
    A[3] = 0;

    // ダブリング作成
    const ll D = 64;
    Doubling<ll> dbl(N, D, A);

    // 頂点0からK回辿った先の頂点は？
    cout << dbl.query(0, K) << endl;
    // 3
}


int main() {
    test1();
    return 0;
}
