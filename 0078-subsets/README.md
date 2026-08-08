# 78. Subsets

**Difficulty:** Medium  
**Language:** Java

---

## 🧠 Approach

### Core Idea

The submitted solution uses **Backtracking** (a form of Depth-First Search) to systematically construct all possible subsets (the power set) of the input array `nums`.

At every recursive step, the current path stored in `temp` represents a valid, unique subset. The algorithm captures this state immediately by making a shallow copy of `temp` and adding it to the `result` list.

To explore further choices, the algorithm loops through all remaining available candidate elements starting from index `start`. For each chosen candidate `nums[i]`, it appends the element to `temp`, makes a recursive call with the updated starting index `i + 1`, and then undoes the choice by removing the last element from `temp`. This "choose, recurse, un-choose" cycle ensures that all decision branches are fully explored without duplicating subsets.

### Why This Approach?

When given an array of $N$ unique elements, generating all subsets requires constructing $2^N$ combinations. A straightforward way to think about this is a decision tree where each candidate element can either be included in or excluded from a given subset.

Without a structured strategy, we risk generating duplicate subsets or missing valid combinations. By maintaining a `start` index parameter, we enforce that elements are added to `temp` in strictly increasing order of their indices in `nums`. This prevents generating equivalent permutations (such as `[1, 2]` and `[2, 1]`) as distinct subsets. Furthermore, reusing a single `temp` list across calls minimizes memory allocations compared to creating new sublists at every decision node.

---

## 💡 How to Think About the Problem

### Step 1: Understand What We Need

We need to generate all possible subsets of an array `nums` containing distinct integers. The final output must be a collection of lists, where each inner list represents one distinct subset (including the empty subset and the subset containing all elements).

### Step 2: Identify the Key Observation

Every element in `nums` has two states: it is either included in the subset or excluded. If we build subsets element-by-element from left to right, every prefix of choices corresponds to a valid subset. By guaranteeing that an element at index `i` can only be followed by elements at indices strictly greater than `i`, we ensure every subset is generated exactly once.

### Step 3: Recognize the Pattern

This problem fits the **Backtracking** pattern. 

- **State:** The elements accumulated so far (`temp`) and the current search boundary (`start`).
- **Choices:** Any element from index `start` to `nums.length - 1`.
- **Backtracking Action:** Add element $\rightarrow$ Recurse $\rightarrow$ Remove element.

### Step 4: Decide What Information We Need to Maintain

- `start`: An integer parameter tracking the first element index available for picking in the current recursive depth.
- `temp`: A dynamic list acting as a call stack to hold the elements of the subset currently being constructed.
- `result`: A master list storing snapshot copies of all generated subsets.

### Step 5: Derive the Algorithm

1. Start at `start = 0` with an empty `temp` list.
2. Record `temp` as a valid subset in `result`.
3. Iterate `i` from `start` to `nums.length - 1`:
   - Include `nums[i]` in `temp`.
   - Recursively call the solver for `i + 1`.
   - Remove `nums[i]` from `temp` to revert the state back before moving to the next candidate `i + 1`.

---

## 🔍 Algorithm

1. Initialize `result` as an empty list of lists.
2. Call `backtrack(nums, 0, new ArrayList<>(), result)`.
3. Inside `backtrack`:
   1. Create a copy of the current state `temp` using `new ArrayList<>(temp)` and append it to `result`.
   2. Loop through the array starting from `i = start` up to `nums.length - 1`.
   3. Append `nums[i]` to `temp`.
   4. Recurse by calling `backtrack(nums, i + 1, temp, result)`.
   5. Pop/remove the last element from `temp` (backtrack step).
4. Return `result`.

### Important Implementation Details

- `start` → Guarantees elements are picked in increasing index order, preventing duplicate subset permutations.
- `temp` → Single dynamic list modified in-place to save memory during recursive traversals.
- `new ArrayList<>(temp)` → Creates a snapshot of `temp` at the current decision point so future modifications to `temp` do not corrupt previously recorded subsets.

---

## 🧩 Understanding the Code

### Phase 1: Entry Point (`subsets`)

```java
public List<List<Integer>> subsets(int[] nums) {
    List<List<Integer>> result = new ArrayList<>();
    backtrack(nums, 0, new ArrayList<>(), result);
    return result;
}
```

