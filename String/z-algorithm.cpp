#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Z-Algorithm
 * 各iについて、S と S.substr(i)の共通接頭辞の長さを格納した配列Zを求める。
 *
 * @tparam T
 * @param S 文字列S
 * @return vector<T> 各iについて共通接頭辞の長さを格納した配列Zを返す。
 */
template <typename T>
vector<T> z_algorithm(string S) {
    T n = S.size();
    vector<T> z(n, 0);
    z[0] = n;

    T i=1, j=0;
    while(i < n) {
        while(i+j<n && S[j]==S[i+j]) j++;
        z[i] = j;

        if (j == 0) {
            i++; continue;
        }

        T k = 1;
        while(k<j && k+z[k]<j) {
            z[i+k] = z[k];
            k++;
        }
        i += k;
        j -= k;
    }

    return z;
}

void test1 () {
    cout << "===test1===" << endl;

    string str = "abcbcba";
    auto z = z_algorithm<int>(str);
    for(int val: z) {
        cout << val << " ";
    }
    cout << endl;
    // 7 0 0 0 0 0 1
}

void test2 () {
    cout << "===test2===" << endl;

    string str = "mississippi";
    auto z = z_algorithm<int>(str);
    for(int val: z) {
        cout << val << " ";
    }
    cout << endl;
    // 11 0 0 0 0 0 0 0 0 0 0
}

void test3 () {
    cout << "===test3===" << endl;

    string str = "ababacaca";
    auto z = z_algorithm<int>(str);
    for(int val: z) {
        cout << val << " ";
    }
    cout << endl;
    // 9 0 3 0 1 0 1 0 1
}

void test4 () {
    cout << "===test4===" << endl;

    string str = "aaaaa";
    auto z = z_algorithm<int>(str);
    for(int val: z) {
        cout << val << " ";
    }
    cout << endl;
    // 5 4 3 2 1
}


int main() {
    test1();
    test2();
    test3();
    test4();
    return 0;
}