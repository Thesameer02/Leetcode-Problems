# Largest Rectangle in Histogram
> **LeetCode** • 🔴 Hard • ☕ Java
>
> ⚡ Runtime: 112 ms • 💾 Memory: 77.6 MB • 📅 Solved: 09 Aug 2026
---

## 🧠 AI Explanation

### Approach
Analyzes the problem constraints for **Largest Rectangle in Histogram** using Monotonic Stack / Stack. The algorithm evaluates input states and applies stack operations to maintain element ordering and track next/previous boundaries to achieve an optimal solution without unnecessary computations.

### How to Think About the Problem
Recognizing that **Largest Rectangle in Histogram** requires efficient state processing, the approach leverages Monotonic Stack / Stack properties to eliminate redundant branches and compute results directly.

### Algorithm
1. Receive input data and initialize operational structures.
2. Apply Monotonic Stack / Stack evaluation to check problem constraints for **Largest Rectangle in Histogram**.
3. Update solution state according to logic rules.
4. Return final computed outcome.

### Why This Works
The mathematical and algorithmic properties of Monotonic Stack / Stack guarantee that all valid constraints for **Largest Rectangle in Histogram** are satisfied without missing edge cases.

### Time Complexity
O(n²) — Dependent on input traversal and operations.

### Space Complexity
O(n) — Storage allocation for variables and data structures.

### Alternative Approach
Use a **Brute Force** traversal to check all candidates.

- **Time Complexity:** `O(n²)`
- **Space Complexity:** `O(1)`

---

## 🔗 Problem
https://leetcode.com/problems/largest-rectangle-in-histogram/