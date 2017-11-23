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
    mpz_class polli;
    mpz_class N, prime, root, remainder;
    int is_prob_prime;
    bool prime_rest;
    vector<string> primes;
    while(mpz_cmp_si(prime.get_mpz_t(), 50) < 1) {
        mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
        primes.push_back(prime.get_str());
    }
    while(gmp_scanf("%Zd", &N) != EOF) {
        vector<string> factors;
        prime_rest = false;
        is_prob_prime = is_prime(N, 15);
        if(is_prob_prime){
            cout << N << endl << endl;
            continue;
        }
        mpz_set_si(prime.get_mpz_t(), 2);
        mpz_root(root.get_mpz_t(), N.get_mpz_t(), 2);
        for (unsigned int i=0; i < primes.size(); i++) {
            mpz_set_str(prime.get_mpz_t(), primes[i].c_str(), 10);
            mpz_mod(remainder.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
            if (mpz_cmp_si(remainder.get_mpz_t(), 0) == 0) {
                while(mpz_cmp_si(remainder.get_mpz_t(), 0) == 0) {
                    factors.push_back(prime.get_str());
                    mpz_divexact (N.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
                    mpz_mod(remainder.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
                }
                is_prob_prime = is_prime(N, 15);
                if(is_prob_prime){
                    prime_rest = true;
                    break;
                }
            }
            if (prime_rest) {
                break;
            }
            mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
        }
        for (auto i = factors.begin(); i != factors.end(); ++i) {
            cout << *i << endl;
        }
        factors.clear();
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
    rop += rand() % 2321 + 47;
//    rop++;
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
    int counter = 0;
    while(true){
        if(++counter == 100000){
            throw;
        }
        mpz_class factor;
        if(is_prime(N, 50)){
            cout << N << endl;
            break;
        }
        factor = pollard(N);
        cout << factor << endl;
        N /= factor;
    }
}

void print_factor(double N) {
  printf("%.0lf\n", N);
}
