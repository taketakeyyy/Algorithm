#include <bits/stdc++.h>
using namespace std;

/***
 * シンプルな最小公倍数の求め方
 * LCM(a, b)を求める
 * C++17では、numericライブラリの中にgcd,lcmがあるので、それ使えばいい
 **/
template<typename T>
T lcm(T a, T b) {
    return a * b / gcd(a, b);
}

void test1(){
    // 038 - Large LCM（★3）の入力例を試す
    // https://atcoder.jp/contests/typical90/tasks/typical90_al
    cout << "===test1===" << endl;
    long long a = 4, b = 6;
    long long ans = lcm<long long>(a, b);

    // 出力
    cout << "lcm(" << a << ", " << b << ") = " << ans << endl;
}

void test2(){
    cout << "===test2===" << endl;
    long long a = 2, b = 30;
    long long ans = lcm<long long>(a, b);

    // 出力
    cout << "lcm(" << a << ", " << b << ") = " << ans << endl;
}

void test3(){
    cout << "===test3===" << endl;
    long long a = 60, b = 40;
    long long ans = lcm<long long>(a, b);

    // 出力
    cout << "lcm(" << a << ", " << b << ") = " << ans << endl;
}

void test4(){
    cout << "===test4===" << endl;
    long long a = 7, b = 9;
    long long ans = lcm<long long>(a, b);

    // 出力
    cout << "lcm(" << a << ", " << b << ") = " << ans << endl;
}


int main(int argc, char const *argv[]){
    test1();
    test2();
    test3();
    test4();
    return 0;
}