#include <bits/stdc++.h>
using namespace std;


/** 強連結成分分解（SCC）
 * @brief
 * 有向グラフに対して「お互いに行き来できる頂点を同じグループにする」ことを強連結分解（SCC）という。
 *
 * サイクルをグループ分けするイメージ。
 * SCC構築の計算量：O(V+E)
 *
 * @tparam T int, long long
 *
 * @param N 頂点数
 * @param G グラフG。G[u] := 頂点uから伸びる有向辺の頂点リスト
 * @example
 * Usage
 *   long long N = 4;
 *   long long M = 7;  // 辺数（使ってない）
 *   vector<vector<long long>> G(N);
 *   G[0].push_back(1);
 *   G[1].push_back(0);
 *   G[1].push_back(2);
 *   G[3].push_back(2);
 *   G[3].push_back(0);
 *   G[0].push_back(3);
 *   G[1].push_back(2);
 *
 *   // SCC実行
 *   SCC scc = SCC<long long>(G);
 *
 *   // SCCを見る
 *   scc.print_groups();
 *   // group0 (size: 3): 0 1 3
 *   // group1 (size: 1): 2
 */
template<typename T>
class SCC {
    private:
        T N;  // 頂点数
        vector<vector<T>> G;  // G[u] := 頂点uに隣接している頂点vのリスト（uからvへの有向辺）
        vector<vector<T>> invG;  // Gの有向辺を反転させたグラフ
        vector<T> id2sccid;  // 強連結成分（SCC）用に記録する番号(頂点番号→SCCID)
        vector<T> sccid2id;  // SCCIDから頂点番号を割り出すテーブル（SCCID→頂点番号）

        /**
         * @brief
         * Gの有向辺を反転させたグラフinvGを確定させる。
         * O(頂点数+辺数)。
         */
        void fix_invG() {
            this->invG.assign(this->N, vector<T>());
            for(T u=0; u<this->N; u++) {
                for(auto v: this->G[u]) {
                    this->invG[v].push_back(u);
                }
            }
        }

        void dfs_step1(T u, T &sccid, vector<bool> &visited) {
            if (id2sccid[u]!=-1) return;
            if (visited[u]) return;
            visited[u] = true;

            for(auto v: this->G[u]) {
                dfs_step1(v, sccid, visited);
            }

            id2sccid[u] = sccid;
            sccid2id[sccid] = u;
            sccid++;
        }

        void dfs_step2(T u, vector<T> &group, vector<bool> &step2_done) {
            if (step2_done[id2sccid[u]]) return;
            group.push_back(u);
            step2_done[id2sccid[u]] = true;

            for(auto v: this->invG[u]) {
                dfs_step2(v, group, step2_done);
            }
        }


    public:
        vector<vector<T>> groups;  // 強連結成分のグループ
        vector<T> id2groupid; // 頂点番号→groupid

        /**
         * @brief SCCを作る。
         * 計算量O(頂点数+辺数)。
         * @return vector<vector<T>> 強連結成分のグループ
         */
        SCC(vector<vector<T>> _G): G(_G) {
            this->N = this->G.size();
            this->id2sccid.assign(N, -1);
            this->sccid2id.assign(N, -1);

            // [ステップ1]
            // DFSの帰りがけ順に番号を振る
            {
                T sccid = 0; // SCCでつける番号
                vector<bool> visited(this->N, false);
                for(int u=0; u<N; u++) {
                    this->dfs_step1(u, sccid, visited);
                }
            }

            // [ステップ2]
            // 辺の向きをすべて反転させ、番号の大きい順からDFSする
            // （実装のコツ）SCC用の番号i=N-1から順に、「反転させた有向辺が張っているならグループ化」をDFSでやっていく
            this->fix_invG();
            vector<bool> step2_done(this->N, false);  // ステップ2で終了したSCCIDを記録する
            for(int i=N-1; i>=0; i--) {
                if (step2_done[i]) continue;
                vector<T> group;
                dfs_step2(sccid2id[i], group, step2_done);
                groups.push_back(group);
            }

            // id2groupid作成
            id2groupid.assign(N, 0);
            for(T groupid=0; groupid<(T)groups.size(); groupid++) {
                for(T u: groups[groupid]) {
                    id2groupid[u] = groupid;
                }
            }
        }

