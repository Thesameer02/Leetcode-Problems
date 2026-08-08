# 338. Counting Bits

**Difficulty:** Easy  
**Language:** Java

---

## 🧠 Approach

### Core Idea

The submitted solution calculates the number of set bits (1s in binary representation) for every integer from $0$ to $n$. Instead of recalculating the count of set bits for each number from scratch, it reuses the results of previously processed smaller numbers.

The fundamental observation is that shifting a binary number to the right by 1 bit (`i >> 1`) strips away its least significant bit (LSB). This right-shifted value is strictly smaller than $i$, meaning its set-bit count has already been calculated and stored in the `ans` array. The total number of 1s in $i$ is simply the number of 1s in `i >> 1` plus the value of the removed LSB (`i & 1`).

The core DSA pattern used here is **Bit Manipulation** combined with **Array Lookup / Memoization**.

### Why This Approach?

To solve this problem, a naive approach would iterate through each number $i$ from $0$ to $n$ and manually count its set bits using a loop or `Integer.bitCount(i)`. Counting bits for a single number $i$ takes $O(\log i)$ time, leading to an overall time complexity of $O(n \log n)$.

By analyzing how binary representations relate to each other, we can derive a relationship between $i$ and a smaller integer whose bit count is already known. Since `i >> 1` is always strictly less than $i$ for any positive integer, we can look up `ans[i >> 1]` in $O(1)$ time and add `1` if $i$ is odd (`i & 1 == 1`) or `0` if $i$ is even (`i & 1 == 0`). This reduces the total runtime to optimal $O(n)$ time with a single linear pass.

---

## 💡 How to Think About the Problem

### Step 1: Understand What We Need

For a given integer $n$, we must construct an array `ans` of length $n + 1$ where `ans[i]` represents the number of set bits (`1`s) in the binary representation of $i$ for every $0 \le i \le n$.

### Step 2: Identify the Key Observation

Any integer $i$ represented in binary can be split into two parts:
1. All bits except the rightmost bit (obtained via `i >> 1`).
2. The rightmost bit itself (obtained via `i & 1`).

For example, consider $i = 13$ (binary `1101`):
- `13 >> 1` gives $6$ (binary `110`).
- `13 & 1` gives $1$ (the trailing bit).
- Count of 1s in $13$ = (Count of 1s in $6$) + $1$.

Since $6 < 13$, the number of 1s in $6$ is already computed before reaching $13$.

### Step 3: Recognize the Pattern

This problem leverages **Bit Manipulation with Precomputed Lookup**:
- **Bitwise Right Shift (`>>`)**: Removes the last bit and divides the number by 2.
- **Bitwise AND (`&`)**: Extracts the last bit to check parity (even/odd).
- **Array Lookup**: Reuses previously computed answers in $O(1)$ constant time.

### Step 4: Decide What Information We Need to Maintain

We only need a single integer array `ans` of size `n + 1`:
- `ans[i]` stores the number of set bits for integer $i$.
- Base state: `ans[0] = 0` (0 has zero set bits).

### Step 5: Derive the Algorithm

Starting from $i = 1$ up to $n$:
1. Access the precomputed bit count of `i >> 1` from `ans[i >> 1]`.
2. Add `i & 1` (which is `1` if $i$ is odd, `0` if $i$ is even).
3. Store the sum in `ans[i]`.

---

## 🔍 Algorithm

1. Allocate an integer array `ans` of size `n + 1`. In Java, array elements default to `0`, which correctly sets `ans[0] = 0`.
2. Start a loop with variable `i` running from `1` to `n`.
3. Compute `i >> 1` to get the integer representing `i` without its least significant bit.
4. Retrieve `ans[i >> 1]` from the array.
5. Compute `i & 1` to determine if the least significant bit of `i` is `1`.
6. Add the results of steps 4 and 5 together and assign to `ans[i]`.
7. Return the completed `ans` array after the loop terminates.

### Important Implementation Details

- `ans` → The output array of size `n + 1` where index `i` holds the count of set bits for number `i`.
- `i >> 1` → Right shift operation equivalent to $\lfloor i / 2 \rfloor$; retrieves the precomputed prefix.
- `i & 1` → Bitwise mask that yields `1` if `i` is odd and `0` if `i` is even.

