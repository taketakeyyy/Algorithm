#include <bits/stdc++.h>
using namespace std;

void bubble_sort(vector<int>& A) {
    int N = A.size();

    for(int i=0; i<N; i++) {
        for(int j=0; j<N-1-i; j++) {
            if (A[j] > A[j+1]) {
                swap(A[j], A[j+1]);
            }
        }
    }
}

void test1() {
    cout << "===test1===" << endl;
    vector<int> A = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 5, 3, 14, 6, 11};
    int N = A.size();

    bubble_sort(A);

    // 出力
    for(int i=0; i<N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void test2() {
    cout << "===test2===" << endl;
    vector<int> A = {10,9,8,7,6,5,4,3,2,1};
    int N = A.size();

    bubble_sort(A);

    // 出力
    for(int i=0; i<N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void test3() {
    cout << "===test3===" << endl;
    vector<int> A = {0};
    int N = A.size();

    bubble_sort(A);

    // 出力
    for(int i=0; i<N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}