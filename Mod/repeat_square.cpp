#include <bits/stdc++.h>
using namespace std;


long long repeat_square(long long a, long long n, long long m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    if (!(n&1)) {  // nが奇数のとき
        long long t = repeat_square(a, n/2, m);
        return (t*t)%m;
    }
    // nが偶数のとき
    return a * repeat_square(a, n-1, m);
}


void test() {
    long long ans;
    long long a, n, m;

    a = 2LL; n = 20LL; m = pow(10, 9)+7;
    ans = repeat_square(a, n, m);
    cout << ans << endl;
    // 1048576

    a = 2LL; n = 1000000000LL; m = pow(10, 9)+7;
    ans = repeat_square(a, n, m);
    cout << ans << endl;
    // 140625001
}


int main(int argc, char const *argv[]){
    test();
    return 0;
}
