#include <bits/stdc++.h>
using namespace std;


/*** 拡張ユークリッドの互除法
 * Descriptions
 *  ax + by = gcd(a,b) となる整数 x, y を求める
 *
 * Returns
 *  gcd(a, b)を返す
 *
 * Usage
 *  // 111x + 30y = gcd(111, 30) となる x, y を求めたい
 *  long long a = 111, b = 30;
 *  long long x, y;
 *  long long g = extgcd<long long>(a, b, x, y);
 *  cout << "gcd(a,b)=" << g << ", x=" << x << ", y=" << y << endl;
 *  // gcd(a,b)=3, x=3, y=-11
 **/
template<typename T>
T extgcd(T a, T b, T& x, T& y) {
    T d = a;
    if (b!=0LL) {
        d = extgcd(b, a%b, y, x);
        y -= (a/b)*x;
    }
    else {
        x = 1LL; y = 0LL;
    }
    return d;
}

void test(){
    long long a, b, x, y, g;

    a=111LL; b=30LL;
    g = extgcd<long long>(a, b, x, y);
    cout << "gcd(a,b)=" << g << ", x=" << x << ", y=" << y << endl;
    // gcd(a,b)=3, x=3, y=-11

    a=30LL; b=111LL;
    g = extgcd<long long>(a, b, x, y);
    cout << "gcd(a,b)=" << g << ", x=" << x << ", y=" << y << endl;
    // gcd(a,b)=3, x=-11, y=3

    a=11LL; b=4LL;
    g = extgcd<long long>(a, b, x, y);
    cout << "gcd(a,b)=" << g << ", x=" << x << ", y=" << y << endl;
    // gcd(a,b)=1, x=-1, y=3

    a=4LL; b=11LL;
    g = extgcd<long long>(a, b, x, y);
    cout << "gcd(a,b)=" << g << ", x=" << x << ", y=" << y << endl;
    // gcd(a,b)=1, x=3, y=-1

    /* [問題] 111x + 30y = 12となる整数x,yを求めよ */
    a, b = 111LL, 30LL;
    g = extgcd<long long>(a, b, x, y);
    // g = 3より、
    // 111x + 30y = 3の整数解が x=3, y=-11
    // 求めたい解は、両辺4倍すればよい。よって4x,4yが答え
}


int main() {
    test();
    return 0;
}