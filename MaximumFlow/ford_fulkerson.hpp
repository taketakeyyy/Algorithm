#ifndef FORD_FULKERSON_HPP
#define FORD_FULKERSON_HPP

#include <vector>
#include <limits>

namespace ford_fulkerson {
    /**
     * @brief 残余グラフ用の辺
     *
     * @tparam T
     */
    template<typename T>
    struct Edge {
        size_t to; // 順方向の辺（どこへ出流するか。頂点番号）
        size_t rev; // 逆方向の辺（どこから入流するか。インデックス番号）
        // G[u][i].toの逆方向の辺は、G[G[u][i].to][G[u][i].rev]
        T cap; // 順方向の空き容量（逆方向は使用済み容量で、-cap）

        Edge(): to(0), rev(0), cap(0) {} // デフォルトコンストラクタ
        Edge(size_t to, size_t rev, T cap): to(to), rev(rev), cap(cap) {}

        bool operator<(const Edge &other) {
            if (this->cap < other.cap) return true;
            if (this->cap == other.cap) {
                if (this->to < other.to) return true;
                if (this->to == other.to) {
                    if (this->rev < other.rev) return true;
                    return false;
                }
            }
            return false;
        }
        bool operator>(const Edge &other) {
            return other<(*this);
        }
        bool operator==(const Edge &other) {
            return (this->to==other.to and this->rev==other.rev and this->cap==other.cap);
        }
        bool operator<=(const Edge &other) {
            return !((*this) > other);
        }
        bool operator>=(const Edge &other) {
            return !((*this) < other);
        }
    };

    /**
     * @brief 最大フロー問題を、FordFulkerson法で解く
     *
     * @tparam T
     */
    template<typename T>
    class FordFulkerson {
    private:
        /**
         * @brief パス探索処理
         * 残余グラフを辿って、パスを見つける
         *
         * @param u 始点
         * @param goal 終点
         * @param F パス上の辺の空き容量の最小値
         * @param visited visited[u] := 頂点uはすでに訪れたか？
         * @return T
         */
        T dfs(T u, const T &goal, T F, std::vector<bool> &visited) {
            // 終了条件
            if (u == goal) return F;

            // 次の探索
            for(size_t i=0; i<G[u].size(); i++) {
                if (G[u][i].cap == 0) continue;
                if (visited[G[u][i].to]) continue;
                visited[G[u][i].to] = true;

                T flow = dfs(G[u][i].to, goal, min(F, G[u][i].cap), visited);

                // 残余グラフの容量をflow分増減させる
                if (flow >= 1) {
                    G[u][i].cap -= flow;
                    G[G[u][i].to][G[u][i].rev].cap += flow;
                    return flow;
                }
            }
            // パスは見つからなかった
            return 0;
        };

        /**
         * @brief 残余グラフを初期化
         *
         */
        void init_residual_graph() {
            G.assign(V, std::vector<Edge<T>>());

            for(size_t u=0; u<V; u++) {
                for(size_t i=0; i<O[u].size(); i++) {
                    const size_t &v = O[u][i].to;
                    const T &cap = O[u][i].cap;

                    size_t SU = G[u].size();
                    size_t SV = G[v].size();
                    G[u].push_back(Edge<T>(v, SV, cap));
                    G[v].push_back(Edge<T>(u, SU, (T)0));
                }
            }
        }

    public:
        static T INF;
        std::vector<std::vector<Edge<T>>> O; // 元のグラフ。O[u][i] := 頂点uから出てるi番目のパイプ
        std::vector<std::vector<Edge<T>>> G; // 残余グラフ。G[u][i] := 頂点uから出てるi番目のパイプ
        size_t V; // 頂点数

        // コンストラクタ
        FordFulkerson(size_t V): V(V) {
            O.assign(V, std::vector<Edge<T>>());
        }

        /**
         * @brief 元のグラフに、頂点uから頂点vへの最大容量capのパイプを追加
         *
         * @param u 頂点uから
         * @param v 頂点vへ
         * @param cap パイプの容量
         */
        void add_edge(size_t u, size_t v, T cap) {
            O[u].push_back(Edge<T>(v, -1, cap));
        }

        /**
         * @brief 始点から終点までの最大フローを求める
         * 計算量は、総流量をF、辺の数をEとすると、O(FE)
         * @param s 始点
         * @param t 終点
         * @return T
         */
        T max_flow(size_t s, size_t t) {
            // 残余グラフの初期化
            init_residual_graph();

            // 最大フローを求める
            T totalFlow = 0;
            while(1) {
                vector<bool> visited(this->V, false);
                visited[s] = true;
                T resFlow = dfs(s, t, FordFulkerson<T>::INF, visited);

                // フローを流せなくなったら終了
                if (resFlow == 0) break;
                totalFlow += resFlow;
            }
            return totalFlow;
        }
    };
    template <typename T>
    T FordFulkerson<T>::INF = std::numeric_limits<T>::max();
}


#endif // FORD_FULKERSON_HPP