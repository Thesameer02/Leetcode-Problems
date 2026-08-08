# 189. Rotate Array

**Difficulty:** Medium  
**Language:** C++

---

## 🧠 Approach

### Core Idea

The submitted solution solves the array rotation problem using the classic **Three Reversals** technique. Rotating an array to the right by $k$ steps means taking the last $k$ elements and placing them at the beginning, while shifting the remaining $n - k$ elements to the right.

Instead of performing expensive element shifts or allocating extra memory, this approach uses array reversals in three distinct steps:
1. Reverse the entire array. This moves the last $k$ elements to the front, but in reverse order, and shifts the first $n - k$ elements to the back, also in reverse order.
2. Reverse the first $k$ elements to restore their original relative order.
3. Reverse the remaining $n - k$ elements to restore their original relative order.

This approach uses **Two Pointers** in a helper function to perform in-place swaps, achieving the optimal $O(n)$ time complexity and $O(1)$ auxiliary space complexity.

### Why This Approach?

When thinking about array rotation, the most direct solution is to shift elements one position at a time $k$ times ($O(n \cdot k)$ time), or to create a secondary array to copy elements to their target indices `(i + k) % n` ($O(n)$ time, $O(n)$ space). However, the problem often asks for an in-place solution with $O(1)$ extra space and linear time.

To achieve $O(1)$ space, we need an operation that rearranges elements in bulk without losing data. Reversing a subarray is an in-place operation taking $O(\text{subarray length})$ time. Recognizing that rotation splits the array into two segments—the prefix of size $n - k$ and the suffix of size $k$—and swaps their positions allows us to derive the three-reversal strategy:

$$[A, B] \xrightarrow{\text{reverse all}} [B^R, A^R] \xrightarrow{\text{reverse } B^R} [B, A^R] \xrightarrow{\text{reverse } A^R} [B, A]$$

Where $A$ is the first $n - k$ elements and $B$ is the last $k$ elements.

---

## 💡 How to Think About the Problem

### Step 1: Understand What We Need

We need to shift every element in an array of size $n$ to the right by $k$ positions. Elements that fall off the right end wrap around to the beginning. The transformation must modify the input vector `nums` in place.

### Step 2: Identify the Key Observation

If $k \ge n$, shifting by $k$ steps is identical to shifting by $k \pmod n$ steps because rotating an array by its full length $n$ results in the original array. 

Furthermore, rotating right by $k$ divides the array into two parts:
- Segment 1: elements from index $0$ to $n - k - 1$ (length $n - k$)
- Segment 2: elements from index $n - k$ to $n - 1$ (length $k$)

After rotation, Segment 2 must precede Segment 1.

### Step 3: Recognize the Pattern

This problem fits the **Two Pointers (In-Place Array Manipulation)** pattern. Reversing a subarray between indices $i$ and $j$ can be done by maintaining two pointers at $i$ and $j$, swapping their contents, and moving them toward each other until they meet.

### Step 4: Decide What Information We Need to Maintain

- `n`: The length of the array (`nums.size()`).
- `k`: Normalized shift amount calculated as `k % n`.
- Two pointers `i` and `j` inside the `reverse` helper function to track the boundaries of the subarray being reversed.

### Step 5: Derive the Algorithm

1. Compute $k = k \pmod n$ to handle cases where $k \ge n$.
2. Call `reverse(0, n - 1, nums)` to flip the entire array.
3. Call `reverse(0, k - 1, nums)` to correct the ordering of the newly placed prefix.
4. Call `reverse(k, n - 1, nums)` to correct the ordering of the suffix.

---

## 🔍 Algorithm

1. Retrieve the size of the array $n$ using `nums.size()`.
2. Normalize $k$ by taking `k % n` to avoid unnecessary redundant rotations.
3. Call `reverse(0, n - 1, nums)` to reverse the whole array from index $0$ to $n - 1$.
4. Call `reverse(0, k - 1, nums)` to reverse the first $k$ elements.
5. Call `reverse(k, n - 1, nums)` to reverse the remaining $n - k$ elements starting from index $k$ to $n - 1$.
6. In the helper function `reverse(i, j, nums)`:
   - While `i <= j`, swap `nums[i]` and `nums[j]`.
   - Increment `i` and decrement `j`.

### Important Implementation Details

- `k = k % n` → Ensures $k$ falls within the valid range $[0, n-1]$. If $n = 0$ or $k$ is a multiple of $n$, this prevents out-of-bounds access.
- `reverse(0, k - 1, nums)` → Reverses the subarray of size $k$ at indices $0$ through $k - 1$.
- `reverse(k, n - 1, nums)` → Reverses the remaining elements from index $k$ to $n - 1$.
- `while(i <= j)` → Two-pointer condition that continues swapping elements until the pointers cross at the center.

