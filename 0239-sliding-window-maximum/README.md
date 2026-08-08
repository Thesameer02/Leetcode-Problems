# 239. Sliding Window Maximum

**Difficulty:** Hard  
**Language:** Java

---

## 🧠 Approach

### Core Idea

The submitted solution solves the Sliding Window Maximum problem by maintaining a **Monotonic Queue** using a double-ended queue (`Deque<Integer>`). Instead of storing the actual values, the deque stores the *indices* of elements from `nums` in a strictly decreasing order of their corresponding values.

As the sliding window shifts from left to right across the array, the deque keeps track of potential candidates for the maximum value. The maximum element for the current window is always available at the front (`head`) of the deque in $O(1)$ time. 

By storing indices instead of values, the algorithm can easily determine if the element at the front of the deque has fallen out of the current window's boundary. When a new element enters the window, any smaller elements currently at the back of the deque are removed because they can never be the maximum for the current or any subsequent window.

The primary DSA pattern utilized here is **Monotonic Deque (Monotonic Stack/Queue variant)** combined with the **Sliding Window** technique.

### Why This Approach?

A naive approach to this problem recomputes the maximum of all $k$ elements for every window shift, which takes $O(k)$ time per step and leads to an overall runtime of $O(N \cdot k)$. This is inefficient because adjacent sliding windows overlap significantly, sharing $k - 1$ elements.

To optimize, we ask: *When does an element in the window become useless?* An element at index $x$ becomes useless as soon as we encounter a newer element at index $y$ ($y > x$) such that `nums[y] >= nums[x]`. Because $y$ is both larger (or equal) and appears later in the array, $x$ can never be the maximum of any window that contains $y$.

This key observation allows us to eliminate smaller, older elements efficiently. Maintaining a monotonically decreasing queue ensures that the largest element in the current window is always at the front, achieving an overall $O(N)$ solution.

---

## 💡 How to Think About the Problem

### Step 1: Understand What We Need

We need to compute the maximum value for every contiguous subarray of size $k$ as a window shifts from index $0$ to $n-1$. For an array of length $N$, there are $N - k + 1$ such windows.

### Step 2: Identify the Key Observation

If an element `nums[i]` is strictly greater than previously seen elements in the window, those smaller elements will never be chosen as the window maximum again—`nums[i]` dominates them in both magnitude and lifespan. Thus, older smaller elements can be discarded immediately.

### Step 3: Recognize the Pattern

Because we need to add elements at the tail end of our structure and inspect/remove elements from both the front (expired elements) and the back (smaller elements), a **Double-Ended Queue (Deque)** maintaining a **monotonically decreasing order** of values is the ideal data structure.

### Step 4: Decide What Information We Need to Maintain

1. **Indices in Deque:** Storing indices rather than values allows us to check whether the element at the front of the queue is still within the active window boundaries (`i - k + 1` to `i`).
2. **Monotonic Order:** Elements in the deque must strictly decrease in value from front to back (`nums[dq.peekFirst()] > nums[...] > nums[dq.peekLast()]`).

### Step 5: Derive the Algorithm

For every index `i` from `0` to `n - 1`:
1. **Evict Expired Index:** If the index at the front of the deque equals `i - k`, it has fallen outside the window. Remove it.
2. **Maintain Monotonicity:** While the deque is non-empty and the value at `nums[i]` is greater than the value corresponding to `dq.peekLast()`, pop from the back.
3. **Push Current Index:** Append index `i` to the back of the deque.
4. **Collect Result:** Once `i >= k - 1` (the first full window is formed), the front of the deque contains the index of the maximum element for the window ending at `i`.

---

## 🔍 Algorithm

1. Initialize an array `res` of size `n - k + 1` to store window maximums and a pointer `j = 0`.
2. Initialize an empty `ArrayDeque<Integer>` named `dq`.
3. Iterate through `i` from `0` to `n - 1`:
   - Check if the front of `dq` contains an index equal to `i - k`. If so, call `dq.poll()` to remove the out-of-bounds index.
   - While `dq` is not empty and `nums[dq.peekLast()] < nums[i]`, call `dq.pollLast()` to discard indices of smaller elements.
   - Add the current index `i` to the back of `dq` using `dq.offer(i)`.
   - If `i >= k - 1`, record the current window's maximum by setting `res[j++] = nums[dq.peekFirst()]`.
4. Return `res`.

### Important Implementation Details

- `dq` → A `Deque<Integer>` storing indices of candidate maximum elements in strictly decreasing order of their array values.
- `dq.peekFirst() == i - k` → Identifies when the index representing the current maximum element has moved outside the active window of size $k$.
- `nums[dq.peekLast()] < nums[i]` → Ensures smaller elements are purged from the back before adding `i`, maintaining the monotonic property.
- `i >= k - 1` → Ensures we only begin writing maximums to `res` once the first complete window of length $k$ has been processed.

