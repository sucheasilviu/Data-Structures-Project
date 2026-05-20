#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>

void custom_sort(std::vector<int>& a) {
    if(a.empty()) return;
    std::vector<std::vector<int>> piles;
    for (int x : a) {
        auto it = std::lower_bound(piles.begin(), piles.end(), x, [](const std::vector<int>& p, int val) {
            return p.back() < val;
        });
        if (it == piles.end()) piles.push_back({x});
        else it->push_back(x);
    }

    auto comp = [&piles](const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return piles[p1.first][p1.second] > piles[p2.first][p2.second];
    };
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)> pq(comp);

    for (int i = 0; i < piles.size(); ++i) pq.push({i, 0});

    int index = 0;
    while (!pq.empty()) {
        auto [pile_idx, elem_idx] = pq.top();
        pq.pop();
        a[index++] = piles[pile_idx][elem_idx];
        if (elem_idx + 1 < piles[pile_idx].size()) {
            pq.push({pile_idx, elem_idx + 1});
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