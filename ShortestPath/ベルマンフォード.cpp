#include <bits/stdc++.h>
using namespace std;


class BellmanFord {
    private:
        using pll = pair<long long, long long>;
        vector<vector<pll>> graph;
        long long e;  // 辺の数
        long long v;  // 頂点数
    public:
        BellmanFord(long long n) {
            /***
             * Args:
             *  s(long long): 始点
             *  n(long long): 頂点数
             *
             **/
            this->graph.resize(n);
            this->e = 0;
            this->v = n;
        }

        long long get_edge_num() {
            /* 無向グラフのときは、辺の数は2倍になって返ってくる */
            return this->e;
        }

        long long get_vertex_num() {
            return this->v;
        }

        void add(long long u, long long v, long long cost) {
            /* 頂点uから頂点vへのコストはcost */
            this->graph[u].push_back(make_pair(v, cost));
            this->e++;
        }

        pair<bool, vector<long long>> shortest_path(long long s) {
            /*** 始点sからの最短経路を求める
             * Args:
             *   s(long long): 始点の頂点番号
             * Returns:
             *   nloop, dist:
             *       nloop(bool): 負の閉路が存在する(true) / 存在しない(false)
             *       dist(vector<long long>): 始点sから、各頂点までの最短距離を格納した配列
             ***/
            // [初期化処理]
            vector<long long> dist(this->v, LONG_LONG_MAX);
            dist[s] = 0;

            for (long long t=0; t<this->v; t++) {
                bool update = false;
                for (long long u=0; u<this->v; u++) {
                    if (dist[u] == LONG_LONG_MAX) continue;
                    for (pll v_cost : graph[u]) {
                        long long v, cost;
                        tie(v, cost) = v_cost;
                        long long ncost = dist[u]+cost; if (dist[u]>0 && cost>0 && ncost<0) ncost = LONG_LONG_MAX;  // オーバーフロー対策
                        if (dist[v] > ncost) {
                            dist[v] = ncost;
                            update = true;
                            if (t == this->v-1) {
                                return make_pair(true, dist);
                            }
                        }
                    }
                }
                if (!update) break;
            }
            return make_pair(false, dist);
        }
};

void test1(){
    // ![](img/bellmanford1.PNG)
    // 例1：負の閉路が存在しない場合
    long long V = 6;  // 頂点数
    BellmanFord bf = BellmanFord(V);
    bf.add(0, 1, 5);
    bf.add(0, 2, 4);
    bf.add(1, 2, -2);
    bf.add(1, 3, 1);
    bf.add(2, 3, 2);
    bf.add(2, 4, 1);
    bf.add(2, 5, 4);
    bf.add(3, 5, 3);
    bf.add(4, 5, 4);
    bool nloop; vector<long long> dist;
    tie(nloop, dist) = bf.shortest_path(0);  // 始点0からの最短距離を求める

    // 負の閉路は存在するか？
    cout << "nloop: " << (nloop?"true":"false") << endl;
    // nloop: false

    // 始点0から頂点iまでの最短距離dist[i]
    for (long long i=0; i<bf.get_vertex_num(); i++) {
        cout << "dist[" << i << "]=" << dist[i] << endl;
    }
    // dist[0]=0
    // dist[1]=5
    // dist[2]=3
    // dist[3]=5
    // dist[4]=4
    // dist[5]=7
}

void test2() {
    // ![](img/bellmanford2.PNG)
    // 例2：負の閉路が存在して、頂点5までの最短コストは求まらない場合
    long long V = 6;
    BellmanFord bf = BellmanFord(V);
    bf.add(0, 1, 5);
    bf.add(0, 2, 4);
    bf.add(1, 2, -2);
    bf.add(1, 3, 1);
    bf.add(2, 3, 2);
    bf.add(2, 4, 1);
    bf.add(2, 5, 4);
    bf.add(3, 1, -1);
    bf.add(3, 5, 3);
    bf.add(4, 5, 4);
    bool nloop; vector<long long> dist;
    tie(nloop, dist) = bf.shortest_path(0);

    // 負の閉路は存在するか？
    cout << "nloop: " << (nloop?"true":"false") << endl;
    // true

    // 始点0から頂点5までのコスト
    cout << "dist[5]=" <<  dist[5] << endl;
    // dist[5]=3（負の閉路が存在して正確な最短コストは求まらない）
}

void test3() {
    // ![](img/bellmanford3.PNG)
    // 例3：負の閉路が存在するが、頂点5までの最短コストは求まる場合
    long long V = 9;
    BellmanFord bf = BellmanFord(V);
    bf.add(0, 1, 5);
    bf.add(0, 2, 4);
    bf.add(1, 2, -2);
    bf.add(1, 3, 1);
    bf.add(2, 3, 2);
    bf.add(2, 4, 1);
    bf.add(2, 5, 4);
    bf.add(3, 5, 3);
    bf.add(3, 6, -1);
    bf.add(4, 5, 4);
    bf.add(6, 7, -1);
    bf.add(7, 8, -1);
    bf.add(8, 6, -1);
    bool nloop; vector<long long> dist;
    tie(nloop, dist) = bf.shortest_path(0);

    // 負の閉路は存在するか？
    cout << "nloop: " << (nloop?"true":"false") << endl;
    // true

    // 始点0から頂点5までのコスト
    cout << "dist[5]=" <<  dist[5] << endl;  // 負の閉路が存在するのですべての頂点について最短経路は求まらないが、頂点5の最短距離は求まる
    // dist[5]=7
}

int main(int argc, char const *argv[]){
    cout << "[test1]" << endl;
    test1();
    cout << endl << "[test2]" << endl;
    test2();
    cout << endl << "[test3]" << endl;
    test3();
    return 0;
}