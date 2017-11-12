#include <algorithm>
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
const int INF = 2147483647;
typedef long long ll;
typedef unsigned long long ull;
template <class T> int size(T &x) { return x.size(); }

void factor(double N);

void print_factor(double N);

double gcd(double X, double Y);

double g(double X, double N);

int main() {
    double N;
    double test = 1200;
    while(scanf("%lf", &N) != EOF) {
      factor(N);
    }
    return 0;
}

void factor(double N) {
  print_factor(N);
}

double gcd(double X, double Y) {
  if (X < 1 || Y < 1)
    return 0;
  if (X == Y)
    return X;
  double remainder;
  while (Y != 0) {
    remainder = fmod(X, Y);
    X = Y;
    Y = remainder;
  }
  return X;
}

double g(double X, double N) {
  return fmod(pow(X,2) + 1, N);
}

void print_factor(double N) {
  printf("%.0lf\n", N);
}