# Empirical Sorting Analysis (MergeSort vs QuickSort vs Bubble Sort)

A C++ console project that **implements 3 sorting algorithms** and performs an **empirical performance analysis** by measuring:

- **Execution time (seconds)** using `std::chrono`
- **Estimated “operation counts”** (comparisons + copies/swaps/partition steps) via manual counters
- **Correctness** by comparing results with `std::sort` as a reference

It also exports results to **CSV (`results.csv`)** for plotting in Python/Excel/gnuplot.

---

## Algorithms Implemented

### 1) MergeSort (Divide et Impera)
- Recursively splits the array into halves and merges sorted halves.
- Complexity: **O(n log n)** worst/average
- Counter tracks:
  - comparisons in merge
  - copy operations into the main array
  - recursion/base-case overhead

### 2) QuickSort (partition-based)
- Uses a pivot (middle element) and partitions into:
  - `leftArr` (< pivot), `middle` (= pivot), `rightArr` (> pivot)
- Complexity: **O(n log n)** average, **O(n²)** worst case (rare with random data)
- Counter tracks:
  - comparisons against pivot
  - partition operations
  - reconstruction writes
  - recursive calls

### 3) Bubble Sort (reference / baseline)
- Simple quadratic algorithm included for comparison.
- Complexity: **O(n²)**
- Includes early-stop optimization (`swapped` flag).
- Counter tracks:
  - comparisons
  - swaps
  - outer loop iterations + break condition

---

## Features

✅ Interactive menu  
✅ Random test vector generation  
✅ Correctness check against `std::sort`  
✅ Performance analysis for multiple sizes  
✅ CSV export: `results.csv`  

---

## Project Structure (simple)

You can keep everything in one file:

- `main.cpp` (contains algorithms + menu + analysis + CSV export)
- output: `results.csv`

---

## How to Build & Run

### Compile (g++)
```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o sorting_analysis
How to Use (Menu)

When you run the program, you get:

Test on a specific size

You enter n

Program generates a random vector

Runs all 3 algorithms

Prints:

time (seconds)

operations count

correctness (“DA/NU”)

Full performance analysis

Automatically tests sizes:

10, 50, 100, 500, 1000, 5000

Prints comparative timing table

Saves all results to results.csv

Exit

Output Example (Console)

For a single test size, it prints a table like:

Algoritm	Timp (s)	Operații	Corect
Mergesort	0.000123	12345	DA
Quicksort	0.000081	11002	DA
Bubble Sort	0.012340	250000	DA

(Values depend on machine + random input.)

CSV Export

After performance analysis, the program generates:

results.csv

Columns:

Size

Mergesort_Time, Quicksort_Time, Bubble_Time

Mergesort_Ops, Quicksort_Ops, Bubble_Ops

This is ready for plotting (Python/Excel/gnuplot).


[Lab 2.docx](https://github.com/user-attachments/files/25639847/Lab.2.docx)


