#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

const string TEAM_ID = "team1";
const int SMALL_N = 20000;      // For O(n^2) algorithms
const int BIG_N = 10000000;     // For efficient algorithms

void generate_test_case(const string& type, const string& id, int n, vector<int>& data) {
    string base_name = type + "_" + TEAM_ID + "_" + id;
    string in_file = base_name + ".in";
    string ok_file = base_name + ".ok";

    cout << "\nCreating " << base_name << " (N=" << n << ")..." << endl;

    // 1. Write the .in file
    cout << "  -> Opening " << in_file << "..." << flush;
    ofstream fout(in_file);
    if (!fout.is_open()) {
        cout << " FAILED! Check folder permissions." << endl;
        return;
    }
    cout << " OK!" << endl << "  -> Writing data..." << flush;
    fout << n << "\n";
    for (int i = 0; i < n; ++i) {
        fout << data[i] << (i == n - 1 ? "" : " ");
    }
    fout.close();
    cout << " OK!" << endl;

    // 2. Sort to get the expected output
    cout << "  -> Sorting (simulating expected output)..." << flush;
    sort(data.begin(), data.end());
    cout << " OK!" << endl;

    // 3. Write the .ok file
    cout << "  -> Opening " << ok_file << "..." << flush;
    ofstream fok(ok_file);
    if (!fok.is_open()) {
        cout << " FAILED! Check folder permissions." << endl;
        return;
    }
    cout << " OK!" << endl << "  -> Writing sorted data..." << flush;
    for (int i = 0; i < n; ++i) {
        fok << data[i] << (i == n - 1 ? "" : " ");
    }
    fok.close();
    cout << " OK! Done with " << base_name << "." << endl;
}

int main() {
    cout << "PROGRAM STARTED SAFELY." << endl;
    mt19937 rng(42);
    uniform_int_distribution<int> dist_full(numeric_limits<int>::min(), numeric_limits<int>::max());
    vector<int> data;

    cout << "===========================================" << endl;
    cout << "--- GENERATING SMALL TESTS (N = " << SMALL_N << ") ---" << endl;
    cout << "===========================================" << endl;

    // small_01: Random
    data.resize(SMALL_N);
    for (int& x : data) x = dist_full(rng);
    generate_test_case("small", "01", SMALL_N, data);

    // small_02: Already Sorted
    for (int& x : data) x = dist_full(rng);
    sort(data.begin(), data.end());
    generate_test_case("small", "02", SMALL_N, data);

    // small_03: Reverse Sorted
    for (int& x : data) x = dist_full(rng);
    sort(data.rbegin(), data.rend());
    generate_test_case("small", "03", SMALL_N, data);

    // small_04: Few Unique Elements
    int pool[5] = {dist_full(rng), dist_full(rng), dist_full(rng), dist_full(rng), dist_full(rng)};
    for (int& x : data) x = pool[rng() % 5];
    generate_test_case("small", "04", SMALL_N, data);


    cout << "\n===========================================" << endl;
    cout << "--- GENERATING BIG TESTS (N = " << BIG_N << ") ---" << endl;
    cout << "Note: These files are ~100MB each. Please wait..." << endl;
    cout << "===========================================" << endl;

    // big_01: Random
    data.resize(BIG_N);
    for (int& x : data) x = dist_full(rng);
    generate_test_case("big", "01", BIG_N, data);

    // big_02: Reverse Sorted
    for (int& x : data) x = dist_full(rng);
    sort(data.rbegin(), data.rend());
    generate_test_case("big", "02", BIG_N, data);

    // big_03: Nearly Sorted (1% swaps)
    for (int& x : data) x = dist_full(rng);
    sort(data.begin(), data.end());
    int num_swaps = BIG_N / 100;
    for (int i = 0; i < num_swaps; ++i) {
        int idx1 = rng() % BIG_N;
        int idx2 = rng() % BIG_N;
        swap(data[idx1], data[idx2]);
    }
    generate_test_case("big", "03", BIG_N, data);

    // big_04: Dense Integers
    uniform_int_distribution<int> dist_small(0, 1000);
    for (int& x : data) x = dist_small(rng);
    generate_test_case("big", "04", BIG_N, data);

    cout << "\nALL TEST FILES SUCCESSFULLY GENERATED!" << endl;
    return 0;
}