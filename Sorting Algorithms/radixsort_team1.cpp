#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void custom_sort(std::vector<int>& a) {
    if(a.empty()) return;
    int min_val = a[0];
    for (int i = 1; i < a.size(); i++) if(a[i] < min_val) min_val = a[i];
    long long offset = min_val < 0 ? - (long long)min_val : 0;

    long long max_val = a[0] + offset;
    for (int i = 0; i < a.size(); i++) {
        a[i] += offset;
        if (a[i] > max_val) max_val = a[i];
    }
    for (long long exp = 1; max_val / exp > 0; exp *= 10) countingSort(a, exp);

    if (offset > 0) {
        for (int i = 0; i < a.size(); i++) a[i] -= offset;
    }
}

int main() {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr);            
    int n;                            
    std::cin >> n;                    
    std::vector<int> a(n);            
    for (int& x : a) {                
        std::cin >> x;                
    }                                 
    
    custom_sort(a);                   
    
    assert(std::ranges::is_sorted(a));
    return 0;                         
}