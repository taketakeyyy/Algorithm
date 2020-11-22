#include <bits/stdc++.h>
using namespace std;

// http://hos.ac/slides/20140319_bit.pdf
/*** BIT実装例
・N個の変数 v[1], ..., v[N]
    - すべて0で初期化
・2種類のクエリ
    - v[a]に値wを加える
    - prefix[1,a]のところの区間和v[1]+v[2]+..+v[a]を求める
・クエリあたりO(logN)時間にしたい

bit[1]からbit[N]までを使用(便宜上bit[0]は使用しない)
bit[1] := v[1]
bit[2] := v[1]+v[2]
bit[3] := v[3]
bit[4] := v[1]+v[2]+v[3]+v[4]
bit[5] := v[5]
***/
class BIT {
    public:
        int N;  // 要素数
        vector<int> bit;  // bit配列

        BIT(int n) {
            this->N = n;
            this->bit.resize(n+1, 0);
        }

        void add(int a, int w) {
            /***v[a]番目に値wを加える
            O(logN)
            ***/
            int x = a;
            while (x <= this->N) {
                this->bit[x] += w;
                x += x&-x;
            }
        }

        int sum(int a) {
            /***vの区間[1,a]の和を求める
            O(logN)
            ***/
            int ret = 0; int x = a;
            while (x > 0) {
                ret += this->bit[x];
                x -= x&-x;
            }
            return ret;
        }
};

/***v[a]を0以外の値で初期化
・addをN回呼び出せばO(NlogN)時間
    - 殆どの場合これで十分
・v[x]=1 で初期化するならbit[x] = x & -x
・一般にはbit[x]をv[x]で初期化したのち、
for (int x=1; x<N; ++x) bit[x + (x&-x)] += bit[x];
***/

void test1() {
    /***例題
    v[1]=1, v[2]=2, v[3]=3, ... , v[100]=100 について考える
    ***/
    /* 初期化 */
    int N = 100;
    BIT bit = BIT(N);
    for (int i=1; i<N+1; i++) {
        bit.add(i, i);
    }

    /* bitの中身を見る */
    for (int i=0; i<bit.N+1; i++) {
        cout << bit.bit[i] << " ";
    }
    // 0 1 3 3 10 5 11 7 36 9 19 11 42 13 27 15 136 17 35 19 74 21 43 23 164 25 51 27 106 29 59 31 528 33 67 35 138 37 75 39 292 41 83 43 170 45 91 47 648 49 99 51 202 53 107 55 420 57 115 59 234 61 123 63 2080 65 131 67 266 69 139 71 548 73 147 75 298 77 155 79 1160 81 163 83 330 85 171 87 676 89 179 91 362 93 187 95 2576 97 195 99 394
    cout << endl;

    /* vの[1,50]の区間和を求める */
    cout << "sum of [1,50]:" << bit.sum(50) << endl;
    // sum of [1,50]:1275

    /* vの[30,50]の区間和を求める */
    cout << "sum of [30,50]:" << bit.sum(50) - bit.sum(29) << endl;
    // sum of [30,50]:840
}


int main(int argc, char const *argv[]){
    test1();
    return 0;
}