#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>


void custom_sort(std::vector<int>& a) {
    int index = 0;
    int n = a.size();
    while (index < n) {
        if (index == 0) index++;
        if (a[index] >= a[index - 1]) index++;
        else {
            std::swap(a[index], a[index - 1]);
            index--;
        }
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