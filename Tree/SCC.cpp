#include <bits/stdc++.h>
using namespace std;


/** 強連結成分分解（SCC）
 * @brief
 * 有向グラフに対して「お互いに行き来できる頂点を同じグループにする」ことを強連結分解（SCC）という。
 *
 * サイクルをグループ分けするイメージ。
 *
 * @tparam T int, long long
 *
 * @param N 頂点数
 * @param G グラフG。G[i] := 頂点iに隣接している頂点集合
 * @example
 * Usage
 *   long long N = 4;
 *   long long M = 7;  // 辺数（使ってない）
 *   vector<set<long long>> graph(N);
 *   graph[0].insert(1);
 *   graph[1].insert(0);
 *   graph[1].insert(2);
 *   graph[3].insert(2);
 *   graph[3].insert(0);
 *   graph[0].insert(3);
 *   graph[1].insert(2);
 *
 *   // SCC実行
 *   SCC scc = SCC<long long>(N, graph);
 *   set<set<long long>> scc_groups = scc.scc_groups();
 *
 *   // SCCを見る
 *   scc.print_scc_groups(scc_groups);
 *   // group0 (size: 3): 0 1 3
 *   // group1 (size: 1): 2
 */
template<typename T>
class SCC {
    private:
        T N;  // 頂点数
        vector<set<T>> graph;  // graph[u] := 頂点uに隣接している頂点vの集合（uからvへの有向辺）
        vector<set<T>> rev_graph;  // graphの有向辺を反転させたグラフrev_graph
        vector<T> id2sccid;  // 強連結成分（SCC）用に記録する番号(頂点番号→SCCID)
        vector<T> sccid2id;  // SCCIDから頂点番号を割り出すテーブル（SCCID→頂点番号）

        /**
         * @brief
         * graphの有向辺を反転させたグラフrev_graphを確定させる。
         * O(頂点数+辺数)。
         */
        void fix_rev_graph() {
            this->rev_graph.assign(this->N, set<T>());
            for(T u=0; u<this->N; u++) {
                for(auto v: graph[u]) {
                    this->rev_graph[v].insert(u);
                }
            }
        }

        void dfs_step1(T u, T &sccid, set<T> &visited) {
            if (visited.count(u)) return;
            if (id2sccid[u]!=-1) return;
            visited.insert(u);

            for(auto v: this->graph[u]) {
                dfs_step1(v, sccid, visited);
            }

            id2sccid[u] = sccid;
            sccid2id[sccid] = u;
            sccid++;
        }

        void dfs_step2(T u, set<T> &visited, vector<bool> &step2_done) {
            if (visited.count(u)) return;
            if (step2_done[id2sccid[u]]) return;
            visited.insert(u);
            step2_done[id2sccid[u]] = true;

            for(auto v: this->rev_graph[u]) {
                dfs_step2(v, visited, step2_done);
            }
        }


    public:
        SCC(T N, vector<set<T>> graph) {
            this->N = N;
            this->graph = graph;
            this->id2sccid.assign(N, -1);
            this->sccid2id.assign(N, -1);
        }

        /**
         * @brief SCCを実行。
         * 計算量O(頂点数+辺数)。
         * @return set<set<T>> 強連結成分のグループ
         */
        set<set<T>> scc_groups() {
            // [ステップ1]
            // DFSの帰りがけ順に番号を振る
            T sccid = 0; // SCCでつける番号
            for(int u=0; u<N; u++) {
                set<T> visited;
                this->dfs_step1(u, sccid, visited);
            }

            // [ステップ2]
            // 辺の向きをすべて反転させ、番号の大きい順からDFSする
            // （実装のコツ）SCC用の番号i=N-1から順に、「反転させた有向辺が張っているならグループ化」をDFSでやっていく
            this->fix_rev_graph();
            vector<bool> step2_done(this->N, false);  // ステップ2で終了したSCCIDを記録する
            set<set<T>> scc_groups;  // 強連結成分のグループ
            for(int i=N-1; i>=0; i--) {
                if (step2_done[i]) continue;
                set<T> visited;
                dfs_step2(sccid2id[i], visited, step2_done);
                scc_groups.insert(visited);
            }

            return scc_groups;
        }

        /**
         * @brief scc_groupsの中身を見る。
         * @param scc_groups
         * @param idx_plus 頂点番号に足す数。デフォルト0。
         */
        void print_scc_groups(set<set<T>> &scc_groups, T idx_plus=0) {
            auto itr = scc_groups.begin();
            for(size_t i=0; i<scc_groups.size(); i++) {
                cout << "group" << i << " (size: " << (*itr).size() << "): ";
                for(auto u: *itr) {
                    cout << u+idx_plus << " ";
                }
                cout << endl;
                itr++;
            }
        }
};

void test1() {
    /*** 頂点数4 辺数7 の以下の有向辺(u, v)が与えられたときのSCCを求める
     * https://atcoder.jp/contests/typical90/tasks/typical90_u の入力例1
    0 1
    1 0
    1 2
    3 2
    3 0
    0 3
    1 2
    ***/
    cout << "===test1===" << endl;
    long long N = 4;
    long long M = 7;  // 辺数（使ってない）
    vector<set<long long>> graph(N);
    graph[0].insert(1);
    graph[1].insert(0);
    graph[1].insert(2);
    graph[3].insert(2);
    graph[3].insert(0);
    graph[0].insert(3);
    graph[1].insert(2);

    // SCC実行
    SCC scc = SCC<long long>(N, graph);
    set<set<long long>> scc_groups = scc.scc_groups();

    // SCCを見る
    scc.print_scc_groups(scc_groups);
    // group0 (size: 3): 0 1 3
    // group1 (size: 1): 2
}

void test2() {
    /***https://manabitimes.jp/math/1250 の図
     ***/
    cout << "===test2===" << endl;
    long long N = 7;
    vector<set<long long>> graph(N);
    graph[0].insert(1);
    graph[1].insert(2);
    graph[2].insert(0);
    graph[2].insert(3);
    graph[3].insert(4);
    graph[4].insert(3);
    graph[4].insert(5);
    graph[4].insert(6);

    // SCC実行
    SCC scc = SCC<long long>(N, graph);
    set<set<long long>> scc_groups = scc.scc_groups();

    // SCCを見る
    scc.print_scc_groups(scc_groups);
    // group0 (size: 3): 0 1 2
    // group1 (size: 2): 3 4
    // group2 (size: 1): 5
    // group3 (size: 1): 6
}

void test3() {
    /*** https://github.com/E869120/kyopro_educational_90/blob/main/editorial/021.jpg の図
     ***/
    cout << "===test3===" << endl;

    long long N = 9;
    vector<set<long long>> graph(N);
    graph[0].insert(1);
    graph[1].insert(6);
    graph[2].insert(7);
    graph[3].insert(1);
    graph[3].insert(5);
    graph[4].insert(3);
    graph[5].insert(8);
    graph[5].insert(7);
    graph[6].insert(0);
    graph[7].insert(2);
    graph[8].insert(4);

    // SCC実行
    SCC scc = SCC<long long>(N, graph);
    set<set<long long>> scc_groups = scc.scc_groups();

    // SCCを見る
    scc.print_scc_groups(scc_groups, 1);
    // group0 (size: 3): 1 2 7
    // group1 (size: 2): 3 8
    // group2 (size: 4): 4 5 6 9
}


int main() {
    test1();
    test2();
    test3();
    return 0;
}