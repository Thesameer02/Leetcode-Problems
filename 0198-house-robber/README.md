# House Robber
> **LeetCode** • 🟡 Medium • ☕ Java
>
> ⚡ Runtime: 0 ms • 💾 Memory: 42.7 MB • 📅 Solved: 09 Aug 2026
---

## 🧠 AI Explanation

### Approach
Analyzes the problem constraints for **House Robber** using Dynamic Programming. The algorithm evaluates input states and applies state transitions and overlapping subproblem memoization to achieve an optimal solution without unnecessary computations.

### How to Think About the Problem
Recognizing that **House Robber** requires efficient state processing, the approach leverages Dynamic Programming properties to eliminate redundant branches and compute results directly.

### Algorithm
1. Receive input data and initialize operational structures.
2. Apply Dynamic Programming evaluation to check problem constraints for **House Robber**.
3. Update solution state according to logic rules.
4. Return final computed outcome.

### Why This Works
The mathematical and algorithmic properties of Dynamic Programming guarantee that all valid constraints for **House Robber** are satisfied without missing edge cases.

### Time Complexity
O(n) — Dependent on input traversal and operations.

### Space Complexity
O(1) — Storage allocation for variables and data structures.

### Alternative Approach
Use a **Brute Force** traversal to check all candidates.

- **Time Complexity:** `O(n²)`
- **Space Complexity:** `O(1)`

---

## 🔗 Problem
https://leetcode.com/problems/house-robber/