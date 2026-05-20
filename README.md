# Sorting Algorithms Benchmark

## 1. Project Overview
The objective of this project was to implement, test, and benchmark nine different sorting algorithms to evaluate their performance characteristics. The evaluation was conducted by designing a custom C++ test case generator capable of producing both small-scale and large-scale datasets with varying distributions. All benchmarking and final validations were hosted and executed on the Polygon platform.

## 2. Algorithm Implementations
We implemented the following nine sorting algorithms: **Heapsort, Quicksort, Mergesort, Introsort, Patience Sorting, Radix Sort, Bubble Sort, Insertion Sort, and Gnome Sort**.

To ensure that input/output operations did not artificially inflate the execution time of the algorithms during benchmarking, every implementation utilized a strict fast-I/O C++ template. We bypassed the standard C++ I/O bottlenecks by disabling the synchronization between C and C++ standard streams (`std::ios::sync_with_stdio(false)`) and untying `cin` from `cout` (`std::cin.tie(nullptr)`).

All algorithms were encapsulated within a `custom_sort(std::vector<int>& a)` function and verified using a final `assert(std::ranges::is_sorted(a))` check.

## 3. Test Case Architecture & Design
To accurately highlight the strengths, weaknesses, and edge-case behaviors of each algorithm, we developed an automated test generator.

### 3.1 Small Tests ($N = 20,000$)
These tests were explicitly designed to observe the behavior of quadratic $O(n^2)$ algorithms (Bubble, Insertion, and Gnome Sort).
* **`small_team1_01.in` (Random Distribution):** Uniformly distributed random 32-bit integers. Serves as the baseline average-case scenario.
* **`small_team1_02.in` (Already Sorted):** Arrays ordered sequentially. This highlights the $O(n)$ best-case scenario for adaptive algorithms like Insertion Sort and Bubble Sort.
* **`small_team1_03.in` (Reverse Sorted):** Arrays ordered from largest to smallest. This triggers the absolute worst-case $O(n^2)$ performance for naive sorting methods, forcing maximum comparisons and element swaps.
* **`small_team1_04.in` (Few Unique Elements):** A dataset consisting of 20,000 integers but containing only 5 unique values, testing how the algorithms handle high redundancy and duplicate keys.

### 3.2 Big Tests ($N = 10,000,000$)
These tests push the limits of efficient $O(n \log n)$ and linear-time algorithms (Heapsort, Quicksort, Mergesort, Introsort, Patience, and Radix Sort). $O(n^2)$ algorithms are expected to Time Out (TLE) on these datasets.
* **`big_team1_01.in` (Random Distribution):** Serves as the standard benchmark for large-scale, real-world data handling.
* **`big_team1_02.in` (Reverse Sorted):** A critical test designed to trigger the worst-case $O(n^2)$ recursion trap for naive Quicksort implementations. It also serves to demonstrate Introsort's superior architecture, as Introsort will detect the deep recursion tree and safely pivot to Heapsort.
* **`big_team1_03.in` (Nearly Sorted - 1% Swaps):** Starts with a perfectly sorted array, after which 1% of the elements are randomly swapped. This simulates real-world log data and allows Patience Sorting to perform highly efficiently.
* **`big_team1_04.in` (Dense Integers - Small Range):** 10 million elements restricted to a tiny value range (0 to 1000). This acts as the ultimate best-case scenario for Radix Sort, demonstrating its ability to achieve essentially linear $O(n)$ time when the key space is small.

## 4. Benchmark Results

Below is the execution result matrix hosted on the Polygon platform for each algorithm across the various test cases. *Times are in milliseconds (ms), and memory is in megabytes (MB).*

