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
    mpz_class polli;
    mpz_class N, prime, remainder;
    int is_prob_prime;
    bool prime_rest;
    vector<string> primes;
    while(mpz_cmp_si(prime.get_mpz_t(), 700000) < 1) {
        mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
        primes.push_back(prime.get_str());
    }
    vector<string> factors;
    while(gmp_scanf("%Zd", &N) != EOF) {
        prime_rest = false;
        is_prob_prime = mpz_probab_prime_p(N.get_mpz_t(), 15);
        if(is_prob_prime){
            cout << N << endl << endl;
            continue;
        }
        for (unsigned int i=0; i < primes.size(); i++) {
            mpz_set_str(prime.get_mpz_t(), primes[i].c_str(), 10);
            mpz_mod(remainder.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
            if (mpz_cmp_si(remainder.get_mpz_t(), 0) == 0) {
                while(mpz_cmp_si(remainder.get_mpz_t(), 0) == 0) {
                    factors.push_back(prime.get_str());
                    mpz_divexact (N.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
                    mpz_mod(remainder.get_mpz_t(), N.get_mpz_t(), prime.get_mpz_t());
                }
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


bool do_pollard(mpz_class &N, vector<string> &factors){
    srand(time(NULL));
    long counter, bent_counter = 0, start = 12459026053, bent_max = 40;
    mpz_class x, factor, mathz, y, bent_product = 1;
    while(true){
        if(mpz_probab_prime_p(N.get_mpz_t(), 15)){
            factors.push_back(N.get_str());
            break;
        }
        counter = 0;
        x = start, factor = 1, y = start;
        while (factor == 1) {
            x = ((x*x)+1) % N;
            x = ((x*x)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            y = ((y*y)+1) % N;
            bent_product *= (x > y ? x - y : y - x);
            if (counter % bent_max == 0) {
                mpz_gcd(factor.get_mpz_t(), bent_product.get_mpz_t(), N.get_mpz_t());
                bent_counter = 0;
                bent_product = 1;
            }
            if(++counter >= 555000){
                return false;
            }
            if (N == factor) {
                factor = 1;
                ++start;
                x = start;
                y = start;
            }
        }
        mpz_divexact(N.get_mpz_t(), N.get_mpz_t(), factor.get_mpz_t());
        if (mpz_probab_prime_p(factor.get_mpz_t(), 15)) {
            factors.push_back(factor.get_str());
        } else {
            bool res = do_pollard(factor, factors);
            if (!res) {
                return false;
            }
        }
    }
    return true;
}