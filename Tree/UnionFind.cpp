#include <bits/stdc++.h>
using namespace std;


/***
 *  UnionFindVerDepth
 *
 * Descriptions:
 *  UnionFindの深さバージョン
 *  グループの併合のとき、木の深さが深いものに浅いものを併合する
 *  あまり使わない。競プロでは後述のサイズバージョンのほうをよく使う。
 *
 * Args
 *  N(T): N個のノードのUnionFindを作成する
 *
 ***/
template <typename T>
struct UnionFindVerDepth {
    private:
        vector<T> depths;   // グループの深さ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
        T group_num;  // 連結成分の個数

    public:
        UnionFindVerDepth(T N=0): depths(N,-1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
            this->group_num = N;
        }

        T find_root(T x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(T x, T y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            T gx = this->find_root(x); T gy = this->find_root(y);
            if (gx == gy) return;

            // 深い方が浅い方を併合する（木の偏りが減るので）
            if (this->depths[gx] < this->depths[gy]) {
                this->parents[gx] = gy;
            }
            else {
                this->parents[gy] = gx;
                if (this->depths[gx] == this->depths[gy]) this->depths[gx] += 1;
            }
            this->group_num--;
        }

        T get_depth(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->depths[this->find_root(x)];
        }

        bool is_same_group(T x, T y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        T get_group_num() {
            /* 連結成分の個数を返す */
            return this->group_num;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (T i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_depths() {
            /* デバッグ用depthsの中身を出力する */
            for (T i=0; i<this->depths.size(); i++) {
                cout << this->depths[i] << endl;
            }
        }
};


/***
 *  UnionFindVerSize
 *
 * Descriptions:
 *  UnionFindのサイズバージョン
 *  グループの併合のとき、サイズが大きい方が、小さい方を併合する
 *  競プロでは、ノードの個数やグループの最小値とかを求めるので、こちらを使うことが多い
 *
 * Args
 *  N(T): N個のノードのUnionFindを作成する
 *
 * ならし計算量
 *  O(α(N))
 *    - α(N)はアッカーマン関数
 *    - 相当小さい（logより小さい）
 ***/
template <typename T>
struct UnionFindVerSize {
    private:
        vector<T> sizes;   // グループのサイズ
        vector<T> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる
        T group_num;  // 連結成分の個数

    public:
        UnionFindVerSize(T N=0): sizes(N,1), parents(N) {
            for (T i=0; i<N; i++) {
                parents[i] = i;
            }
            this->group_num = N;
        }

        T find_root(T x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(T x, T y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            T gx = this->find_root(x); T gy = this->find_root(y);
            if (gx == gy) return;

            // 深い方が浅い方を併合する（木の偏りが減るので）
            if (this->sizes[gx] < this->sizes[gy]) {
                this->parents[gx] = gy;
                this->sizes[gy] += this->sizes[gx];
            }
            else {
                this->parents[gy] = gx;
                this->sizes[gx] += this->sizes[gy];
            }
            this->group_num--;
        }

        T get_size(T x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }

        bool is_same_group(T x, T y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        T get_group_num() {
            /* 連結成分の個数を返す */
            return this->group_num;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (T i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (T i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};


/***クラスカル法
 * Descriptions:
 *  最小全域木と、最小全域木のコストを求める
 * Returns:
 *  pair<UnionFind, long long>
 *   最小全域木(UnionFind)
 *   最小全域木のコスト(long long)
 * Notes:
 *  クラスカル法自体の計算量はO(|E| log|V|)
 *  ただし内部でUnionFindを実行している
 ***/
struct edge {long long u, v, cost; };  // 頂点uと頂点vを結ぶ無向辺（コスト：cost）

bool comp(const edge& e1, const edge& e2) {
    return e1.cost < e2.cost;
}

pair<UnionFindVerSize<long long>, long long> kruskal(vector<edge> es, long long V) {
    sort(es.begin(), es.end(), comp);  // edge.costが小さい順にソートする
    UnionFindVerSize uf = UnionFindVerSize<long long>(V);

    long long res = 0;  // 最小全域木のコスト
    for (long long i=0; i<(long long)es.size(); i++) {
        edge e = es[i];
        if (!uf.is_same_group(e.u, e.v)) {
            uf.unite(e.u, e.v);
            res += e.cost;
        }
    }
    return {uf, res};
}


void test1() {
    cout << "===test1===" << endl;
    // UnionFindのテストコード
    int N = 10;
    UnionFindVerSize<int> uf = UnionFindVerSize<int>(N);

    uf.unite(0, 1);
    uf.unite(1, 2);
    uf.unite(2, 3);
    uf.unite(4, 5);
    uf.unite(4, 6);
    // {0, 1, 2, 3}, {4, 5, 6}, {7}, {8}, {9} の5グループ

    cout << uf.find_root(2) << endl;
    // 0
    cout << uf.get_size(2) << endl;
    // 4
    cout << (uf.is_same_group(3, 4)?"true" : "false") << endl;
    // false
    cout << uf.get_group_num() << endl;
    // 5
}

void test2() {
    cout << "===test2===" << endl;
    // クラスカル法のテストコード
    long long V = 5;  // 頂点数
    long long E = 8;  // 辺数
    vector<edge> es(E);

    // グラフを構築
    es[0] = edge{0, 1, 10};
    es[1] = edge{0, 3, 5};
    es[2] = edge{1, 2, 1};
    es[3] = edge{1, 3, 1000};
    es[4] = edge{1, 4, 500};
    es[5] = edge{2, 3, 100};
    es[6] = edge{2, 4, 10000};
    es[7] = edge{3, 4, 5000};

    // 最小全域木と最小全域木のコストを求める
    auto [uf, cost] = kruskal(es, V);
    cout << "MST Cost: " << cost << endl;
    // MST Cost: 516
}

int main() {
    test1();
    test2();
    return 0;
}