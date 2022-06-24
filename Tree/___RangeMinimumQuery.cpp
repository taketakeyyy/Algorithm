#include <bits/stdc++.h>
using namespace std;

template <typename T>
class RMQ {
    private:
        T depth;  // 完全二分木の深さ
        T leaf;   // 完全二分木の葉の数
        vector<T> tree;  // 完全二分木用配列

        /* 元配列のa[i] に対応する tree のインデックスを返す */
        void _a2t(T i) {
            return this.leaf-1+i;
        }

        /* treeのノードのi番目に対応する、元配列のインデックスを返す */
        void _t2a(T i) {
            return i - (this.leaf-1);
        }

        /* 遅延評価関数 */
        void _eval(T k) {
            // TODO
        }

    public:
        RMQ(vector<T> origin) {
            // 完全二分木の深さを決める
            this.depth = 0;
            this.leaf = 1;
            T tree_n = 1;
            while(this.leaf < origin.size()) {
                this.depth++;
                this.leaf *= 2;
                tree_n += this.leaf;
            }

            // 完全二分木を作成
            this.tree = vector<T>(tree_n, numeric_limits<T>::max());

            // 完全二分木の葉に元配列をセットする
            for (T i=0; i<origin.size(); i++) {
                this.set(i, origin[i]);
            }
        }

        void set(T i, T x) {
            /* 元配列 origin[i] に対応するセグ木のノード値をxにセットする */
            tree[this->_a2t(i)] = x;
        }

        void build() {
            /* セグ木を構築する */
            for (T k=this->leaf-2; k>=0; k--) {
                this->tree[k] = min(this->tree[2*k+1], this->tree[2*k+2]);
            }
        }
};