| # | Bubble Sort | Gnome Sort | Heap Sort | Insertion Sort | Intro Sort | Merge Sort | Patience Sort | Quick Sort | Radix Sort |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **1** | OK 890 / 0 | OK 250 / 0 | OK 15 / 0 | OK 46 / 0 | OK 0 / 0 | OK 15 / 0 | OK 15 / 0 | OK 0 / 0 | OK 31 / 0 |
| **2** | OK 15 / 0 | OK 0 / 0 | OK 15 / 0 | OK 15 / 0 | OK 15 / 0 | OK 31 / 0 | OK 0 / 0 | OK 312 / 0 | OK 31 / 0 |
| **3** | OK 1062 / 0 | OK 500 / 0 | OK 15 / 0 | OK 109 / 0 | OK 31 / 0 | OK 62 / 0 | OK 15 / 0 | OK 250 / 0 | OK 31 / 0 |
| **4** | OK 796 / 0 | OK 218 / 0 | OK 31 / 0 | OK 62 / 0 | OK 31 / 0 | OK 0 / 0 | OK 0 / 0 | OK 62 / 0 | OK 15 / 0 |
| **5** | TL 5000 / 19 | TL 5000 / 19 | OK 2578 / 19 | TL 5000 / 19 | OK 1546 / 19 | OK 2531 / 44 | OK 2921 / 56 | OK 1593 / 19 | OK 2296 / 111 |
| **6** | TL 5000 / 19 | TL 5000 / 19 | OK 1609 / 19 | TL 5000 / 19 | OK 1906 / 19 | OK 1937 / 44 | OK 1031 / 68 | TL 5000 / 19 | OK 2406 / 111 |
| **7** | TL 5000 / 19 | TL 5000 / 19 | OK 1656 / 19 | TL 5000 / 19 | OK 1906 / 19 | OK 2062 / 44 | ML 1765 / 256 | OK 3765 / 19 | OK 2296 / 111 |
| **8** | TL 5000 / 19 | TL 5000 / 19 | OK 2000 / 19 | TL 5000 / 19 | OK 1359 / 19 | OK 2125 / 44 | OK 1578 / 51 | TL 5000 / 19 | OK 1296 / 111 |
| **$\Sigma$ Passed**| **4** | **4** | **8** | **4** | **8** | **8** | **7** | **6** | **8** |
| **Max** | 5000ms / 19MB | 5000ms / 19MB | 2578ms / 19MB | 5000ms / 19MB | 1906ms / 19MB | 2531ms / 44MB | 2921ms / 256MB | 5000ms / 19MB | 2406ms / 111MB |

*(Key: OK = Passed, TL = Time Limit Exceeded, ML = Memory Limit Exceeded)*

## 5. Technical Setup & Custom C++ Test Generator
Generating datasets of up to 10 million integers requires massive disk writing operations. To automate this, we engineered a custom C++ generator script utilizing the robust `std::mt19937` (Mersenne Twister) random number generator to ensure high-quality uniform distributions across the 32-bit integer limit.

### 5.1 Environmental Challenges and `g++` Compilation Strategies
During the development of our test generator, we encountered significant environmental challenges on the Windows OS platform. Generating the `.in` (input) and `.ok` (expected output) files for the "Big Tests" meant rapidly writing hundreds of megabytes of text data directly to the file system.

This behavior caused the program to crash due to two primary factors:
1.  **Execution Bottlenecks:** Standard compilation was too slow to generate, sort, and write $10,000,000$ integers efficiently.
2.  **Security & Dependency Interventions:** Rapid, massive file I/O from an unrecognized executable often triggers silent terminations by Windows Defender, or fails due to missing dynamic-link libraries (DLLs) in the local MinGW/MSYS2 environment.

To resolve these issues and successfully build the test suite, we utilized specific GNU Compiler Collection (`g++`) flags:
* **The `-O3` Optimization Flag:** We compiled our generator using `g++ -O3`. This instructed the compiler to apply the maximum level of aggressive performance optimizations. This was absolutely critical to drastically reduce the execution time of both the `std::mt19937` random generation and the `std::sort` function on arrays of 10 million elements.
* **The `-static` Linker Flag:** To bypass the silent crashes caused by missing background DLLs and local security protocols, we compiled using `g++ -static`. This forced the compiler to bundle all necessary standard C++ libraries and I/O handlers directly inside the executable itself. This made the program entirely self-contained, allowing it to safely and successfully write the massive 100MB dataset files to the hard drive without OS intervention.

## 6. Conclusion
Through careful implementation of the required algorithms and rigorous test engineering using optimized C++ generation techniques, this benchmark successfully maps out the empirical time complexities of various sorting paradigms. All code and generated test cases have been packaged and uploaded to Polygon for final automated benchmarking.
README.md
Displaying README.md.