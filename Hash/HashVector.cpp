#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

/**
 * @brief vector用ハッシュ
 *
 * @example
 *  // ハッシュ作成
 *  vector<int> A = {1,2,3};
 *  HashVector hv = HashVector();
 *  int hash1 = hv(A);
 *
 *  // unordered_mapのキーにvector<int>を指定する
 *  unordered_map<vector<int>, int, HashVector> mp;
 */
struct HashVector {
    static size_t m_hash_random; // 実行時のランダム要素を入れることで、ハッシュ衝突のhackを避ける

    template<class T>
    size_t operator()(const vector<T> &vec) const {
        size_t seed = 0;
        for(size_t i=0; i<vec.size(); i++) {
            auto hash1 = hash<T>{}(vec.at(i));
            seed ^= hash1 + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }
        seed ^= m_hash_random + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};
size_t HashVector::m_hash_random = (size_t)random_device()();


void test1() {
    // 5 1 3 2 4
    cout << "===test1===" << endl;
    vector<ll> A = {5, 1, 3, 2, 4};

    // ハッシュ作成
    HashVector hv = HashVector();
    size_t hash1 = hv(A);
    cout << "hash: " << hash1 << endl;
    // hash: 3005401624104587517 (実行ごとに値は変わる)

    // unordered_mapのキーにvector<ll>を指定する
    unordered_map<vector<ll>, ll, HashVector> mp;
    mp[A] = 1;
    cout << mp[A] << endl;
    // 1
}


int main() {
    test1();
    return 0;
}