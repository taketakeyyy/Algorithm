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
 *  N(int): N個のノードのUnionFindを作成する
 *
 ***/
struct UnionFindVerDepth {
    private:
        vector<int> depths;   // グループの深さ
        vector<int> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる

    public:
        UnionFindVerDepth(int N=0): depths(N,-1), parents(N) {
            for (int i=0; i<N; i++) {
                parents[i] = i;
            }
        }

        int find_root(int x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(int x, int y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            int gx = this->find_root(x); int gy = this->find_root(y);
            if (gx == gy) return;

            // 深い方が浅い方を併合する（木の偏りが減るので）
            if (this->depths[gx] < this->depths[gy]) {
                this->parents[gx] = gy;
            }
            else {
                this->parents[gy] = gx;
                if (this->depths[gx] == this->depths[gy]) this->depths[gx] += 1;
            }
        }

        int get_depth(int x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->depths[this->find_root(x)];
        }

        bool is_same_group(int x, int y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        int calc_group_num() {
            /* グループ数を計算して返す */
            int ans = 0;
            for (int i=0; i<this->parents.size(); i++) {
                if (i == this->find_root(i)) ans++;
            }
            return ans;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (int i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_depths() {
            /* デバッグ用depthsの中身を出力する */
            for (int i=0; i<this->depths.size(); i++) {
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
 *  N(int): N個のノードのUnionFindを作成する
 *
 ***/
struct UnionFindVerSize {
    private:
        vector<int> sizes;   // グループのサイズ
        vector<int> parents;  // 親の番号を格納する。自分が親の場合は自分の番号になり、それがそのグループの番号になる

    public:
        UnionFindVerSize(int N=0): sizes(N,1), parents(N) {
            for (int i=0; i<N; i++) {
                parents[i] = i;
            }
        }

        int find_root(int x) {
            /* ノード番号xの木の根（xがどのグループか）を求める */
            if (this->parents[x] == x) return x;
            this->parents[x] = this->find_root(this->parents[x]);  // 縮約
            return this->parents[x];
        }

        void unite(int x, int y) {
            /* ノード番号xとyが属する木を併合する（グループの併合） */
            int gx = this->find_root(x); int gy = this->find_root(y);
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
        }

        int get_size(int x) {
            /* ノード番号xが属するグループの深さを返す */
            return this->sizes[this->find_root(x)];
        }

        bool is_same_group(int x, int y) {
            /* ノード番号xとyが同じ集合に属するか否か */
            return this->find_root(x) == this->find_root(y);
        }

        int calc_group_num() {
            /* グループ数を計算して返す */
            int ans = 0;
            for (int i=0; i<this->parents.size(); i++) {
                if (i == this->find_root(i)) ans++;
            }
            return ans;
        }

        void print_parents() {
            /* デバッグ用parentsの中身を出力する */
            for (int i=0; i<this->parents.size(); i++) {
                cout << this->parents[i] << endl;
            }
        }

        void print_sizes() {
            /* デバッグ用sizesの中身を出力する */
            for (int i=0; i<this->sizes.size(); i++) {
                cout << this->sizes[i] << endl;
            }
        }
};


int main() {
    int N = 10;
    UnionFindVerSize uf = UnionFindVerSize(N);

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
    cout << uf.calc_group_num() << endl;
    // 5

    return 0;
}