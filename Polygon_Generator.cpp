#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <limits>
#include <cstdio>

using namespace std;

inline void fast_print(long long x) {
    if (x == 0) {
        putchar('0');
        return;
    }
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    char buf[12];
    int i = 0;
    while (x > 0) {
        buf[i++] = (x % 10) + '0';
        x /= 10;
    }
    while (i--) {
        putchar(buf[i]);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;
    string size = argv[1];
    string type = argv[2];

    int n = (size == "small") ? 20000 : 6000000;
    fast_print(n);
    putchar('\n');

    mt19937 rng(42);
    uniform_int_distribution<int> dist_full(numeric_limits<int>::min(), numeric_limits<int>::max());
    vector<int> a(n);

    if (type == "random") {
        for(int& x : a) x = dist_full(rng);
    }
    else if (type == "sorted") {
        for(int& x : a) x = dist_full(rng);
        sort(a.begin(), a.end());
    }
    else if (type == "reverse") {
        for(int& x : a) x = dist_full(rng);
        sort(a.rbegin(), a.rend());
    }
    else if (type == "few") {
        int pool[5] = {dist_full(rng), dist_full(rng), dist_full(rng), dist_full(rng), dist_full(rng)};
        for(int& x : a) x = pool[rng()%5];
    }
    else if (type == "nearly") {
        for(int& x : a) x = dist_full(rng);
        sort(a.begin(), a.end());
        int swaps = n / 100;
        for(int i=0; i<swaps; i++) {
            int idx1 = rng() % n;
            int idx2 = rng() % n;
            swap(a[idx1], a[idx2]);
        }
    }
    else if (type == "dense") {
        uniform_int_distribution<int> dist_small(0, 1000);
        for(int& x : a) x = dist_small(rng);
    }

    for(int i = 0; i < n; i++) {
        fast_print(a[i]);
        if (i != n - 1) putchar(' ');
    }
    putchar('\n');
    return 0;
}