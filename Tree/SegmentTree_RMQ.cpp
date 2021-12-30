#include <bits/stdc++.h>
using namespace std;


template <typename T>
class SegmentTree_RMQ {
    /* Renge Minimum Query */

    private:
        T _lst2node(T i) {
            /* 元の配列 lst[i] は、セグ木の i+(葉の数)-1 番目のノード */
            return i+this->n-1;
        }

        T _find(T a, T b, T k, T l, T r) {
            /* 区間 [a,b) のクエリに対して、担当区間 [l,r) のノード k が応答する */
            if (r<=a || b<=l) {
                // 区間がかぶらない場合
                return this->max_num;
            }
            if (a<=l && r<=b) {
                // 担当区間がすっぽり含まれる場合
                return this->nodes[k];
            }
            // それ以外
            T ret1 = this->_find(a, b, 2*k+1, l, (l+r)/2);  // 左の子に聞く
            T ret2 = this->_find(a, b, 2*k+2, (l+r)/2, r);  // 右の子に聞く
            return min(ret1, ret2);
        }

    public:
        T max_num;  // セグ木のノードの最大値
        T n;  // セグ木の葉の数
        vector<T> nodes;  // セグ木のノード
        SegmentTree_RMQ(vector<T> lst, T max_num) {
            /***
             * Args:
             *  lst(vector<T>) 元の配列
             *  max_num(T): セグ木の各ノードの初期値
             ***/
            this->max_num = max_num;
            T i = 1; T total = 1;
            while (1) {
                if (lst.size() <= i) break;
                i *= 2;
                total += i;
            }
            this->n = i;
            this->nodes.resize(total, this->max_num);
            for (T i=0; i<lst.size(); i++) {
                this->update(i, lst[i]);
            }
        }

        void update(T i, T x) {
            /* 元の配列 lst[i] に対応するセグ木のノード値をxに変更し、セグ木全体を更新する */
            T ni = this->_lst2node(i);
            this->nodes[ni] = x;
            while (ni > 0) {
                ni = (ni-1)/2;
                T l = ni*2+1; T r = ni*2+2;
                this->nodes[ni] = min(this->nodes[l], this->nodes[r]);
            }
        }

        T query(T a, T b) {
            /* 区間 [a,b) のクエリに応答する */
            return this->_find(a, b, 0, 0, this->n);
        }
};


void test1(){
    /* 元の配列 lst */
    vector<int> lst = {7, 3, 5, 4, 8, 9, 1, 0, 1, 3, 9, 4, 6, 2, 1, 9, 4, 5, 6, 7, 3, 5, 4, 1, 1, 2, 6, 8, 9, 5, 3};

    /* lst を RMQ化する */
    SegmentTree_RMQ rmq = SegmentTree_RMQ<int>(lst, INT_MAX);

    /* lst[1:6]の最小値を求める */
    cout << "rmq.query(1,6)=" << rmq.query(1,6) << endl;
    // rmq.query(1,6)=3

    /* lst[1]=10に変更した後、再度lst[1:6]の最小値を求める */
    rmq.update(1,10);
    cout << "rmq.query(1,6)=" << rmq.query(1,6) << endl;
    // rmq.query(1,6)=4

    /* lst全体の最小値を求める */
    cout << "rmq.query(0,lst.size())=" << rmq.query(0,lst.size()) << endl;
    // rmq.query(0,lst.size())=0
}


int main(int argc, char const *argv[]){
    test1();
    return 0;
}