Initializes the output container `result` and triggers the initial backtracking call starting at index `0` with an empty list `new ArrayList<>()`.

### Phase 2: Recording Current State

```java
result.add(new ArrayList<>(temp));
```

Because every node in the recursion tree represents a valid subset, the current contents of `temp` are immediately copied and added to `result`. This captures the empty set on the first call and incomplete/complete subsets on subsequent calls.

### Phase 3: Recursive Exploration and Backtracking Loop

```java
for (int i = start; i < nums.length; i++) {
    temp.add(nums[i]);
    backtrack(nums, i + 1, temp, result);
    temp.remove(temp.size() - 1);
}
```

Iterates over all valid choices starting from index `start`. It pushes `nums[i]` into `temp`, recurses to process elements beyond index `i`, and finally pops `nums[i]` from `temp` to restore the state before testing the next element in the loop.

---

## 🧠 Why This Works

The state-space tree formed by this recursion contains exactly $2^N$ nodes, where $N$ is the number of elements in `nums`. By exploring this state-space tree using Depth-First Search and capturing `temp` at every node, the algorithm visits and records every possible subset. Passing `i + 1` to subsequent calls ensures that elements are never revisited or picked out of order, guaranteeing uniqueness and completeness.

### Key Invariant

At any point in the execution of `backtrack(nums, start, temp, result)`, `temp` contains a unique sequence of elements whose indices in `nums` are strictly increasing and all strictly less than `start`.

---

## ⏱️ Time Complexity

**Time:** `O(N · 2^N)`

### Why?

- An array of size $N$ has $2^N$ total subsets, corresponding to $2^N$ recursive function calls (nodes in the state-space tree).
- At each node, creating a deep copy of `temp` via `new ArrayList<>(temp)` takes $O(k)$ time, where $k$ is the current length of `temp`.
- On average, the length of a subset is $N / 2$. Summing across all $2^N$ calls gives $O(N \cdot 2^N)$ total operations.

---

## 💾 Space Complexity

**Auxiliary Space:** `O(N)`

- The stack depth of the recursion reaches at most $N$ frames deep.
- The working list `temp` stores at most $N$ elements at any given time.
- Note: The returned `result` list contains $2^N$ subsets storing $N \cdot 2^{N-1}$ total elements, requiring $O(N \cdot 2^N)$ space. However, excluding the required output output structure, the auxiliary space consumed by recursion and local variables is $O(N)$.

---

## 🔄 Alternative Approach

### Alternative Idea

Instead of recursion, we can use **Bitmasking** (Iterative Approach).

Since each element can either be present (`1`) or absent (`0`), any integer from `0` to $2^N - 1$ corresponds to a unique subset. We can iterate through all integers from `0` to $(1 \ll N) - 1$, treat each integer as a bitmask, and include `nums[j]` in the current subset if the $j$-th bit of the mask is set.

### Complexity

**Time:** `O(N · 2^N)`  
**Space:** `O(1)` auxiliary space (excluding the output list)

### Comparison

| Aspect | Submitted Approach (Backtracking) | Alternative (Bitmasking) |
|---|---|---|
| Main Idea | Recursive DFS traversing state-space tree | Iterating through integers $0 \dots 2^N-1$ as bit flags |
| Time | `O(N · 2^N)` | `O(N · 2^N)` |
| Space | `O(N)` auxiliary (call stack + `temp`) | `O(1)` auxiliary |
| Advantage | Intuitive structure; easily adaptable to subset constraints (e.g., duplicate handling, targeted sum) | Non-recursive, simple bitwise logic |

---

## 📌 Key Takeaways

- **Pattern:** Backtracking / State-Space Tree Search
- **Core Observation:** Every step in the decision tree represents a valid subset, so the current path state must be recorded at every node.
- **Important Data Structure:** Dynamic ArrayList (used as a Backtracking Stack)
- **Time:** `O(N · 2^N)`
- **Space:** `O(N)` auxiliary

### Remember

> When generating combinatorial subsets using backtracking, pass an updated index (`i + 1`) to eliminate duplicate combinations, and always create explicit snapshot copies (`new ArrayList<>(temp)`) when saving mutable path states.

---

## 🔗 Problem

[LeetCode Problem](https://leetcode.com/problems/subsets/)
