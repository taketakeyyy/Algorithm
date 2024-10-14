#include <bits/stdc++.h>
using namespace std;


/**
 * @brief ワ―シャルフロイド法
 * @example
 * // 頂点3のワ―シャルフロイド作成
 * WarshallFloyd wf(3);
 * // 辺を追加
 * wf.add_edge(0, 1, 5);
 * wf.add_edge(1, 2, 3);
 * // 最短経路を計算して隣接行列を作成
 * wf.build();
 * // 隣接行列作成後に、辺を更に追加
 * wf.add_edge_after_build(0, 2, 2);  // 0 -> 2 に新しいエッジ(コスト2)を追加
 */
class WarshallFloyd {
private:
public:
    vector<vector<long long>> dist;  // 隣接行列dist[i][j]:=iからjへ行くまでのコスト
    long long V;  // 頂点数
    static const long long INF;

    /***
     * Args:
     *  n(long long): 頂点数
     **/
    WarshallFloyd(long long n) {
        this->dist.resize(n);
        for (long long i=0; i<n; i++) {
            this->dist[i].resize(n, WarshallFloyd::INF);
        }
        for (long long i=0; i<n; i++) {
            this->dist[i][i] = 0;
        }
        this->V = n;
    }

    /**
     * @brief 辺を追加する
     *
     * @param u 頂点uから
     * @param v 頂点vへの
     * @param cost コストはcost
     */
    void add_edge(long long u, long long v, long long cost) {
        // 二重辺に注意
        this->dist[u][v] = min(this->dist[u][v], cost);
    }

    /**
     * @brief 最短距離を計算した隣接行列を作成する
     * 計算量O(V^3)
     *
     */
    void build() {
        for (long long k=0; k<this->V; k++) {
            for (long long i=0; i<this->V; i++) {
                for (long long j=0; j<this->V; j++) {
                    if (dist[i][k]==WarshallFloyd::INF) continue;
                    if (dist[k][j]==WarshallFloyd::INF) continue;
                    long long ncost = this->dist[i][k]+this->dist[k][j];
                    this->dist[i][j] = min(this->dist[i][j], ncost);
                }
            }
        }
    }

    /**
     * @brief ビルド後の隣接行列に新しく辺を追加し、隣接行列を再計算する
     * 計算量O(V^2)
     *
     * @param u 頂点uから
     * @param v 頂点vへの
     * @param new_cost 新しいコスト
     */
    void add_edge_after_build(long long u, long long v, long long new_cost) {
        long long N = dist.size();
        for (long long i=0; i<N; i++) {
            for (long long j=0; j<N; j++) {
                if (dist[i][u]!=WarshallFloyd::INF and dist[v][j]!=WarshallFloyd::INF) {
                    long long updated_dist = dist[i][u] + new_cost + dist[v][j];
                    if (updated_dist < dist[i][j]) {
                        dist[i][j] = updated_dist;
                    }
                }
            }
        }
    }
};
const long long WarshallFloyd::INF = LONG_LONG_MAX;


void test1(){
    cout << "===test1===" << endl;

    long long V = 5;  // 頂点数
    WarshallFloyd wf = WarshallFloyd(V);

    // 辺のコストを更新する
    wf.add_edge(0, 1, 80);
    wf.add_edge(1, 2, 20);
    wf.add_edge(0, 2, 60);
    wf.add_edge(2, 3, 50);
    wf.add_edge(3, 4, 60);
    wf.add_edge(1, 4, 90);

    // 全対最短経路を求める
    wf.build();

    // 各頂点の、頂点4への最短距離を出力する
    for (long long i=0; i<wf.V; i++) {
        cout << "dist[" << i << "][4]=" << wf.dist[i][4] << endl;
    }
    // dist[0][4]=170
    // dist[1][4]=90
    // dist[2][4]=110
    // dist[3][4]=60
    // dist[4][4]=0
    cout << endl;

    // 頂点0から、各頂点までの最短距離を出力する
    for (long long i=0; i<wf.V; i++) {
        cout << "dist[0][" << i << "]=" << wf.dist[0][i] << endl;
    }
    // dist[0][0]=0
    // dist[0][1]=80
    // dist[0][2]=60
    // dist[0][3]=110
    // dist[0][4]=170
    cout << endl;

    // 各頂点の、頂点1までの最短距離を出力する（LONG_LONG_MAXは到達不可能）
    for (long long i=0; i<wf.V; i++) {
        cout << "dist[" << i << "][1]=" << wf.dist[i][1] << endl;
    }
    // dist[0][1]=80
    // dist[1][1]=0
    // dist[2][1]=9223372036854775807
    // dist[3][1]=9223372036854775807
    // dist[4][1]=9223372036854775807
}

// これを使う問題：https://atcoder.jp/contests/abc375/tasks/abc375_f
void test_add_edge_after_build() {
    cout << "===test_add_edge_after_build===" << endl;

    WarshallFloyd wf(3);
    wf.add_edge(0, 1, 5);
    wf.add_edge(1, 2, 3);
    wf.build();
    assert(wf.dist[0][2] == 8);  // 0->2の最短距離は8

    wf.add_edge_after_build(0, 2, 2);  // 0 -> 2 に新しいエッジ(コスト2)を追加

    assert(wf.dist[0][2] == 2);  // 直接のエッジ0->2のコストが短いので、最短距離に更新
    assert(wf.dist[0][1] == 5);  // 0->1のコストはそのまま
    cout << "test_add_edge_after_build passed!" << endl;
}

int main(){
    test1();
    test_add_edge_after_build();
    return 0;
}