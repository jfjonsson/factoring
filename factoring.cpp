#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Pollard's rho algorithm implementation
bool do_pollard(mpz_class &N, vector<string> &factors, size_t start){
    int brent_max=35, counter=0;
    mpz_class x, y, factor, brent_product = 1;
    while(!mpz_probab_prime_p(N.get_mpz_t(), 15)){
        counter = 0;
        x = y = start;
        factor = 1;
//        while (factor == 1) {
        while (factor == 1) {
            if(++counter >= 750000){ return false; }
            x = (x * x + 1) % N;
            x = (x * x + 1) % N;
            y = (y * y + 1) % N;
            y = (y * y + 1) % N;
            y = (y * y + 1) % N;
            y = (y * y + 1) % N;
            brent_product *= x - y;
            // We use Brent-Pollard cycle detection to save us from doing multiple GCD calculations
            if (counter % brent_max == 0) {
                mpz_gcd(factor.get_mpz_t(), brent_product.get_mpz_t(), N.get_mpz_t());
                brent_product = 1;
            }
            if (N == factor) {
                factor = 1;
            }
        }
        N /= factor;
        // If the factor is a prime number continue running Pollard's rho with the remainder
        // else we recursively factor that factor.
        if (mpz_probab_prime_p(factor.get_mpz_t(), 15)) {
            factors.push_back(factor.get_str());
        } else {
            if (!do_pollard(factor, factors, start)) {
                return false;
            }
        }
    }
    factors.push_back(N.get_str());
    return true;
}

int main() {
    size_t i, prime_threshold = 3000, start=12459026053;
    mpz_class N, prime;
    vector<string> primes(430);  // number of primes from 0 to 3000
    // Pre compute all primes under 3000
    while(prime < prime_threshold){
        mpz_nextprime(prime.get_mpz_t(), prime.get_mpz_t());
        primes.push_back(prime.get_str());
    }
    vector<string> factors;
    while(gmp_scanf("%Zd", &N) != EOF) {
        // If N is prime print it and move on to the next N
        if(mpz_probab_prime_p(N.get_mpz_t(), 15)){
            cout << N << endl << endl;
            continue;
        }
        // Check if the primes below 3000 are factors in N
        for (i=0; i < primes.size(); ++i) {
            mpz_set_str(prime.get_mpz_t(), primes[i].c_str(), 10);
            if(N % prime == 0){
                if(!mpz_probab_prime_p(N.get_mpz_t(), 15)){
                    // if we find a factor check if it is a repeated factor in N
                    factors.push_back(prime.get_str());
                    N /= prime;
                    --i;
                }
            }
            // If the remainder is prime we break and print out the factors
            if(mpz_probab_prime_p(N.get_mpz_t(), 15)){
                break;
            }
        }
        // Run Pollard's rho algorithm to find larger factors
        if(do_pollard(N, factors, start)){
            for (auto i = factors.begin(); i != factors.end(); ++i) {
                cout << *i << endl;
            }
        } else {
            cout << "fail" << endl;
        }
        factors.clear();
        cout << endl;
    }
}