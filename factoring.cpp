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

double g(double X, double N);

int main() {
    mpz_class N;
    mpz_class GCD;
    int is_prob_prime = 0;

    while(gmp_scanf("%Zd", &N) != EOF) {
        is_prob_prime = is_prime(N, 50);
        if(is_prob_prime == 2 || is_prob_prime == 1){
            cout << N << endl << endl;
        } else {
            mpz_gcd(GCD.get_mpz_t(), N.get_mpz_t(), N.get_mpz_t());
            cout << "fail" << endl << endl;
        }
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


double g(double X, double N) {
  return fmod(pow(X,2) + 1, N);
}

void print_factor(double N) {
  printf("%.0lf\n", N);
}
