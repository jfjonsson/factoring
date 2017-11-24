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

int is_prime(mpz_class &N, int reps);

//mpz_class g(mpz_class &X, mpz_class &N);
bool do_pollard(mpz_class &N, vector<string> &factors);
mpz_class pollard(mpz_class &N);

int main() {
    mpz_class polli;
    mpz_class N, prime, root, remainder;
    int is_prob_prime;
    bool prime_rest;
    vector<string> primes;
    while(mpz_cmp_si(prime.get_mpz_t(), 100) < 1) {
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
        if(do_pollard(N, factors)){
            for (auto i = factors.begin(); i != factors.end(); ++i) {
                cout << *i << endl;
            }
        } else {
            cout << "fail" << endl;
        }
        factors.clear();
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
int is_prime(mpz_class &N, int reps){
    return mpz_probab_prime_p(N.get_mpz_t(), reps);
}


/// Having this in a function makes the code much slower
/// \param X
/// \param N
/// \return
//mpz_class g(mpz_class &X, mpz_class &N) {
//    mpz_class rop;
//    mpz_pow_ui(rop.get_mpz_t(), X.get_mpz_t(), 2);
//    mpz_add_ui(rop.get_mpz_t(), rop.get_mpz_t(), 1);
//    mpz_mod(rop.get_mpz_t(), rop.get_mpz_t(), N.get_mpz_t());
//    return rop;
//}

//mpz_class pollard(mpz_class &N){
//    mpz_class x = 2, x_fixed = 2, size = 2, factor = 1, mathz;
//    int counter = 0;
//    while(factor == 1) {
////        for(size_t c = 1; c <= size && factor <= 1; c++) {
//        for(size_t c = 1; c <= size && factor <= 1; c++) {
//            mpz_pow_ui(x.get_mpz_t(), x.get_mpz_t(), 2);
//            mpz_add_ui(x.get_mpz_t(), x.get_mpz_t(), 1);
//            mpz_mod(x.get_mpz_t(), x.get_mpz_t(), N.get_mpz_t());
//            mathz = x - x_fixed;
//            mpz_gcd(factor.get_mpz_t(), mathz.get_mpz_t(), N.get_mpz_t());
//            if(++counter >= 1000000){
//                return -1;
//            }
//        }
//        size *= 2;
//        x_fixed = x;
//    }
//    return factor;
//}

bool do_pollard(mpz_class &N, vector<string> &factors){
    int counter;
    mpz_class x, size, factor, mathz, y;
    while(true){
        if(mpz_probab_prime_p(N.get_mpz_t(), 15)){
            factors.push_back(N.get_str());
            break;
        }
        counter = 0;
        x = 2, size = 2, factor = 1, y = 2;
        for(;factor == 1; size*=2) {
            for(size_t c = 1; c <= size && factor <= 1; ++c) {
                x = ((x*x)+1) % N;
                y = ((y*y)+1) % N;
                y = ((y*y)+1) % N;
                mathz = (x - y) % N;
                mpz_gcd(factor.get_mpz_t(), mathz.get_mpz_t(), N.get_mpz_t());
                if(++counter >= 700000){
                    return false;
                }
            }
        }
        if(factor == -1){
            return false;
        }
        factors.push_back(factor.get_str());
        mpz_divexact(N.get_mpz_t(), N.get_mpz_t(), factor.get_mpz_t());
    }
    return true;
}