#include <algorithm>
#include <gmp.h>
#include <gmpxx.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool do_pollard(mpz_class &N, vector<string> &factors);

int main() {
    mpz_class N, prime, remainder;
    int is_prob_prime;
    bool prime_rest;
    vector<string> primes;
    primes.reserve(3000);
    // Pre compute all primes under 3000
    while(mpz_cmp_si(prime.get_mpz_t(), 3000) < 1) {
        mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
        primes.push_back(prime.get_str());
    }
    vector<string> factors;
    while(gmp_scanf("%Zd", &N) != EOF) {
        prime_rest = false;
        is_prob_prime = mpz_probab_prime_p(N.get_mpz_t(), 15);
        // check if N is prime, if so print it out and start on the next number
        if(is_prob_prime){
            cout << N << endl << endl;
            continue;
        }
        // Check if the first 3000 primes are factors in N
        for (unsigned int i=0; i < primes.size(); i++) {
            mpz_set_str(prime.get_mpz_t(), primes[i].c_str(), 10);
            mpz_mod(remainder.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
            // if we find a factor check if it is a repeated factor in N
            if (mpz_cmp_si(remainder.get_mpz_t(), 0) == 0) {
                while(mpz_cmp_si(remainder.get_mpz_t(), 0) == 0) {
                    factors.push_back(prime.get_str());
                    mpz_divexact (N.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
                    mpz_mod(remainder.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
                }
                // If the remainder is prime we break and print out the factors
                is_prob_prime = mpz_probab_prime_p(N.get_mpz_t(), 15);
                if(is_prob_prime){
                    prime_rest = true;
                    break;
                }
            }
            if (prime_rest) {
                break;
            }
        }
        // Run Rollard's rho algorithm to find larger factors
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


// Pollard's rho algorithm implementation
bool do_pollard(mpz_class &N, vector<string> &factors){
    int brent_max=35, counter=0;
    long start=12459026053;
    mpz_class x, y, factor, brent_product = 1;
    while(!mpz_probab_prime_p(N.get_mpz_t(), 15)){
        counter = 0;
        x = y = start;
        factor = 1;
        while (factor == 1) {
            if(++counter >= 555000){ return false; }
            x = ((x*x)+1) % N;
            x = ((x*x)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            // We use Brent's cycle detection method instead of Floyd's. This saves
            // GCD calculations
            brent_product *= (x > y ? x - y : y - x);
            if (counter % brent_max == 0) {
                mpz_gcd(factor.get_mpz_t(), brent_product.get_mpz_t(), N.get_mpz_t());
                brent_product = 1;
            }
            if (N == factor) {
                factor = 1;
                x = y = ++start;
            }
        }
        mpz_divexact(N.get_mpz_t(), N.get_mpz_t(), factor.get_mpz_t());
        // if the factor is a prime number continue running pollard's rho with the remainder
        // else we recursively factor that factor.
        if (mpz_probab_prime_p(factor.get_mpz_t(), 15)) {
            factors.push_back(factor.get_str());
        } else {
            if (!do_pollard(factor, factors)) {
                return false;
            }
        }
    }
    factors.push_back(N.get_str());
    return true;
}
