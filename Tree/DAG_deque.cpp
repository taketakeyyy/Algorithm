#include <bits/stdc++.h>
using namespace std;

/**トポロジカルソート（DAG）
 * 閉路のない有向グラフ
 * 「どの頂点iについても、行き先の頂点番号が、頂点iよりも大きくなる」という性質を持つ
 *
 * Args:
 *  N(T): 頂点数（整数）
 **/
template<typename T>
class DAG {
    private:
        vector<T> in_degrees;  // in_degrees[i] := ノードiの入次数
        vector<vector<T>> G;  // G[i] := ノードiに隣接しているノードの集合（配列）

    public:
        T V;  // 頂点数
        T E = 0;  // 辺の数
        vector<T> dag;  // トポロジカル順序で並んだ要素の配列

        DAG(T N) {
            this->V = N;
            this->in_degrees.assign(N, 0);
            this->G.resize(N);
        }

        /*** 頂点uから頂点vへの辺を追加する
         ***/
        void add_edge(T u, T v) {
            this->G[u].emplace_back(v);
            this->in_degrees[v]++;
            this->E++;
        }

        /*** DAGを構築する
         * Notes:
         *  キューにdequeを使っている
         *  * 計算量
         *    - dequeを使うと、O(|E|+|V|)
         ***/
        void build() {
            deque<T> que;

            // まず、入次数0の頂点をキューに追加する
            for(T i=0; i<this->V; i++) {
                if (in_degrees[i]==0) que.push_back(i);
            }

            // 「キューに入っている頂点を削除する」処理を繰り返す
            while(!que.empty()) {
                T u = que.front(); que.pop_front();

                // 頂点uを削除するので、頂点uに隣接している頂点の入次数を減らす
                for(auto v: G[u]) {
                    this->in_degrees[v]--;
                    if (this->in_degrees[v] == 0) que.push_back(v);  // 入次数が0になった頂点は、キューに追加する
                }

                this->dag.emplace_back(u);
            }
        }

        /*** DAGの構築に成功したか？
         * 閉路があると、失敗する
         ***/
        bool is_build_success() {
            return (T)this->dag.size()==this->V;
        }
};

void test0(){
    cout << "===test0===" << endl;
    // D - Restricted Permutationの入力例1を試す
    // https://atcoder.jp/contests/abc223/tasks/abc223_d
    long long N = 4;

    // DAGの宣言
    DAG dag = DAG<long long>(N);

    // 辺を追加する
    // 1 → 0
    //   ↘
    // 2 → 3
    dag.add_edge(1, 0);
    dag.add_edge(2, 3);
    dag.add_edge(1, 3);

    // DAGの構築
    dag.build();

    // DAGの構築成功判定
    if (dag.is_build_success()) {
        cout << "Success" << endl;

        // DAGの出力（頂点をトポロジカル順序で出力）
        for(long long i=0; i<N; i++) {
            cout << dag.dag[i] << endl;
        }
    } else {
        cout << "Failed" << endl;
    }
    // Success
    // 1
    // 2
    // 0
    // 3
}

void test1(){
    cout << "===test1===" << endl;
    // AOJの入力例を試す
    // https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B&lang=ja
    long long N = 6;

    // DAGの宣言
    DAG dag = DAG<long long>(N);

    // 辺を追加する
    // 0 → 1 → 2
    //   ↗     ↑
    // 3 → 4 → 5
    dag.add_edge(0, 1);
    dag.add_edge(1, 2);
    dag.add_edge(3, 1);
    dag.add_edge(3, 4);
    dag.add_edge(4, 5);
    dag.add_edge(5, 2);

    // DAGの構築
    dag.build();

    // DAGの構築成功判定
    if (dag.is_build_success()) {
        cout << "Success" << endl;

        // DAGの出力（頂点をトポロジカル順序で出力）
        for(long long i=0; i<N; i++) {
            cout << dag.dag[i] << endl;
        }
    } else {
        cout << "Failed" << endl;
    }
    // Success
    // 0
    // 3
    // 1
    // 4
    // 5
    // 2
}

void test2() {
    cout << "===test2===" << endl;
    long long N = 6;

    // DAGの宣言
    DAG dag = DAG<long long>(N);

    // 辺を追加する
    // 0 → 1 → 2
    //     ↑
    // 3 → 4 → 5
    dag.add_edge(0, 1);
    dag.add_edge(1, 2);
    dag.add_edge(3, 4);
    dag.add_edge(4, 5);
    dag.add_edge(4, 1);

    // DAGの構築
    dag.build();

    // DAGの構築成功判定
    if (dag.is_build_success()) {
        cout << "Success" << endl;

        // DAGの出力（頂点をトポロジカル順序で出力）
        for(long long i=0; i<N; i++) {
            cout << dag.dag[i] << endl;
        }
    } else {
        cout << "Failed" << endl;
    }
    // Success
    // 0
    // 3
    // 4
    // 5
    // 1
    // 2
}

void test3() {
    cout << "===test3===" << endl;
    // DAGの構築失敗例: 有向グラフに閉路がある
    long long N = 4;

    // DAGの宣言
    DAG dag = DAG<long long>(N);

    // 辺を追加する
    // 0 → 1 → 2 → 3
    //   ↖ ←----← ↙
    dag.add_edge(0, 1);
    dag.add_edge(1, 2);
    dag.add_edge(2, 3);
    dag.add_edge(3, 1);

    // DAGの構築
    dag.build();

    // DAGの構築成功判定
    if (dag.is_build_success()) {
        cout << "Success" << endl;

        // DAGの出力（頂点をトポロジカル順序で出力）
        for(long long i=0; i<N; i++) {
            cout << dag.dag[i] << endl;
        }
    } else {
        cout << "Failed" << endl;
    }
    // Failed
}

void test4() {
    cout << "===test4===" << endl;
    long long N = 6;

    // DAGの宣言
    DAG dag = DAG<long long>(N);

    // 辺を追加する
    // 以下のようなグラフでも、トポロジカルソートは成功したとみなす
    // 0 → 1
    // 2 → 3 → 4
    // 5
    dag.add_edge(2, 3);
    dag.add_edge(3, 4);
    dag.add_edge(0, 1);

    // DAGの構築
    dag.build();

    // DAGの構築成功判定
    if (dag.is_build_success()) {
        cout << "Success" << endl;
        // DAGの出力（頂点をトポロジカル順序で出力）
        for(long long i=0; i<N; i++) {
            cout << dag.dag[i] << endl;
        }
    }
    else {
        cout << "Failed" << endl;
    }
    // Success
    // 0
    // 2
    // 5
    // 1
    // 3
    // 4
}

int main(int argc, char const *argv[]){
    test0();
    test1();
    test2();
    test3();
    test4();
    return 0;
}