---

## 🧩 Understanding the Code

### Reversing Helper Function (`reverse`)

```cpp
void reverse(int i, int j, vector<int>& nums) {
    while (i <= j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        i++;
        j--;
    }
}
```

This helper function reverses a segment of the vector in-place. Pointer `i` starts at the beginning of the target range, and `j` starts at the end. In each iteration, elements at `i` and `j` are swapped using a temporary variable `temp`, after which `i` moves right and `j` moves left until the entire range is inverted.

### Modulo Normalization and Full Array Reversal

```cpp
int n = nums.size();
k = k % n;
reverse(0, n - 1, nums);
```

First, `k = k % n` handles inputs where $k \ge n$. Then, reversing the complete vector (`0` to `n - 1`) places the last $k$ elements at indices $0 \dots k - 1$ and the first $n - k$ elements at indices $k \dots n - 1$. However, both segments are now in inverted order.

### Restoring Subarray Order

```cpp
reverse(0, k - 1, nums);
reverse(k, n - 1, nums);
```

The second call reverses the range $[0, k - 1]$, turning the inverted last $k$ elements back into their original order. The third call reverses $[k, n - 1]$, turning the inverted first $n - k$ elements back into their original order. Together, these steps complete the right rotation in-place.

---

## 🧠 Why This Works

### Key Invariant

Reversing a sequence twice restores its original relative order. Let the array be split into $A = \text{nums}[0 \dots n - k - 1]$ and $B = \text{nums}[n - k \dots n - 1]$. 

- Original array: $[A, B]$
- Step 1 (Reverse entire array): $[A, B]^R = [B^R, A^R]$
- Step 2 (Reverse first $k$ elements): $[(B^R)^R, A^R] = [B, A^R]$
- Step 3 (Reverse remaining $n - k$ elements): $[B, (A^R)^R] = [B, A]$

Since $[B, A]$ is the exact definition of array $A$ rotated right by $k$ positions, the algorithm is guaranteed to be correct.

---

## ⏱️ Time Complexity

**Time:** `O(n)`

### Why?

- The `reverse` function performs $\lfloor \frac{\text{length}}{2} \rfloor$ swaps.
- Step 1 reverses $n$ elements: takes $\frac{n}{2}$ swaps.
- Step 2 reverses $k$ elements: takes $\frac{k}{2}$ swaps.
- Step 3 reverses $n - k$ elements: takes $\frac{n - k}{2}$ swaps.
- Total swaps = $\frac{n}{2} + \frac{k}{2} + \frac{n - k}{2} = n$ swaps.

Each swap takes $O(1)$ time, making the total overall time complexity strictly linear, $O(n)$.

---

## 💾 Space Complexity

**Auxiliary Space:** `O(1)`

The algorithm operates entirely in-place on the input `vector<int>& nums`. It only allocates a few primitive integer variables (`n`, `k`, `i`, `j`, `temp`), consuming $O(1)$ extra space.

---

## 🔄 Alternative Approach

### Alternative Idea

Another common $O(1)$ space approach is **Cyclic Replacements**. We move each element directly to its target position `(current_index + k) % n`. Since moving an element overwrites the value at the target position, we store the target value in a temporary variable before overwriting it and continue chain-placing elements. To handle cases where $n$ and $k$ share common factors (which causes cyclic loops), we keep a count of total elements moved ($n$) and start a new cycle whenever we return to the starting index of the current cycle.

### Complexity

**Time:** `O(n)`  
**Space:** `O(1)`

### Comparison

| Aspect | Submitted Approach (3 Reversals) | Alternative (Cyclic Replacements) |
|---|---|---|
| Main Idea | Reverse whole array, then reverse both halves | Move each element directly to its final destination in cycles |
| Time | `O(n)` | `O(n)` |
| Space | `O(1)` | `O(1)` |
| Advantage | Simpler to implement and less prone to edge-case bugs | Writes each element to its final location exactly once |

---

## 📌 Key Takeaways

- **Pattern:** Two Pointers / Array Reversal
- **Core Observation:** Rotating right by $k$ is equivalent to swapping two array blocks $[A, B] \to [B, A]$, which can be done by reversing all elements, then reversing each block individually.
- **Important Data Structure:** None required beyond two pointers for in-place swapping.
- **Time:** `O(n)`
- **Space:** `O(1)`

### Remember

> Reversing an array globally, then reversing subarrays locally, transforms block order $[A, B]$ to $[B, A]$ in linear time and $O(1)$ extra space.

---

## 🔗 Problem

[LeetCode Problem](https://leetcode.com/problems/rotate-array/)