---

## 🧩 Understanding the Code

### Phase 1: Evicting Out-of-Bound Indices

```java
if(!dq.isEmpty() && dq.peekFirst() == i - k){
    dq.poll();
}
```
The window spans indices `[i - k + 1, i]`. If the index at the head of the deque is `i - k`, it belongs to the element that just slid out of the window. Removing it ensures the head of the deque always represents an element within the active window.

### Phase 2: Maintaining the Monotonic Decreasing Order

```java
while(!dq.isEmpty() && nums[dq.peekLast()] < nums[i]){
    dq.pollLast();
}
dq.offer(i);
```
Before inserting `i`, we pop elements from the back of `dq` as long as their values are smaller than `nums[i]`. This guarantees that values associated with stored indices decrease from left to right inside `dq`. Afterwards, `i` is pushed to the back.

### Phase 3: Recording Window Maximum

```java
if(i >= k - 1) res[j++] = nums[dq.peekFirst()];
```
Since the deque maintains elements in strictly decreasing order, `dq.peekFirst()` always holds the index of the largest valid element in the current window. Once the loop reaches `k - 1` (end of the first valid window), we record `nums[dq.peekFirst()]` into `res`.

---

## 🧠 Why This Works

The algorithm guarantees correctness by ensuring two main properties at every step `i`:

1. **Validity:** Every index in `dq` belongs to the current window `[i - k + 1, i]`.
2. **Dominance:** Any element smaller than `nums[i]` that appeared before index `i` is purged because `nums[i]` is both larger and will persist longer in subsequent windows.

Because no valid candidate for the maximum is ever prematurely removed, the front of the deque (`dq.peekFirst()`) is guaranteed to point to the maximum element of the active sliding window.

### Key Invariant

At the end of processing index `i`, `dq` contains indices $[idx_1, idx_2, \dots, idx_m]$ such that:
- $i - k + 1 \le idx_1 < idx_2 < \dots < idx_m = i$
- $nums[idx_1] > nums[idx_2] > \dots > nums[idx_m]$

---

## ⏱️ Time Complexity

**Time:** `O(N)`

### Why?

- The main `for` loop executes $N$ times.
- Inside the loop, each index $i$ from $0$ to $N - 1$ is pushed (`offer`) into the deque **exactly once**.
- Consequently, each index can be popped from the deque (`poll` or `pollLast`) **at most once** across the entire execution of the program.
- Although there is a nested `while` loop, its total operations aggregated across all iterations are bounded by $N$. Thus, the amortized time per element is $O(1)$, resulting in an overall $O(N)$ time complexity.

---

## 💾 Space Complexity

**Auxiliary Space:** `O(k)`

The auxiliary space used by the algorithm (excluding the output array `res`) is determined by the size of the deque `dq`. In the worst case (e.g., when array elements are sorted in strictly decreasing order), `dq` holds at most $k$ indices simultaneously. Hence, the auxiliary space complexity is $O(k)$.

---

## 🔄 Alternative Approach

### Alternative Idea

An alternative way to solve this problem is using a **Max-Heap (Priority Queue)** storing pairs of `(value, index)`.

For each index `i`:
1. Add `(nums[i], i)` to the heap.
2. Check the top of the heap. If its index is less than or equal to `i - k`, lazily remove it from the top of the heap.
3. The top of the heap now contains the maximum value in the current window.

This approach is easier to conceptualize but slightly slower due to logarithmic insertion and removal times.

### Complexity

**Time:** `O(N \log N)` (or `O(N \log k)` if optimized)  
**Space:** `O(N)` (or `O(k)` if optimized)

### Comparison

| Aspect | Submitted Approach (Monotonic Deque) | Alternative (Max-Heap / PriorityQueue) |
|---|---|---|
| Main Idea | Maintain candidate indices in monotonic order using Deque | Maintain elements in a Max-Heap with lazy index eviction |
| Time | `O(N)` amortized | `O(N \log k)` or `O(N \log N)` |
| Space | `O(k)` auxiliary | `O(N)` or `O(k)` auxiliary |
| Advantage | Optimal linear time performance | Conceptually straightforward to implement |

---

## 📌 Key Takeaways

- **Pattern:** Monotonic Queue / Monotonic Deque
- **Core Observation:** Smaller elements appearing earlier in the window are useless once a larger element arrives later.
- **Important Data Structure:** `ArrayDeque<Integer>` storing array indices.
- **Time:** `O(N)`
- **Space:** `O(k)` auxiliary space

### Remember

> When tracking sliding window maximums or minimums, maintain a Monotonic Deque of indices: strip outdated indices from the front, pop dominated elements from the back, and read the answer from the front.

---

## 🔗 Problem

[LeetCode Problem](https://leetcode.com/problems/sliding-window-maximum/)
