#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


class BellmanFord {
    private:
        using pii = pair<int, int>;
        vector<vector<pii>> graph;
        int e;  // 辺の数
        int v;  // 頂点数
    public:
        BellmanFord(int n) {
            /***
             * Args:
             *  s(int): 始点
             *  n(int): 頂点数
             *
             **/
            this->graph.resize(n);
            this->e = 0;
            this->v = n;
        }

        int get_edge_num() {
            /* 無向グラフのときは、辺の数は2倍になって返ってくる */
            return this->e;
        }

        int get_vertex_num() {
            return this->v;
        }

        void add(int u, int v, int cost) {
            /* 頂点uから頂点vへのコストはcost */
            this->graph[u].push_back(make_pair(v, cost));
            this->e++;
        }

        pair<bool, vector<int>> shortest_path(int s) {
            /*** 始点sからの最短経路を求める
             * Args:
             *   s(int): 始点の頂点番号
             * Returns:
             *   nloop, dist:
             *       nloop(bool): 負の閉路が存在する(true) / 存在しない(false)
             *       dist(vector<int>): 始点sから、各頂点までの最短距離を格納した配列
             ***/
            // [初期化処理]
            vector<int> dist(this->v, INT_MAX);
            dist[s] = 0;

            for (int t=0; t<this->v; t++) {
                bool update = false;
                for (int u=0; u<this->v; u++) {
                    if (dist[u] == INT_MAX) continue;
                    for (pii v_cost : graph[u]) {
                        int v, cost;
                        tie(v, cost) = v_cost;
                        if (dist[v] > dist[u]+cost) {
                            dist[v] = dist[u]+cost;
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
    int V = 6;  // 頂点数
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
    bool nloop; vector<int> dist;
    tie(nloop, dist) = bf.shortest_path(0);  // 始点0からの最短距離を求める

    // 負の閉路は存在するか？
    cout << "nloop: " << (nloop?"true":"false") << endl;
    // nloop: false

    // 始点0から頂点iまでの最短距離dist[i]
    for (int i=0; i<bf.get_vertex_num(); i++) {
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
    int V = 6;
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
    bool nloop; vector<int> dist;
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
    int V = 9;
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
    bool nloop; vector<int> dist;
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