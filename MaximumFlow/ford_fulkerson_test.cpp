#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;

#include "ford_fulkerson.hpp"

void test1() {
    cout << "===test1===" << endl;
    const ll N = 5;
    ford_fulkerson::FordFulkerson<ll> ff(N);

    // パイプを追加
    ff.add_edge(0, 1, 1);
    ff.add_edge(0, 2, 1);
    ff.add_edge(0, 3, 1);
    ff.add_edge(1, 2, 1);
    ff.add_edge(1, 4, 1);
    ff.add_edge(2, 3, 1);
    ff.add_edge(3, 4, 2);

    // 頂点0から頂点4までの最大フローを求める
    ll ans = ff.max_flow(0, 4);
    cout << ans << endl;
    // 3
    assert(ans == 3);

    // 辺を追加して、再度最大フローを求める
    ff.add_edge(0, 4, 7);
    ans = ff.max_flow(0, 4);
    cout << ans << endl;
    // 10
    assert(ans == 10);
}

/**
 * @brief 問題：https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_bp
 * 入力例1
 */
void test_tessoku_book_bp() {
    cout << "===test_tessoku_book_bp===" << endl;
    const ll N = 6;
    ford_fulkerson::FordFulkerson<ll> ff(N);

    // パイプを追加
    ff.add_edge(0, 1, 5);
    ff.add_edge(0, 3, 4);
    ff.add_edge(1, 2, 4);
    ff.add_edge(1, 4, 7);
    ff.add_edge(2, 5, 3);
    ff.add_edge(3, 4, 3);
    ff.add_edge(4, 5, 5);

    // 頂点0から頂点5までの最大フローを求める
    ll ans = ff.max_flow(0, 5);
    cout << ans << endl;
    // 8
    assert(ans == 8);
}

int main() {
    test1();
    test_tessoku_book_bp();
    return 0;
}