---

## 🧩 Understanding the Code

### Array Allocation

```java
int[] ans = new int[n + 1];
```

Creates the output array of size `n + 1` to hold results from index `0` to `n`. `ans[0]` is automatically initialized to `0`, which serves as the base value since $0$ has zero set bits.

### Iterative Bit Shift Recurrence Loop

```java
for (int i = 1; i <= n; i++) {
    ans[i] = ans[i >> 1] + (i & 1);
}
```

Iterates sequentially from $1$ to $n$. For each $i$, it fetches the already computed bit count of `i >> 1` and adds `1` if the current number $i$ is odd (`i & 1 == 1`). This executes in $O(1)$ time per element.

---

## 🧠 Why This Works

The binary representation of any positive integer $i$ can be written as $i = 2 \times \lfloor i / 2 \rfloor + (i \bmod 2)$. 
In terms of binary bits, $2 \times \lfloor i / 2 \rfloor$ represents shifting all bits of $\lfloor i / 2 \rfloor$ one position to the left (adding a trailing `0`). Shifting bits does not alter the total number of set bits present in $\lfloor i / 2 \rfloor$. The remaining term $(i \bmod 2)$ contributes an additional `1` if and only if the original number $i$ was odd.

Since $\lfloor i / 2 \rfloor < i$ for all $i \ge 1$, the bit count for $\lfloor i / 2 \rfloor$ (which is `i >> 1`) is guaranteed to be calculated before evaluating $i$.

### Key Invariant

At the beginning of iteration `i`, every index $j < i$ in `ans` contains the correct number of set bits for integer $j$.

---

## ⏱️ Time Complexity

**Time:** `O(n)`

### Why?

The algorithm runs a single loop from $i = 1$ to $n$. Inside the loop, it performs a constant number of low-level operations:
- Bitwise right shift (`>>`)
- Bitwise AND (`&`)
- Array lookup and addition (`+`)

Each iteration takes $O(1)$ time, yielding an overall time complexity of $O(n)$.

---

## 💾 Space Complexity

**Auxiliary Space:** `O(1)`

The algorithm uses no additional memory beyond the mandatory output array `ans` of size $n + 1$. Since the output array is required by the problem statement, the auxiliary space used by the algorithm is $O(1)$.

---

## 🔄 Alternative Approach

### Alternative Idea

Another standard pattern uses the bitwise operation `i & (i - 1)`. The operation `i & (i - 1)` drops the lowest (rightmost) set bit of $i$. 

Since `i & (i - 1)` clears one set bit and is strictly smaller than $i$, its answer is already calculated in `ans`. Thus, we can compute `ans[i]` as:
`ans[i] = ans[i & (i - 1)] + 1`

### Complexity

**Time:** `O(n)`  
**Space:** `O(1)` auxiliary space

### Comparison

| Aspect | Submitted Approach (`i >> 1`) | Alternative (`i & (i - 1)`) |
|---|---|---|
| Main Idea | Strips the least significant bit (LSB) | Clears the lowest set bit |
| Transition Formula | `ans[i >> 1] + (i & 1)` | `ans[i & (i - 1)] + 1` |
| Operations Per Loop | Right shift, bitwise AND, addition | Bitwise AND, subtraction, addition |
| Time Complexity | `O(n)` | `O(n)` |
| Auxiliary Space | `O(1)` | `O(1)` |
| Readability | Extremely intuitive arithmetic/bit split | Clever bit manipulation trick |

---

## 📌 Key Takeaways

- **Pattern:** Bit Manipulation + Array Lookup
- **Core Observation:** `i >> 1` removes the last bit, reducing $i$ to a smaller number whose set bit count is already known.
- **Important Data Structure:** 1D Array for result storage
- **Time:** `O(n)`
- **Space:** `O(1)` auxiliary space

### Remember

> Shifting a binary number right (`i >> 1`) drops its least significant bit. You can compute the bit count of $i$ in $O(1)$ time by adding `i & 1` to the already known bit count of `i >> 1`.

---

## 🔗 Problem

[LeetCode Problem](https://leetcode.com/problems/counting-bits/)
