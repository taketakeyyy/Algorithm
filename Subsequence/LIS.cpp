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


/** 最長増加部分列(LIS)
 * @arg:
 *  vector<ll> A: 配列
 *
 * @note:
 *  計算量はO(NlogN)
 *  LISを求めるのにはdp1のみでよいが、dp2も構築しといたほうが便利なのでこうしている。
 *
 * @example
 *   vector<ll> A = {5, 1, 3, 2, 4};
 *
 *   // LIS作成
 *   LIS lis = LIS(A);
 *   cout << lis.answer << endl;
 *   // 3
 *
 *   // LISの経路を求めて表示
 *   auto route = lis.make_route();
 *   for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
 *   cout << endl;
 *   // 1 2 4
 *
 **/
class LIS {
    private:
        vector<ll> dp1u;// dp1u[i] := dp1[i]を最後に更新したインデックス番号
        vector<ll> prev; // prev[i] := LISを後ろから辿りたい。インデックス番号iの要素は、どのインデックス番号の要素へ辿ればいいか
    public:
        ll answer;  // LISの長さ
        vector<ll> dp1; // dp1[i] := 長さがi+1であるような、増加部分列における最終要素の最小値
        vector<ll> dp2; // dp2[i] := 最後がA[i]であるような、最長な増加部分列の長さ

        LIS(const vector<ll> &A) {
            ll N = (ll)A.size();
            dp1.assign(N, INF);
            dp1u.assign(N, -1);
            dp2.assign(N, 0);
            prev.assign(N, -1);

            for(ll i=0; i<N; i++) {
                ll idx = lower_bound(dp1.begin(), dp1.end(), A.at(i)) - dp1.begin();
                dp1[idx] = A.at(i);
                dp1u[idx] = i;
                if (idx-1 >= 0) {
                    prev[i] = dp1u[idx-1];
                }
                dp2[i] = idx+1;
            }

            answer = lower_bound(dp1.begin(), dp1.end(), INF) - dp1.begin();
        }

        /**
         * @brief LISの経路を求める
         *
         * @return vector<ll> 経路を表す頂点番号のリスト
         */
        vector<ll> make_route() {
            vector<ll> res;
            ll u = this->dp1u[this->answer-1];
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

    // LIS作成
    LIS lis = LIS(A);
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

    // LIS作成
    LIS lis = LIS(A);
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

    // LIS作成
    LIS lis = LIS(A);
    cout << "answer: " << lis.answer << endl;
    // answer: 3

    // LISの経路を求めて表示
    auto route = lis.make_route();
    cout << "route: ";
    for(ll i=0; i<(ll)route.size(); i++) cout << A[route[i]] << " ";
    cout << endl;
    // route: 2 3 5
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}