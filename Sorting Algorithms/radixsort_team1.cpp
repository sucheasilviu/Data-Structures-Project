#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

void custom_sort(std::vector<int>& a) {
    if(a.empty()) return;
    
    std::vector<long long> arr(a.begin(), a.end());
    
    long long min_val = arr[0];
    for (long long x : arr) if (x < min_val) min_val = x;
    long long offset = min_val < 0 ? -min_val : 0;
    
    long long max_val = arr[0] + offset;
    for (int i = 0; i < arr.size(); i++) {
        arr[i] += offset;
        if (arr[i] > max_val) max_val = arr[i];
    }
    
    for (long long exp = 1; max_val / exp > 0; exp *= 10) {
        int n = arr.size();
        std::vector<long long> output(n);
        int count[10] = {0};
        
        for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        for (int i = 0; i < n; i++) arr[i] = output[i];
    }
    for (int i = 0; i < arr.size(); i++) a[i] = arr[i] - offset;
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