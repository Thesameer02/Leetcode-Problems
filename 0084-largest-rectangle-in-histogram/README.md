# 84. Largest Rectangle in Histogram

**Difficulty:** Hard  
**Language:** Java

---

## 🧠 Approach

### Core Idea

The submitted solution solves **Largest Rectangle in Histogram** using Monotonic Stack / Stack. The algorithm evaluates input states and applies stack operations to maintain element ordering and track next/previous boundaries to achieve an optimal solution without unnecessary computations.

It observes the primary constraints of the problem and leverages Monotonic Stack / Stack to maintain efficiency.

### Why This Approach?

Recognizing that **Largest Rectangle in Histogram** requires efficient state processing, the approach leverages Monotonic Stack / Stack properties to eliminate redundant branches and compute results directly rather than using a naive brute-force search.

---

## 💡 How to Think About the Problem

### Step 1: Understand What We Need

Identify the core targets and constraints of **Largest Rectangle in Histogram**.

### Step 2: Identify the Key Observation

Recognize the structural property of the problem that enables an efficient algorithm.

### Step 3: Recognize the Pattern

Apply Monotonic Stack / Stack to optimize the search space.

### Step 4: Decide What Information We Need to Maintain

Track the necessary state variables, arrays, pointers, or data structures.

### Step 5: Derive the Algorithm

Construct the loop iterations and conditional state transitions.

---

## 🔍 Algorithm

1. Receive input data and initialize operational structures.
2. Apply Monotonic Stack / Stack evaluation to process constraints for **Largest Rectangle in Histogram**.
3. Update solution state according to logic rules.
4. Return final computed outcome.

### Important Implementation Details

- `solution state` → Maintains current progress and intermediate results.

---

## 🧩 Understanding the Code

### Core Processing Block

Evaluates input elements sequentially or recursively using Monotonic Stack / Stack.

---

## 🧠 Why This Works

The mathematical and algorithmic properties of Monotonic Stack / Stack guarantee that all valid constraints for **Largest Rectangle in Histogram** are satisfied without missing edge cases.

### Key Invariant

Maintains valid state properties throughout execution.

---

## ⏱️ Time Complexity

**Time:** `O(n²)`

### Why?

Dependent on input length and operations executed during traversal.

---

## 💾 Space Complexity

**Auxiliary Space:** `O(n)`

Allocated data structures or recursion stack memory.

---

## 📌 Key Takeaways

- **Pattern:** Monotonic Stack / Stack
- **Core Observation:** Optimal state evaluation avoids redundant checks.
- **Important Data Structure:** Primary variables / collections used in code.
- **Time:** `O(n²)`
- **Space:** `O(n)`

### Remember

> Carefully analyze state transitions and boundary constraints when solving similar problems.

---

## 🔗 Problem

[LeetCode Problem](https://leetcode.com/problems/largest-rectangle-in-histogram/)