        /**
         * @brief groupsの中身を見る。
         * @param groups
         * @param idx_plus 頂点番号に足す数。デフォルト0。
         */
        void print_groups(T idx_plus=0) {
            auto itr = groups.begin();
            for(size_t i=0; i<groups.size(); i++) {
                cout << "groupid" << i << " (size: " << (*itr).size() << "): ";
                for(auto u: *itr) {
                    cout << u+idx_plus << " ";
                }
                cout << endl;
                itr++;
            }
        }

        /**
         * @brief 強連結成分分解後のDAGの根を見つける
         * 根は複数ある場合がある
         * 計算量 O(頂点数+辺数)
         * @return vector<T> 根のgroupidのリスト
         */
        vector<T> find_roots() {
            // SCC後のDAGの根の判定は、グループ外からの有向辺が存在しないなら根
            vector<T> roots; // 根のgroupidを格納
            for(T groupid=0; groupid<(T)groups.size(); groupid++) {
                const auto &group = groups[groupid];
                bool is_root = true;
                for(T u: group) {
                    for(T v: this->invG[u]) {
                        if (id2groupid[u]!=id2groupid[v]) { is_root=false; break; }
                    }
                    if (!is_root) { break; }
                }
                if (is_root) { roots.push_back(groupid); }
            }
            return roots;
        }

        /**
         * @brief 強連結成分分解後のDAGの葉を見つける
         * 計算量 O(頂点数+辺数)
         * @return vector<T> 葉のgroupidリスト
         */
        vector<T> find_leaves() {
            // SCC後のDAGの葉の判定は、グループ外に有向辺が存在しないなら葉
            vector<T> leaves;  // 葉のgroupid番号を格納
            for(T groupid=0; groupid<(T)groups.size(); groupid++) {
                const auto &group = groups[groupid];
                bool is_leaf = true;
                for(T u: group) {
                    for(T v: this->G[u]) { // グループ外に有向辺があるなら、葉ではない
                        if (id2groupid[u]!=id2groupid[v]) { is_leaf = false; break; }
                    }
                    if (!is_leaf) { break; }
                }
                if (is_leaf) { leaves.push_back(groupid); }
            }
            return leaves;
        }

        /**
         * @brief SCC後のDAGを作る
         * 計算量 O(V+E)
         * @return vector<vector<T>>
         */
        vector<vector<T>> makeDAG() {
            T GN = groups.size();
            vector<set<T>> DAGset(GN); // 辺に重複がないようにsetで持つ
            for(T u=0; u<this->N; u++) {
                for(T v: this->G[u]) {
                    if (id2groupid[u] != id2groupid[v]) {
                        // 異なるグループへの辺を張る
                        DAGset[id2groupid[u]].insert(id2groupid[v]);
                    }
                }
            }

            // vectorに直す
            vector<vector<T>> DAG(GN);
            for(T groupid=0; groupid<GN; groupid++) {
                DAG[groupid] = vector<T>(DAGset[groupid].begin(), DAGset[groupid].end());
            }

            return DAG;
        }

        /**
         * @brief SCC後のDAGの辺を反転したグラフを返す
         * 計算量 O(V+E)
         * @return vector<vector<T>>
         */
        vector<vector<T>> makeInvDAG() {
            T GN = groups.size();
            vector<set<T>> invDAGset(GN); // 辺に重複がないようにsetで持つ
            for(T u=0; u<this->N; u++) {
                for(T v: this->invG[u]) {
                    if (id2groupid[u] != id2groupid[v]) {
                        // 異なるグループへの辺を張る
                        invDAGset[id2groupid[u]].insert(id2groupid[v]);
                    }
                }
            }

            // vectorに直す
            vector<vector<T>> invDAG(GN);
            for(T groupid=0; groupid<GN; groupid++) {
                invDAG[groupid] = vector<T>(invDAGset[groupid].begin(), invDAGset[groupid].end());
            }

            return invDAG;
        }

