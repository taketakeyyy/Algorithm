#include <bits/stdc++.h>
using namespace std;

/***ローリングハッシュ法で文字列検索
 * 計算量はO(N+M)
 ***/
const unsigned long long B = 100000007;  // ハッシュの基数

/***文字列s1はs2に含まれているか？
 * Returns:
 *  含まれている場合、一致箇所の開始位置であるs2のインデックスを返す
 *  含まれていなかった場合、-1を返す
 **/
long long contain(string s1, string s2) {
    long long s1_len = s1.length();
    long long s2_len = s2.length();

    if (s1_len > s2_len) return -1;

    // Bのs1_len乗を計算する
    unsigned long long t = 1;
    for (long long i=0; i<s1_len; i++) t *= B;

    // s1とs2の最初のs1_len文字に関するハッシュ値を計算する
    unsigned long long s1h = 0, s2h = 0;  // ハッシュ値
    for (long long i=0; i<s1_len; i++) s1h = s1h * B + s1[i];
    for (long long i=0; i<s1_len; i++) s2h = s2h * B + s2[i];

    // s2の場所を1つずつ進めながらハッシュ値をチェック
    for (long long i=0; i+s1_len<=s2_len; i++) {
        if (s1h == s2h) return i;  // s2のi文字目からのs1_len文字が一致
        if (i+s1_len < s2_len) s2h = s2h * B + s2[i+s1_len] - s2[i]*t;
    }

    return -1;
 }


/***文字列s1の末尾とs2の先頭を何文字重ねることができるか？
 * Returns:
 *  重なっている文字数を返す。
 *  重なっていなかった場合、0を返す
 ***/
long long overlap(string s1, string s2) {
    long long s1_len = s1.length();
    long long s2_len = s2.length();
    long long ans = 0;
    unsigned long long s1h = 0, s2h = 0;  // ハッシュ値
    unsigned long long t = 1;

    for (long long i=1; i<=min(s1_len, s2_len); i++) {
        s1h = s1h + s1[s1_len-i]*t;  // s1の末尾i文字のハッシュ値
        s2h = s2h * B + s2[i-1];     // s2の先頭i文字のハッシュ値
        if (s1h == s2h) ans = i;
        t *= B;
    }

    return ans;
}


void test1() {
    cout << "===test1===" << endl;

    string s1 = "note";
    string s2 = "I have a pen, eraser, notebook.";

    long long idx = contain(s1, s2);
    if (idx != -1) {
        cout << "Contain!" << endl;
    }
    else {
        cout << "Not Contain." << endl;
    }
    // Contain!
}

void test2() {
    cout << "===test2===" << endl;

    string s1 = "I have a pen, eraser, notebook.";
    string s2 = "I have a pen, eraser, notebook.";

    long long idx = contain(s1, s2);
    if (idx != -1) {
        cout << "Contain!" << endl;
    }
    else {
        cout << "Not Contain." << endl;
    }
    // Contain!
}

void test3() {
    cout << "===test3===" << endl;

    string s1 = "notebook!";
    string s2 = "I have a pen, eraser, notebook.";

    long long idx = contain(s1, s2);
    if (idx != -1) {
        cout << "Contain!" << endl;
    }
    else {
        cout << "Not Contain." << endl;
    }
    // Not Contain
}

void test4() {
    cout << "===test4===" << endl;

    string s1 = "NMLKJIHGFEDCBA";
    string s2 = "ABCDEFGHIJKLMN";

    // s1の末尾と、s2の先頭は何文字重なっているか？
    long long cnt = overlap(s1, s2);
    cout << "Overlap: " << cnt << endl;
    // Overlap: 1
}

void test5() {
    cout << "===test5===" << endl;

    string s1 = "NMLKJIHGFED ABC";
    string s2 = "ABCDEFGHIJKLMN";

    // s1の末尾と、s2の先頭は何文字重なっているか？
    long long cnt = overlap(s1, s2);
    cout << "Overlap: " << cnt << endl;
    // Overlap: 3
}

void test6() {
    cout << "===test6===" << endl;

    string s1 = "NMLKJIHGFED ABC";
    string s2 = "abcdefghijklmn";

    // s1の末尾と、s2の先頭は何文字重なっているか？
    long long cnt = overlap(s1, s2);
    cout << "Overlap: " << cnt << endl;
    // Overlap: 0
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    return 0;
}