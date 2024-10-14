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

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void test1() {
    cout << "===test1===" << endl;
    ordered_set<ll> ost;

    // 要素の挿入
    ost.insert(-3);
    ost.insert(0);
    ost.insert(1);
    ost.insert(1);
    ost.insert(3);
    for(ll v: ost) cout << v << " ";
    cout << endl;
    // -3 0 1 3

    // 要素の削除
    ost.erase(-3);
    ost.erase(ost.begin());
    for(ll v: ost) cout << v << " ";
    cout << endl;
    // 1 3
}

void test2() {
    cout << "===test2===" << endl;
    ordered_set<ll> ost;
    for(ll i=0; i<10; i++) ost.insert(i);

    // ost = {0,1,2,3,4,5,6,7,8,9}
    // find_by_order(k) := 小さい方からk番目の要素のイテレータを返す
    auto itr = ost.find_by_order(0);
    cout << *itr << endl;
    // 0

    itr = ost.find_by_order(9);
    cout << *itr << endl;
    // 9

    itr = ost.find_by_order(101);
    cout << *itr << endl;
    // 0(?)
}

void test3() {
    cout << "===test3===" << endl;
    ordered_set<ll> ost;
    for(ll i=0; i<10; i++) ost.insert(i);

    // ost = {0,1,2,3,4,5,6,7,8,9}
    // order_of_key(key) := keyは小さい方から何番目か(0-indexed)
    ll idx = ost.order_of_key(0);
    cout << idx << endl;
    // 0

    idx = ost.order_of_key(9);
    cout << idx << endl;
    // 9

    idx = ost.order_of_key(999);
    cout << idx << endl;
    // 10(?)
}


int main() {
    test1();
    test2();
    test3();
    return 0;
}
