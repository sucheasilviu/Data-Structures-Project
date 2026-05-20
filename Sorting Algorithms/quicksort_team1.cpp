#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


void quicksort_helper(std::vector<int>& a, int low, int high) {
    if (low < high) {
        int pivot = a[high];
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (a[j] < pivot) {
                i++;
                std::swap(a[i], a[j]);
            }
        }
        std::swap(a[i + 1], a[high]);
        int pi = i + 1;
        quicksort_helper(a, low, pi - 1);
        quicksort_helper(a, pi + 1, high);
    }
}
void custom_sort(std::vector<int>& a) {
    if (!a.empty()) quicksort_helper(a, 0, a.size() - 1);
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