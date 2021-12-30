#include <bits/stdc++.h>
using namespace std;

/***SegmentTree_LazyRMQ
 *  いわゆる遅延評価セグメント木
 *  通常のセグ木に比べて、以下のことができる
 *  - 区間更新：[a, b)の値をxに更新する
 *  - 区間加算：[a, b)の値にxを加算する
 ***/

template <typename T>
class SegmentTree_LazyRMQ {
    /* Lazy Renge Minimum Query */

    private:
        const T INF = numeric_limits<T>::max();
        T _lst2node(T i) {
            /* 元の配列lstのi番目を、セグ木のノード番号に変換する */
            return i+this->N-1;
        }

        T _node2lst(T i) {
            /* セグ木のノードのi番目を、元の配列 lst の添字に変換する */
            return i - (this->N-1);
        }

        void _eval(T k) {
            /* 遅延評価関数 */
            if (this->lazy[k] == this->INF) return;
            if (k < this->N-1) {
                this->lazy[2*k+1] = this->lazy[k];
                this->lazy[2*k+2] = this->lazy[k];
            }
            // 自身を更新
            this->nodes[k] = this->lazy[k];
            this->lazy[k] = this->INF;
        }

        void _update(T a, T b, T x, T k, T l, T r) {
            /* 区間 [a, b) に対して、担当区間 [l, r) のノード k が応答する */
            this->_eval(k);
            if (a<=l && r<=b) {
                // 担当区間がすっぽり含まれる場合
                this->lazy[k] = x;
                this->_eval(k);
            }
            else if (a<r && l<b){
                // 一部区間が被る場合
                this->_update(a, b, x, 2*k+1, l, (l+r)/2);  // 左の子
                this->_update(a, b, x, 2*k+2, (l+r)/2, r);  // 右の子
                this->nodes[k] = min(this->nodes[2*k+1], this->nodes[2*k+2]);
            }
        }

        T _query(T a, T b, T k, T l, T r) {
            /* 区間 [a,b) のクエリに対して、担当区間 [l,r) のノード k が応答する */
            this->_eval(k);
            if (r<=a || b<=l) {
                // 区間がかぶらない場合
                return this->INF;
            }
            if (a<=l && r<=b) {
                // 担当区間がすっぽり含まれる場合
                return this->nodes[k];
            }
            // それ以外
            T ret1 = this->_query(a, b, 2*k+1, l, (l+r)/2);  // 左の子に聞く
            T ret2 = this->_query(a, b, 2*k+2, (l+r)/2, r);  // 右の子に聞く
            return min(ret1, ret2);
        }

        T _find_rightest(T a, T b, T x, T k, T l, T r) {
            /* 区間 [a, b) に対して、担当区間 [l, r) のノード k が応答する */
            this->_eval(k);
            if (this->nodes[k]>x || r <= a || b <= l) {
                // 自分の値がxより大きい or [a,b)が[l,r)の範囲外の場合
                return a-1;
            }
            else if (k >= this->N-1) {
                // 自分が葉の場合
                return this->_node2lst(k);
            }
            else {
                T ret = this->_find_rightest(a, b, x, 2*k+2, (l+r)/2, r);
                if (ret != a-1) {
                    // 右の部分木を見て a-1 以外なら終了
                    return ret;
                }
                else {
                    // 左の部分木を見る
                    return this->_find_rightest(a, b, x, 2*k+1, l, (l+r)/2);
                }
            }
        }

        T _find_leftest(T a, T b, T x, T k, T l, T r) {
            /* 区間 [a, b) に対して、担当区間 [l, r) のノード k が応答する */
            this->_eval(k);
            if (this->nodes[k]>x || r <= a || b <= l) {
                // 自分の値がxより大きい or [a,b)が[l,r)の範囲外の場合
                return b;
            }
            else if (k >= this->N-1) {
                // 自分が葉の場合
                return this->_node2lst(k);
            }
            else {
                T ret = this->_find_leftest(a, b, x, 2*k+1, l, (l+r)/2);
                if (ret != b) {
                    // 左の部分木を見て b 以外なら終了
                    return ret;
                }
                else {
                    // 右の部分木を見る
                    return this->_find_leftest(a, b, x, 2*k+2, (l+r)/2, r);
                }
            }
        }

    public:
        T N;  // セグ木の葉の数
        T list_size;  // 元の配列(lst)のサイズ
        vector<T> nodes, lazy;  // セグ木のノードと、遅延評価用のノード
        SegmentTree_LazyRMQ(T n) {
            /***
             * Args:
             *  n(T): 元の配列の要素数
             ***/
            this->list_size = n;

            T x = 1;
            while (n > x) x *= 2;
            this->N = x;

            this->nodes.assign(this->N*2-1, this->INF);
            this->lazy.assign(this->N*2-1, this->INF);
        }

