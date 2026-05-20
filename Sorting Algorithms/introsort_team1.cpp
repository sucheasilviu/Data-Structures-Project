#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>

void introsort_util(std::vector<int>& a, int begin, int end, int depthLimit) {
    int size = end - begin;
    if (size < 16) {
        for (int i = begin + 1; i < end; ++i) {
            int key = a[i];
            int j = i - 1;
            while (j >= begin && a[j] > key) { a[j + 1] = a[j]; j--; }
            a[j + 1] = key;
        }
        return;
    }
    if (depthLimit == 0) {
        std::make_heap(a.begin() + begin, a.begin() + end);
        std::sort_heap(a.begin() + begin, a.begin() + end);
        return;
    }
    int pivot = a[end - 1];
    int i = begin - 1;
    for (int j = begin; j < end - 1; j++) {
        if (a[j] <= pivot) { i++; std::swap(a[i], a[j]); }
    }
    std::swap(a[i + 1], a[end - 1]);
    int partitionPoint = i + 1;

    introsort_util(a, begin, partitionPoint, depthLimit - 1);
    introsort_util(a, partitionPoint + 1, end, depthLimit - 1);
}
void custom_sort(std::vector<int>& a) {
    if (a.empty()) return;
    int depthLimit = 2 * std::log2(a.size());
    introsort_util(a, 0, a.size(), depthLimit);
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