#include <algorithm>
#include <gmp.h>
#include <gmpxx.h>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define all(o) (o).begin(), (o).end()
#define allr(o) (o).rbegin(), (o).rend()
typedef long long ll;
typedef unsigned long long ull;
template <class T> int size(T &x) { return x.size(); }

void factor(double N);

int is_prime(mpz_class N, int reps);

void print_factor(double N);

mpz_class g(mpz_class X, mpz_class N);
void do_pollard(mpz_class N);
mpz_class pollard(mpz_class N);

int main() {
    mpz_class N;
    mpz_class polli;
    mpz_class GCD;
    while(gmp_scanf("%Zd", &N) != EOF) {
        do_pollard(N);
        cout << endl;
    }
    return 0;
}

/// Estimates if N is prime. It is not guaranteed t be correct. Higher reps mean higher likelihood of being correct.
/// \param N Number to check
/// \param reps Number of times the algorithm checks if N is prime
/// \return 0 if not Prime!
///         1 if maybe Prime!
///         2 if definitely Prime!
int is_prime(mpz_class N, int reps){
    return mpz_probab_prime_p(N.get_mpz_t(), reps);
}


/// This is the g function. If you dont know the g you ain't no g...g
/// \param X
/// \param N
/// \return
mpz_class g(mpz_class X, mpz_class N) {
    mpz_class rop;
    mpz_pow_ui(rop.get_mpz_t(), X.get_mpz_t(), 2);
//    rop += rand() % 2321 + 47;
    rop++;
    mpz_mod(rop.get_mpz_t(), rop.get_mpz_t(), N.get_mpz_t());
    return rop;
}

mpz_class pollard(mpz_class N){
    mpz_class x = 2, x_fixed = 2, size = 2, factor = 1, mathz;
    while(factor == 1) {
        for(size_t c = 1; c <= size && factor <= 1; c++) {
            x = g(x, N);
            mathz = x - x_fixed;
            mpz_gcd(factor.get_mpz_t(), mathz.get_mpz_t(), N.get_mpz_t());
        }
        size *= 2;
        x_fixed = x;
    }
    return factor;
}

void do_pollard(mpz_class N){
    while(true){
        mpz_class polli;
        if(is_prime(N, 50)){
            cout << N << endl;
            break;
        }
        polli = pollard(N);
        cout << polli << endl;
        if(polli == N){
            break;
        }
        N /= polli;
    }
}

void print_factor(double N) {
  printf("%.0lf\n", N);
}
