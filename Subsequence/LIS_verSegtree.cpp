#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


#include <atcoder/segtree>
using S = pair<ll,ll>;
S op(S a, S b) { return max(a, b); }
S e() { return {-INF, -1}; } // (長さ,インデックス番号)
// max_rightの二分探索用
S target;
bool comp(S x) { return x < target; }

/** 最長増加部分列(LIS)のセグ木を使うバージョン
 **/
class LIS_verSegtree {
    private:
        vector<ll> prev; // prev[i] := LISを後ろから辿りたい。インデックス番号iの要素は、どのインデックス番号の要素へ辿ればいいか

    public:
        ll answer;  // LISの長さ、または価値
        vector<ll> dp1;  // dp1[i] := 長さがi+1であるような、増加部分列における最終要素の最小値
        atcoder::segtree<S, op, e> dp2; // dp2[i] := 最後がA[i]であるような、最長な増加部分列の長さ

        /**
         * @brief 最長増加部分列用コンストラクタ
         *
         * @param A 最長増加部分列を求めたい配列
         * @param MAX_VAL 配列Aの最大値
         *
         * @note: 計算量はO(NlogN)
         *  LISを求めるのにはdp2のみでよいが、dp1も構築しといたほうが便利なのでこうしている。
         *
         * @example
         *  vector<ll> A = {5, 1, 3, 2, 4};
         *  const ll MAX_VAL = 1e6; // Aの最大値
         *
         *  // LIS作成
         *  LIS_verSegtree lis(A, MAX_VAL);
         *  cout << lis.answer << endl;
         *  // 3
         *
         *  // LISの経路を求めて表示
         *  auto route = lis.make_route();
         *  for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
         *  cout << endl;
         *  // 1 2 4
         */
        LIS_verSegtree(const vector<ll> &A, const ll &MAX_VAL): dp2(vector<pair<ll,ll>>(MAX_VAL+1, {0,-1}/*(価値,インデックス番号)*/)) {
            ll N = (ll)A.size();
            dp1.assign(N, INF);
            prev.assign(N, -1);

            // LISを求める
            for(ll i=0; i<N; i++) {
                auto[mx, idx] = dp2.prod(0, A.at(i));
                dp2.set(A.at(i), {mx+1, i});
                prev[i] = idx;
                dp1[mx] = min(dp1[mx], A.at(i));
            }

            answer = dp2.all_prod().first;
        }

        /**
         * @brief 最大価値増加部分列用コンストラクタ
         * 最大価値増加部分列とは、増加部分列のうち、最も価値が大きいもの
         *
         * @param A 最大価値増加部分列を求めたい配列
         * @param MAX_VAL 配列Aの最大値
         * @param V A[i]の価値V[i]
         *          Vの値がすべて1のとき、最長増加部分列と同等になる
         * @note: 計算量はO(NlogN)
         *  dp2のみを求め、dp1は求めない。
         *
         * @example
         *  vector<ll> A = {3, 1, 4, 2};
         *  vector<ll> V = {10, 20, 30, 40};
         *  const ll MAX_VAL = 1e6;
         *
         *  // LIS作成
         *  LIS_verSegtree lis(A, MAX_VAL, V);
         *  cout << lis.answer << endl;
         *  // 60
         *
         *  // LISの経路を求めて表示
         *  auto route = lis.make_route();
         *  for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
         *  cout << endl;
         *  // route: 1 2
         */
        LIS_verSegtree(const vector<ll> &A, const ll &MAX_VAL, const vector<ll> &V): dp2(vector<pair<ll,ll>>(MAX_VAL+1, {0,-1}/*(価値,インデックス番号)*/)) {
            ll N = (ll)A.size();
            prev.assign(N, -1);

            // LISを求める
            for(ll i=0; i<N; i++) {
                auto[mx, idx] = dp2.prod(0, A.at(i));
                dp2.set(A.at(i), {mx+V.at(i), i});
                prev[i] = idx;
            }

            answer = dp2.all_prod().first;
        }

        /**
         * @brief LISの経路を求める
         *
         * @return vector<ll> 経路を表す頂点番号のリスト
         */
        vector<ll> make_route() {
            vector<ll> res;
            auto[_, u] = this->dp2.all_prod();
            res.push_back(u);
            while(this->prev[u] != -1) {
                u = this->prev[u];
                res.push_back(u);
            }
            reverse(res.begin(), res.end());

            return res;
        }
};


void test1() {
    // 5 1 3 2 4
    cout << "===test1===" << endl;
    vector<ll> A = {5, 1, 3, 2, 4};
    const ll MAX_VAL = 1e6;

    // LIS作成
    LIS_verSegtree lis(A, MAX_VAL);
    cout << "answer: " << lis.answer << endl;
    // answer: 3

    // LISの経路を求めて表示
    auto route = lis.make_route();
    cout << "route: ";
    for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
    cout << endl;
    // route: 1 2 4
}

void test2() {
    // 1 1 1
    cout << "===test2===" << endl;
    vector<ll> A = {1, 1, 1};
    const ll MAX_VAL = 1e6;

    // LIS作成
    LIS_verSegtree lis(A, MAX_VAL);
    cout << "answer: " << lis.answer << endl;
    // answer: 1

    // LISの経路を求めて表示
    auto route = lis.make_route();
    cout << "route: ";
    for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
    cout << endl;
    // route: 1
}

void test3() {
    // 4 2 3 1 5
    cout << "===test3===" << endl;
    vector<ll> A = {4, 2, 3, 1, 5};
    const ll MAX_VAL = 1e6;

    // LIS作成
    LIS_verSegtree lis(A, MAX_VAL);
    cout << "answer: " << lis.answer << endl;
    // answer: 3

    // LISの経路を求めて表示
    auto route = lis.make_route();
    cout << "route: ";
    for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
    cout << endl;
    // route: 2 3 5
}

void test4() {
    // [Q - Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) 入力例1
    // A: 3 1 4 2
    // V: 10 20 30 40
    cout << "===test4===" << endl;
    vector<ll> A = {3, 1, 4, 2};
    vector<ll> V = {10, 20, 30, 40};
    const ll MAX_VAL = 1e6;

    // LIS作成
    LIS_verSegtree lis(A, MAX_VAL, V);
    cout << "answer: " << lis.answer << endl;
    // answer: 60

    // LISの経路を求めて表示
    auto route = lis.make_route();
    cout << "route: ";
    for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
    cout << endl;
    // route: 1 2
}

void test5() {
    // [Q - Flowers](https://atcoder.jp/contests/dp/tasks/dp_q) 入力例4
    // A: 4 2 5 8 3 6 1 7 9
    // V: 6 8 8 4 6 3 5 7 5
    cout << "===test5===" << endl;
    vector<ll> A = {4, 2, 5, 8, 3, 6, 1, 7, 9};
    vector<ll> V = {6, 8, 8, 4, 6, 3, 5, 7, 5};
    const ll MAX_VAL = 1e6;

    // LIS作成
    LIS_verSegtree lis(A, MAX_VAL, V);
    cout << "answer: " << lis.answer << endl;
    // answer: 31

    // LISの経路を求めて表示
    auto route = lis.make_route();
    cout << "route: ";
    for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
    cout << endl;
    // route: 2 5 6 7 9
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}