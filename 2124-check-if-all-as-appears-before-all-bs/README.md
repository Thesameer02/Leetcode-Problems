# 2124. Check if All A's Appears Before All B's

**Difficulty:** Easy  
**Language:** Java

---

## 🧠 Approach

### Core Idea

The submitted solution determines whether all occurrences of the character `'a'` appear before every occurrence of the character `'b'` in the given string `s`.

The algorithm works in two sequential phases. First, it iterates through the string to find the index of the very first occurrence of `'b'`. It stores this index in the variable `ans`. If no `'b'` is present in the string, `ans` remains initialized to `s.length()`.

Second, starting from index `ans`, the algorithm scans the rest of the string. If it encounters any `'a'` at or after the first `'b'`, it immediately returns `false` because an `'a'` has appeared after a `'b'`. If the loop finishes without encountering any `'a'`, it returns `true`.

The main DSA pattern used here is a **Linear Scan / Array Traversal** approach.

### Why This Approach?

To check if all `'a'`s appear before all `'b'`s, we need to verify that no `'a'` exists after any `'b'`. 

The key observation is that if an `'a'` appears after *any* `'b'`, it will definitely appear after the *first* `'b'`. Therefore, finding the index of the first `'b'` creates a boundary: every character at or after this boundary must be a `'b'` (or at least cannot be an `'a'`).

A naive brute-force approach might check every pair of indices $(i, j)$ with $i < j$ to see if `s[i] == 'b'` and `s[j] == 'a'`, which would take $O(N^2)$ time. By identifying the boundary of the first `'b'`, the submitted approach simplifies the check to two linear scans, running in $O(N)$ time.

---

## 💡 How to Think About the Problem

### Step 1: Understand What We Need

We need to verify whether a given string `s` containing only characters `'a'` and `'b'` follows the pattern $a^*b^*$ (zero or more `'a'`s followed by zero or more `'b'`s).

### Step 2: Identify the Key Observation

If the string is valid, once we encounter the first `'b'`, no `'a'` is allowed to appear after it. The first `'b'` acts as a dividing line for the entire string.

### Step 3: Recognize the Pattern

This problem falls under the **Linear Scan** pattern. We are scanning a sequence to locate a specific threshold condition (the first `'b'`) and then validating that all subsequent elements meet our criteria (no `'a'`s).

### Step 4: Decide What Information We Need to Maintain

We need:
1. A variable `ans` to track the index of the first occurrence of `'b'`.
2. A default value for `ans` set to `s.length()` to handle the case where the string contains no `'b'` characters.

### Step 5: Derive the Algorithm

1. Convert string `s` into a character array `chars`.
2. Find the first index `i` where `chars[i] == 'b'`. Store this in `ans` and break.
3. Iterate from index `ans` to the end of the array.
4. If `chars[i] == 'a'`, return `false`.
5. If the loop ends without finding an `'a'`, return `true`.

---

## 🔍 Algorithm

1. Convert the input string `s` into a character array `chars`.
2. Initialize an integer `ans` with `s.length()`.
3. Loop through `chars` from index `0` to `s.length() - 1`. If `chars[i] == 'b'`, set `ans = i` and `break`.
4. Loop through `chars` from index `ans` to `s.length() - 1`. If `chars[i] == 'a'`, return `false`.
5. Return `true` if the second loop completes without returning `false`.

### Important Implementation Details

- `ans` → Stores the index of the first occurrence of `'b'`. Initialized to `s.length()` so the second loop is skipped if `'b'` does not exist.
- `chars` → Array representation of the input string for fast character access.
- `chars[i] == 'b'` → The condition used to identify the boundary index and break early from the first loop.
- `chars[i] == 'a'` → The violation condition in the second loop indicating an `'a'` appears after a `'b'`.

---

## 🧩 Understanding the Code

### Phase 1: Finding the First Occurrence of 'b'

```java
char[] chars = s.toCharArray();
int ans = s.length();
for(int i = 0; i<s.length();i++){
    if(chars[i] == 'b'){
        ans = i;
        break;
    }
}
```

This block converts the string to a character array and searches for the first `'b'`. The `break` statement ensures we stop immediately at the first occurrence, giving us the earliest boundary index. If no `'b'` exists, `ans` remains `s.length()`.

### Phase 2: Verifying the Remainder of the String

```java
for(int i = ans;i<s.length();i++){
    if(chars[i] == 'a'){
        return false;
    }
}
return true;
```

This block iterates from index `ans` to the end of the string. If `ans` was set to `s.length()`, this loop will not execute at all and the method will immediately return `true` (which is correct, as a string with no `'b'`s satisfies the condition). If a `'b'` was found, any `'a'` seen at or after index `ans` invalidates the condition, triggering an early `return false`.

---

## 🧠 Why This Works

### Key Invariant

The algorithm maintains the invariant that prior to index `ans`, all characters inspected are `'a'`. After index `ans`, every character must be `'b'`. By establishing `ans` as the position of the first `'b'`, any `'a'` found at or after `ans` represents an out-of-order character, rendering the string invalid.

---

## ⏱️ Time Complexity

**Time:** `O(N)`

### Why?

- Converting the string `s` to a character array takes $O(N)$ time, where $N$ is the length of `s`.
- The first `for` loop runs at most $N$ times.
- The second `for` loop runs from `ans` to $N$, which is at most $N$ operations.
- Summing these up gives $O(N) + O(N) = O(N)$ time complexity.

---

## 💾 Space Complexity

**Auxiliary Space:** `O(N)`

### Why?

- `s.toCharArray()` creates a new `char[]` of size $N$, which consumes $O(N)$ extra memory.
- Using primitive variables like `ans` and `i` uses $O(1)$ space.
- Overall auxiliary space used by the submitted implementation is $O(N)$.

---

## 🔄 Alternative Approach

### Alternative Idea

Instead of using two passes and creating a character array, we can observe that the string is invalid **if and only if** the substring `"ba"` exists anywhere in `s`. If `'b'` appears before `'a'`, there must be at least one point in the string where a `'b'` is immediately followed by an `'a'`.

Using Java's built-in string method `s.contains("ba")`, we can solve the entire problem in a single line without allocating additional character arrays.

### Complexity

**Time:** `O(N)`  
**Space:** `O(1)`

### Comparison

| Aspect | Submitted Approach | Alternative (`!s.contains("ba")`) |
|---|---|---|
| Main Idea | Two-pass scan finding first `'b'` index | Substring search for invalid sequence `"ba"` |
| Time | `O(N)` | `O(N)` |
| Space | `O(N)` (allocates `char[]`) | `O(1)` auxiliary space |
| Advantage | Explicit control and easy to step through in debuggers | Extremely concise, clean, and avoids $O(N)$ memory allocation |

---

## 📌 Key Takeaways

- **Pattern:** Linear Scan / Boundary Search
- **Core Observation:** All `'a'`s precede all `'b'`s if and only if no `'a'` appears after the first `'b'` (or equivalently, `"ba"` never appears).
- **Important Data Structure:** None required (Primitive types).
- **Time:** `O(N)`
- **Space:** `O(N)` (can be optimized to `O(1)` by using `s.charAt()` or `!s.contains("ba")`).

### Remember

> A non-decreasing order requirement on binary alphabets (like 'a' and 'b') is violated if and only if the inverted pattern `"ba"` exists in the sequence.

---

## 🔗 Problem

[LeetCode Problem](https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/)
