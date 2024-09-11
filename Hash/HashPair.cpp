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
 * @brief pair用ハッシュ
 *
 * @example
 *  // ハッシュ作成
 *  pair<int,int> p = {1,2};
 *  HashPair hp = HashPair();
 *  int hash1 = hp(p);
 *
 *  // unordered_mapのキーにpair<int,int>を指定する
 *  unordered_map<pair<int,int>, int, HashPair> mp;
 */
struct HashPair {
    static size_t m_hash_random; // 実行時のランダム要素を入れることで、ハッシュ衝突のhackを避ける

    template<class T1, class T2>
    size_t operator()(const pair<T1, T2> &p) const {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        size_t seed = 0;
        seed ^= hash1 + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= hash2 + 0x9e3779b9 + (seed<<6) + (seed>>2);
        seed ^= m_hash_random + 0x9e3779b9 + (seed<<6) + (seed>>2);
        return seed;
    }
};
size_t HashPair::m_hash_random = (size_t)random_device()();


void test1() {
    cout << "===test1===" << endl;
    pair<ll,ll> p = {1,2};

    // ハッシュ作成
    HashPair hp = HashPair();
    size_t hash1 = hp(p);
    cout << "hash: " << hash1 << endl;
    // hash: 11091699636195 (実行ごとに値は変わる)

    // unordered_mapのキーにpair<ll,ll>を指定する
    unordered_map<pair<ll,ll>, ll, HashPair> mp;
    mp[p] = 1;
    cout << mp[p] << endl;
    // 1
}


int main() {
    test1();
    return 0;
}