        /**
         * @brief 頂点uがどのSCCのグループに属しているかを返す
         *
         * @param u
         * @return T
         */
        T get_groupid(T u) {
            return id2groupid[u];
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
    vector<vector<long long>> G(N);
    G[0].push_back(1);
    G[1].push_back(0);
    G[1].push_back(2);
    G[3].push_back(2);
    G[3].push_back(0);
    G[0].push_back(3);
    G[1].push_back(2);

    // SCC実行
    SCC scc = SCC<long long>(G);

    // SCCを見る
    scc.print_groups();
    // group0 (size: 3): 0 1 3
    // group1 (size: 1): 2

    // DAGの根は？
    auto roots = scc.find_roots();
    cout << "roots(groupid): ";
    for(auto u : roots) cout << u << " ";
    cout << endl;
    // roots(groupid): 0

    // DAGの葉は？
    auto leaves = scc.find_leaves();
    cout << "leaves(groupid): ";
    for(auto u : leaves) cout << u << " ";
    cout << endl;
    // leaves(groupid): 1
}

void test2() {
    /***https://manabitimes.jp/math/1250 の図
     ***/
    cout << "===test2===" << endl;
    long long N = 7;
    vector<vector<long long>> G(N);
    G[0].push_back(1);
    G[1].push_back(2);
    G[2].push_back(0);
    G[2].push_back(3);
    G[3].push_back(4);
    G[4].push_back(3);
    G[4].push_back(5);
    G[4].push_back(6);

    // SCC実行
    SCC scc = SCC<long long>(G);

    // SCCを見る
    scc.print_groups();
    // group0 (size: 3): 0 2 1
    // group1 (size: 2): 3 4
    // group2 (size: 1): 6
    // group3 (size: 1): 5

    // DAGの根は？
    auto roots = scc.find_roots();
    cout << "roots(groupid): ";
    for(auto u : roots) cout << u << " ";
    cout << endl;
    // roots(groupid): 0

    // DAGの葉は？
    auto leaves = scc.find_leaves();
    cout << "leaves(groupid): ";
    for(auto u : leaves) cout << u << " ";
    cout << endl;
    // leaves(groupid): 2 3
}

void test3() {
    /*** https://github.com/E869120/kyopro_educational_90/blob/main/editorial/021.jpg の図
     ***/
    cout << "===test3===" << endl;

    long long N = 9;
    vector<vector<long long>> G(N);
    G[0].push_back(1);
    G[1].push_back(6);
    G[2].push_back(7);
    G[3].push_back(1);
    G[3].push_back(5);
    G[4].push_back(3);
    G[5].push_back(8);
    G[5].push_back(7);
    G[6].push_back(0);
    G[7].push_back(2);
    G[8].push_back(4);

    // SCC実行
    SCC scc = SCC<long long>(G);

    // SCCを見る
    scc.print_groups(1);
    // group0 (size: 4): 4 5 9 6
    // group1 (size: 2): 3 8
    // group2 (size: 3): 1 7 2

    // DAGの根は？
    auto roots = scc.find_roots();
    cout << "roots(groupid): ";
    for(auto u : roots) cout << u << " ";
    cout << endl;
    // roots(groupid): 0

    // DAGの葉は？
    auto leaves = scc.find_leaves();
    cout << "leaves(groupid): ";
    for(auto u : leaves) cout << u << " ";
    cout << endl;
    // leaves(groupid): 1 2
}


int main() {
    test1();
    test2();
    test3();
    return 0;
}