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


class LIS {
    /** 最長増加部分列(LIS)
     * Args:
     *  vector<ll> A: 配列
     *
     * Notes:
     *  計算量はO(NlogN)
     *  LISを求めるのにはdp1のみでよいが、dp2も構築しといたほうが便利なのでこうしている。
     **/
    public:
        ll answer;  // LISの長さ
        vector<ll> dp1;  // dp1[i] := 長さがi+1であるような、増加部分列における最終要素の最小値
        vector<ll> dp2;  // dp2[i] := 最後がA[i]であるような、最長な増加部分列の長さ
        LIS(vector<ll>A) {
            ll N = (ll)A.size();
            dp1.assign(N, INF);
            dp2.assign(N, 0);

            for(ll i=0; i<N; i++) {
                auto it = lower_bound(dp1.begin(), dp1.end(), A[i]);
                *it = A[i];
                dp2[i] = it-dp1.begin() + 1;
            }

            answer = lower_bound(dp1.begin(), dp1.end(), INF) - dp1.begin();
        }
};


void test1() {
    // 5 1 3 2 4
    cout << "===test1===" << endl;
    vector<ll> A = {5, 1, 3, 2, 4};
    LIS lis = LIS(A);
    cout << lis.answer << endl;
}

void test2() {
    // 1 1 1
    cout << "===test2===" << endl;
    vector<ll> A = {1, 1, 1};
    LIS lis = LIS(A);
    cout << lis.answer << endl;
}

void test3() {
    // 4 2 3 1 5
    cout << "===test3===" << endl;
    vector<ll> A = {4, 2, 3, 1, 5};
    LIS lis = LIS(A);
    cout << lis.answer << endl;
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}