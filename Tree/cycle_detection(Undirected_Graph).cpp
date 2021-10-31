#include <bits/stdc++.h>
using namespace std;

/***無向グラフの閉路検出(DFS)
 * 閉路がある：trueを返す
 ***/
bool cycle_detection(long long now, long long parent, vector<vector<long long>> const &graph, set<long long> &visited) {
    if (visited.count(now)) return true;
    visited.insert(now);

    for(auto v: graph[now]) {
        if (v == parent) continue;
        if (cycle_detection(v, now, graph, visited)) return true;
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
    vector<vector<long long>> graph(N);
    for(auto [u, v]: edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 無向グラフの検出
    set<long long> visited;
    bool is_cycle = cycle_detection(0, -1, graph, visited);

    // 出力
    if (is_cycle) {
        cout << "Found Cycle!" << endl;
    }
    else {
        cout << "Not Found." << endl;
    }
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
    vector<vector<long long>> graph(N);
    for(auto [u, v]: edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 無向グラフの検出
    set<long long> visited;
    bool is_cycle = cycle_detection(0, -1, graph, visited);

    // 出力
    if (is_cycle) {
        cout << "Found Cycle!" << endl;
    }
    else {
        cout << "Not Found." << endl;
    }
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
    vector<vector<long long>> graph(N);
    for(auto [u, v]: edges) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 無向グラフの検出
    set<long long> visited;
    bool is_cycle = cycle_detection(0, -1, graph, visited);

    // 出力
    if (is_cycle) {
        cout << "Found Cycle!" << endl;
    }
    else {
        cout << "Not Found." << endl;
    }
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}