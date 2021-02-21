#include <bits/stdc++.h>
using namespace std;

class Dijkstra {
    /*** ダイクストラ法
     * 重み付きグラフにおける単一始点最短路アルゴリズム
     *  * 使用条件
     *      - 負のコストがないこと
     *      - 有向グラフ、無向グラフともにOK
     *
     *  * 計算量はO(E*log(V))
     *
     *  * ベルマンフォード法より高速なので、負のコストがないならばこちらを使うとよい
     ***/
    private:
        using pll = pair<long long, long long>;
        vector<vector<pll>> graph;  // 隣接リストgraph[u][i]:=頂点uのi個目の隣接辺
        long long e;  // 辺の数
        long long v;  // 頂点の数
    public:
        Dijkstra(long long n) {
            graph.resize(n);
            this->v = n;
            this->e = 0;
        }

        long long get_vertex_num() {
            return this->v;
        }

        long long get_edge_num() {
            return this->e;
        }

        void add(long long u, long long v, long long cost) {
            /* 頂点uから頂点vへのコストはcost */
            this->graph[u].push_back(make_pair(v, cost));
            this->e++;
        }

        vector<long long> shortest_path(long long s) {
            /***
             * Args:
             *   s(long long): 始点s
             * Returns:
             *   dist(vector<long long>): dist[i] := 始点sから頂点iまでの最短コストを格納したリスト。
             *   到達不可の場合、値はLONG_LONG_MAX
             ***/
            /*** [初期化処理] ***/
            vector<long long> dist(this->v, LONG_LONG_MAX);
            dist[s] = 0;
            priority_queue<pll, vector<pll>, greater<pll>> que;  // 小さい順を維持する優先度付きキュー
            que.push(make_pair(0, s));  // 始点の(最短距離の候補, 頂点番号)を追加する（最短距離の候補が小さい順に取り出したいので、firstが最短距離の候補）

            /*** [探索処理] ***/
            while (!que.empty()) {
                /*** [pop処理] ***/
                long long u, d;
                tie(d, u) = que.top();
                que.pop();

                /*** [スキップ判定] ***/
                // キューに格納されている最短経路の候補がdistの距離よりも大きければ、他の経路で最短経路が存在するので、処理をスキップ
                if (dist[u] < d) continue;

                /*** [更新処理] ***/
                for (long long i=0; i<this->graph[u].size(); i++) {
                    long long v, cost;
                    tie(v, cost) = graph[u][i];
                    // 頂点uに隣接する各頂点に対して、頂点uを経由した場合の距離を計算し、今までの距離(dist)よりも小さければ更新する
                    long long ncost = dist[u]+cost; if (dist[u]>0 && cost>0 && ncost<0) ncost = LONG_LONG_MAX;  // オーバーフロー対策
                    if (dist[v] > ncost) {
                        dist[v] = ncost;  // 更新
                        que.push(make_pair(dist[v], v));
                    }
                }
            }
            return dist;
        }
};


void test1() {
    // ![](img/Dijkstra1.PNG)
    // 無向グラフ
    long long N = 8;  // 頂点数
    Dijkstra djk = Dijkstra(N);
    djk.add(0, 1, 1); djk.add(1, 0, 1);
    djk.add(0, 2, 7); djk.add(2, 0, 7);
    djk.add(0, 3, 2); djk.add(3, 0, 2);
    djk.add(1, 4, 2); djk.add(4, 1, 2);
    djk.add(1, 5, 4); djk.add(5, 1, 4);
    djk.add(2, 5, 2); djk.add(5, 2, 2);
    djk.add(2, 6, 3); djk.add(6, 2, 3);
    djk.add(3, 6, 5); djk.add(6, 3, 5);
    djk.add(4, 5, 1); djk.add(5, 4, 1);
    djk.add(5, 7, 6); djk.add(7, 5, 6);
    djk.add(6, 7, 2); djk.add(7, 6, 2);

    vector<long long> dist = djk.shortest_path(0);  // 始点0からの最短距離を求める

    // dist[i] 始点0から頂点iまでの最短距離
    for (long long i=0; i<dist.size(); i++) {
        cout << "dist[" << i << "]=" << dist[i] << endl;
    }
    // dist[0]=0
    // dist[1]=1
    // dist[2]=6
    // dist[3]=2
    // dist[4]=3
    // dist[5]=4
    // dist[6]=7
    // dist[7]=9
}

void test2() {
    // ![](img/bellmanford1.PNG)
    // 有向グラフ（負の閉路なし）
    long long V = 6;  // 頂点数
    Dijkstra djk = Dijkstra(V);
    djk.add(0, 1, 5);
    djk.add(0, 2, 4);
    djk.add(1, 2, -2);
    djk.add(1, 3, 1);
    djk.add(2, 3, 2);
    djk.add(2, 4, 1);
    djk.add(2, 5, 4);
    djk.add(3, 5, 3);
    djk.add(4, 5, 4);

    vector<long long> dist = djk.shortest_path(0);  // 始点0からの最短距離を求める

    // dist[i] 始点0から頂点iまでの最短距離
    for (long long i=0; i<dist.size(); i++) {
        cout << "dist[" << i << "]=" << dist[i] << endl;
    }
    // dist[0]=0
    // dist[1]=5
    // dist[2]=3
    // dist[3]=5
    // dist[4]=4
    // dist[5]=7
}

void test3() {
    // ![](img/bellmanford2.PNG)
    // 有向グラフ（負の閉路あり）
    long long V = 6;  // 頂点数
    Dijkstra djk = Dijkstra(V);
    djk.add(0, 1, 5);
    djk.add(0, 2, 4);
    djk.add(1, 2, -2);
    djk.add(1, 3, 1);
    djk.add(2, 3, 2);
    djk.add(2, 4, 1);
    djk.add(2, 5, 4);
    djk.add(3, 1, -1);
    djk.add(3, 5, 3);
    djk.add(4, 5, 4);

    /* 負の閉路があるので、最短距離の計算が収束せず、無限ループしてしまう */
    // vector<long long> dist = djk.shortest_path(0);  // 始点0からの最短距離を求める

    // // dist[i] 始点0から頂点iまでの最短距離
    // for (long long i=0; i<dist.size(); i++) {
    //     cout << "dist[" << i << "]=" << dist[i] << endl;
}

int main(int argc, char const *argv[]){
    cout << "[test1]" << endl;
    test1();
    cout << endl << "[test2]" << endl;
    test2();
    test3();
    return 0;
}