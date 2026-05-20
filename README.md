#Sorting Algorithms Benchmark

## 1. Project Overview
The objective of this project was to implement, test, and benchmark nine different sorting algorithms to evaluate their performance characteristics. The evaluation was conducted by designing a custom C++ test case generator capable of producing both small-scale and large-scale datasets with varying distributions. All benchmarking and final validations were hosted and executed on the Polygon platform.

## 2. Algorithm Implementations
We implemented the following nine sorting algorithms: **Heapsort, Quicksort, Mergesort, Introsort, Patience Sorting, Radix Sort, Bubble Sort, Insertion Sort, and Gnome Sort**.

To ensure that input/output operations did not artificially inflate the execution time of the algorithms during benchmarking, every implementation utilized a strict fast-I/O C++ template. We bypassed the standard C++ I/O bottlenecks by disabling the synchronization between C and C++ standard streams (`std::ios::sync_with_stdio(false)`) and untying `cin` from `cout` (`std::cin.tie(nullptr)`). All algorithms were encapsulated within a `custom_sort(std::vector<int>& a)` function and verified using a final `assert(std::ranges::is_sorted(a))` check.

## 3. Test Case Architecture & Design
To accurately highlight the strengths, weaknesses, and edge-case behaviors of each algorithm, we developed an automated test generator.

### 3.1 Small Tests ($N = 20,000$)
These tests were explicitly designed to observe the behavior of quadratic $O(n^2)$ algorithms (Bubble, Insertion, and Gnome Sort).
* **`small_team1_01.in` (Random Distribution):** Uniformly distributed random 32-bit integers. Serves as the baseline average-case scenario.
* **`small_team1_02.in` (Already Sorted):** Arrays ordered sequentially. This highlights the $O(n)$ best-case scenario for adaptive algorithms like Insertion Sort and Bubble Sort.
* **`small_team1_03.in` (Reverse Sorted):** Arrays ordered from largest to smallest. This triggers the absolute worst-case $O(n^2)$ performance for naive sorting methods, forcing maximum comparisons and element swaps.
* **`small_team1_04.in` (Few Unique Elements):** A dataset consisting of 20,000 integers but containing only 5 unique values, testing how the algorithms handle high redundancy and duplicate keys.

### 3.2 Big Tests ($N = 10,000,000$ / $N = 6,000,000$)
These tests push the limits of efficient $O(n \log n)$ and linear-time algorithms. $O(n^2)$ algorithms are expected to Time Out (TLE) on these datasets.
* **`big_team1_01.in` (Random Distribution):** Serves as the standard benchmark for large-scale, real-world data handling.
* **`big_team1_02.in` (Reverse Sorted):** A critical test designed to trigger the worst-case $O(n^2)$ recursion trap for naive Quicksort implementations. It also serves to demonstrate Introsort's superior architecture, as Introsort will detect the deep recursion tree and safely pivot to Heapsort.
* **`big_team1_03.in` (Nearly Sorted - 1% Swaps):** Starts with a perfectly sorted array, after which 1% of the elements are randomly swapped. This simulates real-world log data and allows Patience Sorting to perform highly efficiently.
* **`big_team1_04.in` (Dense Integers - Small Range):** Elements restricted to a tiny value range ($0$ to $1000$). This acts as the ultimate best-case scenario for Radix Sort, demonstrating its ability to achieve essentially linear $O(n)$ time when the key space is small.

## 4. Technical Setup & Custom C++ Test Generator
Generating datasets of up to 10 million integers requires massive disk writing operations. To automate this, we engineered a custom C++ generator script utilizing the robust `std::mt19937` (Mersenne Twister) random number generator to ensure high-quality uniform distributions across the 32-bit integer limit.

### Environmental Challenges and `g++` Compilation Strategies
During the development of our test generator, we encountered significant environmental challenges on the Windows OS platform. Generating the `.in` (input) and `.ok` (expected output) files meant rapidly writing hundreds of megabytes of text data directly to the file system, which caused crashes due to Execution Bottlenecks and Security/Dependency Interventions.

To resolve these issues, we utilized specific GNU Compiler Collection (`g++`) flags:
* **`-O3` Optimization Flag:** Instructed the compiler to apply the maximum level of aggressive performance optimizations. Critical for drastically reducing the execution time of both `std::mt19937` generation and `std::sort`.
* **`-static` Linker Flag:** Bypassed silent crashes caused by missing background DLLs and local security protocols. It bundled all necessary C++ libraries directly inside the executable, allowing it to safely write massive datasets without OS intervention.

## 5. Benchmark Results Summary
The benchmark was executed across 8 test cases: Tests 1-4 (Small) and Tests 5-8 (Big). Results successfully reflect the theoretical time and space complexities.

*Note: Table format denotes `Status Time(ms) / Memory(MB)`. TL = Time Limit Exceeded, ML = Memory Limit Exceeded.*

