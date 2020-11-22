#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;


class WarshallFloyd {
    /***ワーシャルフロイド法
     * 計算量:
     *   O(V**3)
    ***/
    vector<vector<int>> dist;  // 隣接行列dist[i][j]:=iからjへ行くまでのコスト
    int v;  // 頂点数

    public:
        WarshallFloyd(int n) {
            /***
             * Args:
             *  n(int): 頂点数
             **/
            this->dist.resize(n);
            for (int i=0; i<n; i++) {
                this->dist[i].resize(n, INT_MAX);
            }
            for (int i=0; i<n; i++) {
                this->dist[i][i] = 0;
            }
            this->v = n;
        }

        int get_vertex_num() {
            // 頂点数を返す
            return this->v;
        }

        void update(int u, int v, int cost) {
            /*** 隣接行列のコストを更新する
             * Args:
             *   u(int): 頂点uから
             *   v(int): 頂点vへの
             *   cost(int): コストをcostに更新する
             **/
            this->dist[u][v] = cost;
        }

        vector<vector<int>> shortest_path() {
            /* 最短距離を計算する */
            for (int k=0; k<this->v; k++) {
                for (int i=0; i<this->v; i++) {
                    for (int j=0; j<this->v; j++) {
                        int ncost = this->dist[i][k]+this->dist[k][j]; if (dist[i][k]>0 && dist[k][j]>0 && ncost < 0) ncost = INT_MAX;  // オーバーフロー対策（オーバーフローしたらINT_MAXにする）
                        this->dist[i][j] = min(this->dist[i][j], ncost);
                    }
                }
            }
            return this->dist;
        }
};


void test1(){
    int V = 5;  // 頂点数
    WarshallFloyd wf = WarshallFloyd(V);

    // 辺のコストを更新する
    wf.update(0, 1, 80);
    wf.update(1, 2, 20);
    wf.update(0, 2, 60);
    wf.update(2, 3, 50);
    wf.update(3, 4, 60);
    wf.update(1, 4, 90);

    // 全対最短経路を求める
    vector<vector<int>> dist;
    dist = wf.shortest_path();

    // 各頂点の、頂点4への最短距離を出力する
    for (int i=0; i<wf.get_vertex_num(); i++) {
        cout << "dist[" << i << "][4]=" << dist[i][4] << endl;
    }
    // dist[0][4]=170
    // dist[1][4]=90
    // dist[2][4]=110
    // dist[3][4]=60
    // dist[4][4]=0
    cout << endl;

    // 頂点0から、各頂点までの最短距離を出力する
    for (int i=0; i<wf.get_vertex_num(); i++) {
        cout << "dist[0][" << i << "]=" << dist[0][i] << endl;
    }
    // dist[0][0]=0
    // dist[0][1]=80
    // dist[0][2]=60
    // dist[0][3]=110
    // dist[0][4]=170
    cout << endl;

    // 各頂点の、頂点1までの最短距離を出力する（INT_MAXは到達不可能）
    for (int i=0; i<wf.get_vertex_num(); i++) {
        cout << "dist[" << i << "][1]=" << dist[i][1] << endl;
    }
    // dist[0][1]=80
    // dist[1][1]=0
    // dist[2][1]=2147483647
    // dist[3][1]=2147483647
    // dist[4][1]=2147483647
}


int main(int argc, char const *argv[]){
    test1();
    return 0;
}