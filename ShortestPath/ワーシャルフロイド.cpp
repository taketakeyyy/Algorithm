#include <bits/stdc++.h>
using namespace std;


class WarshallFloyd {
    /***ワーシャルフロイド法
     * 計算量:
     *   O(V**3)
    ***/
    vector<vector<long long>> dist;  // 隣接行列dist[i][j]:=iからjへ行くまでのコスト
    long long v;  // 頂点数

    public:
        WarshallFloyd(long long n) {
            /***
             * Args:
             *  n(long long): 頂点数
             **/
            this->dist.resize(n);
            for (long long i=0; i<n; i++) {
                this->dist[i].resize(n, LONG_LONG_MAX);
            }
            for (long long i=0; i<n; i++) {
                this->dist[i][i] = 0;
            }
            this->v = n;
        }

        long long get_vertex_num() {
            // 頂点数を返す
            return this->v;
        }

        void update(long long u, long long v, long long cost) {
            /*** 隣接行列のコストを更新する
             * Args:
             *   u(long long): 頂点uから
             *   v(long long): 頂点vへの
             *   cost(long long): コストをcostに更新する
             **/
            // 二重辺に注意
            if (this->dist[u][v] == 0) this->dist[u][v] = cost;
            else this->dist[u][v] = min(this->dist[u][v], cost);
        }

        vector<vector<long long>> shortest_path() {
            /* 最短距離を計算する */
            for (long long k=0; k<this->v; k++) {
                for (long long i=0; i<this->v; i++) {
                    for (long long j=0; j<this->v; j++) {
                        long long ncost = this->dist[i][k]+this->dist[k][j]; if (dist[i][k]>0 && dist[k][j]>0 && ncost < 0) ncost = LONG_LONG_MAX;  // オーバーフロー対策（オーバーフローしたらLONG_LONG_MAXにする）
                        this->dist[i][j] = min(this->dist[i][j], ncost);
                    }
                }
            }
            return this->dist;
        }
};


void test1(){
    long long V = 5;  // 頂点数
    WarshallFloyd wf = WarshallFloyd(V);

    // 辺のコストを更新する
    wf.update(0, 1, 80);
    wf.update(1, 2, 20);
    wf.update(0, 2, 60);
    wf.update(2, 3, 50);
    wf.update(3, 4, 60);
    wf.update(1, 4, 90);

    // 全対最短経路を求める
    vector<vector<long long>> dist;
    dist = wf.shortest_path();

    // 各頂点の、頂点4への最短距離を出力する
    for (long long i=0; i<wf.get_vertex_num(); i++) {
        cout << "dist[" << i << "][4]=" << dist[i][4] << endl;
    }
    // dist[0][4]=170
    // dist[1][4]=90
    // dist[2][4]=110
    // dist[3][4]=60
    // dist[4][4]=0
    cout << endl;

    // 頂点0から、各頂点までの最短距離を出力する
    for (long long i=0; i<wf.get_vertex_num(); i++) {
        cout << "dist[0][" << i << "]=" << dist[0][i] << endl;
    }
    // dist[0][0]=0
    // dist[0][1]=80
    // dist[0][2]=60
    // dist[0][3]=110
    // dist[0][4]=170
    cout << endl;

    // 各頂点の、頂点1までの最短距離を出力する（LONG_LONG_MAXは到達不可能）
    for (long long i=0; i<wf.get_vertex_num(); i++) {
        cout << "dist[" << i << "][1]=" << dist[i][1] << endl;
    }
    // dist[0][1]=80
    // dist[1][1]=0
    // dist[2][1]=9223372036854775807
    // dist[3][1]=9223372036854775807
    // dist[4][1]=9223372036854775807
}


int main(int argc, char const *argv[]){
    test1();
    return 0;
}