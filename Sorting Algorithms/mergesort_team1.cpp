#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


void merge(std::vector<int>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = a[left + i];
    for (int j = 0; j < n2; j++) R[j] = a[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while (i < n1) a[k++] = L[i++];
    while (j < n2) a[k++] = R[j++];
}
void mergesort_helper(std::vector<int>& a, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort_helper(a, left, mid);
        mergesort_helper(a, mid + 1, right);
        merge(a, left, mid, right);
    }
}
void custom_sort(std::vector<int>& a) {
    if (!a.empty()) mergesort_helper(a, 0, a.size() - 1);
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