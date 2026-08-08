# Two Sum
> **LeetCode** • 🟢 Easy • 📝 C++
>
> ⚡ Runtime: 2 ms • 💾 Memory: 14.8 MB • 📅 Solved: 08 Aug 2026
---

## 🧠 AI Explanation

### Approach
Uses a `HashMap` to store previously visited numbers while iterating through the input collection once. For each element, it checks whether its complement or required condition already exists in the map. If found, the results are returned immediately, resulting in a linear-time solution.

### Time Complexity
**O(n)**

### Space Complexity
**O(n)**

### Alternative Approach
Sort the array and apply the **Two Pointer** technique.

- **Time Complexity:** `O(n log n)`
- **Space Complexity:** `O(1) *(excluding the cost of preserving original indices)*`

---

## 🔗 Problem
https://leetcode.com/problems/two-sum/