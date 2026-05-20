#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


void custom_sort(std::vector<int>& a) {
    for (int i = 1; i < a.size(); ++i) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j = j - 1;
        }
        a[j + 1] = key;
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