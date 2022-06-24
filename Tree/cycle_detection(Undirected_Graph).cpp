#include <bits/stdc++.h>
using namespace std;

/***無向グラフの閉路検出(DFS)
 *
 * Args:
 *  now: 現在の頂点
 *  parent: 前回の頂点
 *  G: グラフ
 *  visited: 訪問済みの頂点集合
 *
 * Returns:
 *  true（閉路がある） / false（閉路なし）
 *
 * Example:
 *  bool is_cycle = cycle_detection_in_undirected_graph<long long>(0, -1, G, visited);
 ***/
template<typename T>
bool cycle_detection_in_undirected_graph(T now, T parent, vector<set<T>> const &G, set<T> &visited) {
    if (visited.count(now)) return true;
    visited.insert(now);

    for(auto v: G[now]) {
        if (v == parent) continue;
        if (cycle_detection_in_undirected_graph(v, now, G, visited)) return true;
    }

    return false;
}

void test1() {
    cout << "===test1===" << endl;
    long long N = 8;  // 頂点数
    // 以下の無向辺が与えられる
    vector<pair<long long, long long>> edges = {
        make_pair(0, 1),
        make_pair(0, 2),
        make_pair(1, 3),
        make_pair(1, 4),
        make_pair(2, 5),
        make_pair(4, 6),
        make_pair(5, 6),
        make_pair(5, 7),
    };

    // グラフ構築
    vector<set<long long>> G(N);
    for(auto [u, v]: edges) {
        G[u].insert(v);
        G[v].insert(u);
    }

    // 無向グラフの閉路検出
    set<long long> visited;
    bool is_cycle = cycle_detection_in_undirected_graph<long long>(0, -1, G, visited);

    // 出力
    if (is_cycle) {
        cout << "Found Cycle!" << endl;
    }
    else {
        cout << "Not Found." << endl;
    }
    // Found Cycle!
}

void test2() {
    cout << "===test2===" << endl;
    long long N = 6;  // 頂点数
    // 以下の無向辺が与えられる
    vector<pair<long long, long long>> edges = {
        make_pair(0, 1),
        make_pair(1, 2),
        make_pair(3, 4),
        make_pair(4, 5),
        make_pair(1, 4),
    };

    // グラフ構築
    vector<set<long long>> G(N);
    for(auto [u, v]: edges) {
        G[u].insert(v);
        G[v].insert(u);
    }

    // 無向グラフの閉路検出
    set<long long> visited;
    bool is_cycle = cycle_detection_in_undirected_graph<long long>(0, -1, G, visited);

    // 出力
    if (is_cycle) {
        cout << "Found Cycle!" << endl;
    }
    else {
        cout << "Not Found." << endl;
    }
    // Not Found.
}

void test3() {
    cout << "===test3===" << endl;
    long long N = 5;  // 頂点数
    // 以下の無向辺が与えられる
    vector<pair<long long, long long>> edges = {
        make_pair(0, 1),
        make_pair(1, 2),
        make_pair(2, 3),
        make_pair(3, 4),
        make_pair(4, 0),
    };

    // グラフ構築
    vector<set<long long>> G(N);
    for(auto [u, v]: edges) {
        G[u].insert(v);
        G[v].insert(u);
    }

    // 無向グラフの閉路検出
    set<long long> visited;
    bool is_cycle = cycle_detection_in_undirected_graph<long long>(0, -1, G, visited);

    // 出力
    if (is_cycle) {
        cout << "Found Cycle!" << endl;
    }
    else {
        cout << "Not Found." << endl;
    }
    // Found Cycle!
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}