        void set(T i, T x) {
            /* セグ木の葉に値をセットする（セットするだけ。セグ木を構築するときはbuild()を呼ぶ） */
            T ni = this->_lst2node(i);
            this->nodes[ni] = x;
        }

        void build() {
            /* セグ木を構築する */
            for (T k=this->N-2; k>=0; k--) {
                this->nodes[k] = min(this->nodes[2*k+1], this->nodes[2*k+2]);
            }
        }

        void update(T a, T b, T x) {
            /* 区間 [a, b) の値を x に変更し、セグ木全体を更新する */
            this->_update(a, b, x, 0, 0, this->N);
        }

        T query(T a, T b) {
            /* 区間 [a,b) のクエリに応答する */
            return this->_query(a, b, 0, 0, this->N);
        }

        T find_rightest(T a, T b, T x) {
            /* 区間 [a, b) で x 以下の要素を持つ最右位置を返す
             * 見つからなかった場合、-1を返す
             */
            return _find_rightest(a, b, x, 0, 0, this->N);
        }

        T find_leftest(T a, T b, T x) {
            /* 区間 [a, b) で x 以下の要素を持つ最左位置を返す
             * 見つからなかった場合、list_size以上の番号を返す
             */
            return _find_leftest(a, b, x, 0, 0, this->N);
        }
};


void test1(){
    cout << "===test1===" << endl;

    /* 元の配列 lst */
    vector<int> lst = {7, 3, 5, 4, 8, 9, 1, 0, 1, 3, 9, 4, 6, 2, 1, 9, 4, 5, 6, 7, 3, 5, 4, 1, 1, 2, 6, 8, 9, 5, 3};

    /* LazyRMQの作成と構築 */
    SegmentTree_LazyRMQ lazyrmq = SegmentTree_LazyRMQ<int>((int)lst.size());
    for(int i=0; i<(int)lst.size(); i++) {
        lazyrmq.set(i, lst[i]);
    }
    lazyrmq.build();

    /* lst [1, 10) の最小値を求める */
    cout << "lazyrmq.query(1, 10): " << lazyrmq.query(1, 10) << endl;
    // lazyrmq.query(1, 10): 0

    /* lst [6, 10) の値を 100 に変更した後、再度lst [1, 10)の最小値を求める */
    lazyrmq.update(6, 10, 100);
    cout << "lazyrmq.query(1, 10): " << lazyrmq.query(1, 10) << endl;
    // lazyrmq.query(1, 10): 3

    /* lst全体の最小値を求める */
    cout << "lazyrmq.query(0, lst.size()): " << lazyrmq.query(0, lst.size()) << endl;
    // lazyrmq.query(0, lst.size()): 1

    /* lst全体の区間で、2以下の最右位置を求める */
    cout << "lazyrmq.find_rightest(0, lst.size(), 2): " << lazyrmq.find_rightest(0, lst.size(), 2) << endl;
    // lazyrmq.find_rightest(0, lst.size(), 2): 25

    /* lst全体の区間で、2以下の最左位置を求める */
    cout << "lazyrmq.find_leftest(0, lst.size(), 2): " << lazyrmq.find_leftest(0, lst.size(), 2) << endl;
    // lazyrmq.find_leftest(0, lst.size(), 2): 13

    /* [14, lst.size())の区間で、2以下の最左位置を求める */
    cout << "lazyrmq.find_leftest(14, lst.size(), 2): " << lazyrmq.find_leftest(14, lst.size(), 2) << endl;
    // lazyrmq.find_leftest(14, lst.size(), 2): 14
}

void test2(){
    cout << "===test2===" << endl;

    /* 元の配列 lst */
    vector<int> lst = {7, 3, 5, 4, 8};

    /* LazyRMQの作成と構築 */
    SegmentTree_LazyRMQ lazyrmq = SegmentTree_LazyRMQ<int>((int)lst.size());
    for(int i=0; i<(int)lst.size(); i++) {
        lazyrmq.set(i, lst[i]);
    }
    lazyrmq.build();

    /* lst全体の区間で、2以下の最右位置を求める */
    cout << "lazyrmq.find_rightest(0, lst.size(), 2): " << lazyrmq.find_rightest(0, lst.size(), 2) << endl;
    // lazyrmq.find_rightest(0, lst.size(), 2): -1

    /* lst全体の区間で、2以下の最左位置を求める */
    cout << "lazyrmq.find_leftest(0, lst.size(), 2): " << lazyrmq.find_leftest(0, lst.size(), 2) << endl;
    // lazyrmq.find_leftest(0, lst.size(), 2): 5
}

int main(int argc, char const *argv[]){
    test1();
    test2();
    return 0;
}