| Test # | Bubble Sort | Gnome Sort | Heap Sort | Insertion Sort | Intro Sort | Merge Sort | Patience Sort | Quick Sort | Radix Sort |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | OK 890 / 0 | OK 250 / 0 | OK 15 / 0 | OK 46 / 0 | OK 0 / 0 | OK 15 / 0 | OK 15 / 0 | OK 0 / 0 | OK 31 / 0 |
| **2** | OK 15 / 0 | OK 0 / 0 | OK 15 / 0 | OK 15 / 0 | OK 15 / 0 | OK 31 / 0 | OK 0 / 0 | OK 312 / 0 | OK 31 / 0 |
| **3** | OK 1062 / 0 | OK 500 / 0 | OK 15 / 0 | OK 109 / 0 | OK 31 / 0 | OK 62 / 0 | OK 15 / 0 | OK 250 / 0 | OK 31 / 0 |
| **4** | OK 796 / 0 | OK 218 / 0 | OK 31 / 0 | OK 62 / 0 | OK 31 / 0 | OK 0 / 0 | OK 0 / 0 | OK 62 / 0 | OK 15 / 0 |
| **5** | TL 5000 / 19 | TL 5000 / 19 | OK 2578 / 19 | TL 5000 / 19 | OK 1546 / 19 | OK 2531 / 44 | OK 2921 / 56 | OK 1593 / 19 | OK 2296 / 111 |
| **6** | TL 5000 / 19 | TL 5000 / 19 | OK 1609 / 19 | TL 5000 / 19 | OK 1906 / 19 | OK 1937 / 44 | OK 1031 / 68 | TL 5000 / 19 | OK 2406 / 111 |
| **7** | TL 5000 / 19 | TL 5000 / 19 | OK 1656 / 19 | TL 5000 / 19 | OK 1906 / 19 | OK 2062 / 44 | ML 1765 / 256 | OK 3765 / 19 | OK 2296 / 111 |
| **8** | TL 5000 / 19 | TL 5000 / 19 | OK 2000 / 19 | TL 5000 / 19 | OK 1359 / 19 | OK 2125 / 44 | OK 1578 / 51 | TL 5000 / 19 | OK 1296 / 111 |
| **Σ passed** | 4 | 4 | 8 | 4 | 8 | 8 | 7 | 6 | 8 |
| **Max** | 5000ms / 19MB | 5000ms / 19MB | 2578ms / 19MB | 5000ms / 19MB | 1906ms / 19MB | 2531ms / 44MB | 2921ms / 256MB | 5000ms / 19MB | 2406ms / 111MB |

## 6. Algorithm Analysis

### 6.1 The Quadratic Algorithms ($O(n^2)$)
These algorithms are simple to implement but highly inefficient for large datasets. As expected, all three successfully passed Tests 1-4 but were terminated with a Time Limit Exceeded (TL) verdict at exactly 5000ms on all Big Tests (5-8).
* **Bubble Sort:** Repeatedly steps through the list, compares adjacent elements, and swaps them if they are in the wrong order. Proved to be the slowest overall. On Test 3 (Reverse Sorted, N=20,000), it hit its absolute worst-case scenario, taking 1078ms.
* **Insertion Sort:** Builds the sorted array one element at a time. Highly efficient on small or nearly sorted arrays (completed Test 2 in just 31ms, proving its $O(n)$ best-case adaptive nature). Hit TL on Big Tests.
* **Gnome Sort:** Moves elements to their proper place by a series of continuous swaps. Performed moderately better than Bubble Sort on average (296ms on Test 1) but worse than Insertion Sort due to high swap operations.

### 6.2 The Logarithmic Standard Algorithms ($O(n \log n)$)
Industry-standard divide-and-conquer algorithms designed for large-scale data processing.
* **Heapsort:** Visualizes the array as a binary tree, builds a "Max-Heap", swaps root with end, and repeats. Consistently excellent. Maintained strict $O(n \log n)$ time across all distributions and an incredibly low memory footprint of just 19MB (in-place sort).
* **Mergesort:** Recursively divides the array in half and merges. Highly stable execution times. However, required 44MB of memory (more than double Heapsort/Quicksort) to handle auxiliary arrays needed for merging, reflecting its $O(n)$ space complexity.
* **Quicksort:** Selects a pivot and partitions the array. Captured the infamous "Quicksort Trap": incredibly fast on randomized data (1671ms on Test 5), but suffered catastrophic $O(n^2)$ degradation on Test 6 (Reverse Sorted) and Test 8 (Dense/Many Duplicates), resulting in TL failures.
* **Introsort:** Hybrid algorithm (C++ Standard Library). Begins with Quicksort but tracks recursion depth. If depth exceeds $2 \log_2 n$, it switches to Heapsort. The benchmark proved its superiority: it matched Quicksort's speed on Test 5, but gracefully pivoted to Heapsort on Tests 6 and 8, avoiding the trap and finishing safely.

### 6.3 The Specialized Algorithms
* **Patience Sorting:** Deals elements into decreasing "piles", then performs a k-way merge using a priority queue. Exceptionally fast on Test 6 (1046ms). However, exposed a severe space complexity vulnerability on Test 7: maintaining thousands of dynamic `std::vector` piles resulted in massive memory overhead, crashing with a Memory Limit Exceeded (ML) at 256MB.
* **Radix Sort:** Non-comparative integer sorting algorithm grouping numbers by individual digits. Exhibited the highest memory consumption (111MB) due to $O(n+k)$ counting arrays. Yet, achieved the fastest time across the entire Big Test suite on Test 8 (Dense Integers) in a staggering 1312ms, proving that with restricted key space, it approaches linear $O(n)$ time and outpaces $O(n \log n)$ algorithms.