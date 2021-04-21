#include <stdio.h>
#include <iostream>
#include <tuple>
#include <vector>
#include <deque>
#include <map>

using namespace std;


int partition(vector<int>& A, int l, int r) {
    /* 配列A[l]~A[r]までの区間を、
     * - pivot以下の配列A[l..q]と、
     * - pivotより大きい配列A[q+1..r]に分割する
     * pivotのインデックス番号qを返す
     */
    int pivot = A[r];
    int q = l;
    for(int j=l; j<=r; j++) {
        if (A[j] <= pivot) {
            swap(A[q], A[j]);
            q++;
        }
    }
    return q-1;
}

void quick_sort(vector<int>& A, int l, int r) {
    if (l < r) {
        int q = partition(A, l, r);
        quick_sort(A, l, q-1);
        quick_sort(A, q+1, r);
    }
}

void test1() {
    cout << "===test1===" << endl;
    vector<int> A = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 5, 3, 14, 6, 11};
    int N = A.size();

    quick_sort(A, 0, N-1);

    // 出力
    for(int i=0; i<N; i++) {
        cout << A[i];
        if (i!=N-1) cout << " ";
    }
    cout << endl;
}

void test2() {
    cout << "===test2===" << endl;
    vector<int> A = {10,9,8,7,6,5,4,3,2,1};
    int N = A.size();

    quick_sort(A, 0, N-1);

    // 出力
    for(int i=0; i<N; i++) {
        cout << A[i];
        if (i!=N-1) cout << " ";
    }
    cout << endl;
}

void test3() {
    cout << "===test3===" << endl;
    vector<int> A = {0};
    int N = A.size();

    quick_sort(A, 0, N-1);

    // 出力
    for(int i=0; i<N; i++) {
        cout << A[i];
        if (i!=N-1) cout << " ";
    }
    cout << endl;
}

int main() {
    test1();
    test2();
    test3();
    return 0;
}