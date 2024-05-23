#include <bits/stdc++.h>
using namespace std;


/* 分数 */
template<typename T>
struct frac {
    private:
        T a;  // 分子
        T b;  // 分母
    public:
        frac(T a=0, T b=1) {
            this->a = a; this->b = b;
            // 分母が0のときは、無限大扱いにしたい
            if (this->b == 0) {
                this->a = 1;
                return;
            }
            // マイナスは分子につける
            if (b < 0) { this->a=-this->a; this->b=-this->b; }
            // 約分しておく
            T g = gcd<T>(this->a, this->b);
            this->a /= g;
            this->b /= g;
        }
        bool operator<(const frac &other) const {
            return this->a*other.b < other.a*this->b;
        }
        bool operator<=(const frac &other) const {
            return this->a*other.b <= other.a*this->b;
        }
        bool operator>(const frac &other) const {
            return this->a*other.b > other.a*this->b;
        }
        bool operator>=(const frac &other) const {
            return this->a*other.b >= other.a*this->b;
        }
        bool operator==(const frac &other) const {
            return (this->a == other.a) && (this->b == other.b);
        }
        frac operator*(const frac &other) const {
            T na = this->a*other.a;
            T nb = this->b*other.b;
            return frac(na, nb);
        }
        frac operator/(const frac &other) const {
            T na = this->a*other.b;
            T nb = this->b*other.a;
            return frac(na, nb);
        }
        frac operator+(const frac &other) const {
            T l = lcm(this->b, other.b);
            T na1 = this->a*(l/this->b);
            T na2 = other.a*(l/other.b);
            T na = na1 + na2;
            T nb = l;
            return frac(na, nb);
        }
        frac operator-(const frac &other) const {
            T l = lcm(b, other.b);
            T na1 = this->a*(l/this->b);
            T na2 = other.a*(l/other.b);
            T na = na1 - na2;
            T nb = l;
            return frac(na, nb);
        }
        void print() const {
            cout << this->a << "/" << this->b << endl;
        }
};


void test(){
    frac a = frac(1,3);
    frac b = frac(2,5);

    frac c = a * b;
    c.print();  // 2/15

    frac d = a / b;
    d.print();  // 5/6

    frac e = a + b;
    e.print();  // 11/15

    frac f = a - b;
    f.print();  // -1/15

    frac g = a / a;
    g.print();  // 1/1

    frac h = frac(-100, -10);
    h.print();  // 10/1

    frac i = frac(100, -10);
    i.print();  // -10/1

    frac j = frac(4,5) * frac(10, 8);
    j.print();  // 1/1

    frac k = frac(100, 0);
    k.print();  // 1/0
}


int main(int argc, char const *argv[]){
    test();
    return 0;
}