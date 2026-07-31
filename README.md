*This project has been created as part of the 42 curriculum by alesferr and ahideo-k.*

# Push_swap

An optimized, modular, and robust implementation of the **Push_swap** project from the 42 curriculum, developed in C. The project features a core sorting algorithm supporting multiple strategies, a bonus verification program (**checker**), detailed benchmarking metrics, and dynamic disorder calculation of the input stack.

---

## 👥 Authors and Contributions

This project was developed in pairs as required by the 42 curriculum:

* **Student 1 (`login1`):** Circular stack data structure architecture, argument parsing routines, disorder metric calculation (`disorder_bp`), rank indexing (`to_ranks`), and implementation of the complex strategy ($O(N \log N)$ Bitwise Radix Sort).
* **Student 2 (`login2`):** Execution engine for stack operations (`ops.c`), implementation of simple ($O(N^2)$) and medium ($O(N \sqrt{N})$ Chunk-Based) sorting strategies, development of the bonus `checker` program, and benchmarking/reporting system (`--bench`).

---

## 📋 Project Overview

The objective of **Push_swap** is to sort a given set of integer values on Stack **A** in ascending order, using an auxiliary Stack **B** and a restricted set of stack manipulation operations, producing the **shortest sequence of instructions possible**.

### Key Features
* **Disorder Metric:** Precise measurement of the initial stack disorder percentage (based on the proportion of inverted pairs/inversions) before executing any moves.
* **Automatic Adaptive Selection (`--adaptive`):** Dynamically chooses the optimal sorting strategy based on the initial disorder level.
* **4 Embedded Sorting Strategies:** `SIMPLE` ($O(N^2)$), `MEDIUM` ($O(N \sqrt{N})$), `COMPLEX` ($O(N \log N)$), and `ADAPTIVE`.
* **Benchmark Mode (`--bench`):** Outputs detailed execution metrics to `stderr`, including disorder rate, strategy applied, theoretical complexity class, total operations, and individual operation counts.
* **Checker Program (Bonus):** Validates whether a sequence of instructions read from `stdin` correctly sorts Stack **A** while leaving Stack **B** empty.

---

## 🛠️ Supported Operations

| Operation | Name | Description |
| :--- | :--- | :--- |
| **`sa`** | Swap A | Swaps the top two elements of Stack A. |
| **`sb`** | Swap B | Swaps the top two elements of Stack B. |
| **`ss`** | Swap Both | Executes `sa` and `sb` simultaneously. |
| **`pa`** | Push A | Moves the top element from Stack B to the top of Stack A. |
| **`pb`** | Push B | Moves the top element from Stack A to the top of Stack B. |
| **`ra`** | Rotate A | Shifts up all elements of Stack A by 1 (the top element becomes the bottom). |
| **`rb`** | Rotate B | Shifts up all elements of Stack B by 1 (the top element becomes the bottom). |
| **`rr`** | Rotate Both | Executes `ra` and `rb` simultaneously. |
| **`rra`** | Reverse Rotate A | Shifts down all elements of Stack A by 1 (the bottom element becomes the top). |
| **`rrb`** | Reverse Rotate B | Shifts down all elements of Stack B by 1 (the bottom element becomes the top). |
| **`rrr`** | Reverse Rotate Both | Executes `rra` and `rrb` simultaneously. |

---

## 📐 Disorder Metric & Strategy Selection

### Disorder Metric
The disorder metric $D \in [0, 1]$ calculates the ratio between the number of out-of-order pairs (inversions) and the maximum possible number of pairs in the initial stack:

$$D = \frac{\text{mistakes}}{\text{total\_pairs}} = \frac{\sum_{i=0}^{N-1} \sum_{j=i+1}^{N-1} \mathbb{I}(A[i] > A[j])}{\frac{N(N-1)}{2}}$$

### Implemented Algorithms & Complexity Justification

1. **Simple Strategy — Selection / Min Extraction ($O(N^2)$):**
   * **Mechanism:** Iteratively finds the smallest element in Stack A, rotates it to the top via the shortest path, and pushes it to Stack B. Once Stack A is empty, all elements are pushed back to Stack A.
   * **Complexity Bounds:** Time $O(N^2)$ Push_swap operations; $O(1)$ auxiliary space.

2. **Medium Strategy — Chunk-Based Sorting ($O(N \sqrt{N})$):**
   * **Mechanism:** Divides rank-indexed values into chunks of size $C \approx \sqrt{N}$. Elements are pushed to Stack B in ranges and organized. Finally, elements are pushed back to Stack A in descending order.
   * **Complexity Bounds:** Time $O(N \sqrt{N})$ Push_swap operations; $O(N)$ auxiliary space.

3. **Complex Strategy — Bitwise Radix Sort ($O(N \log N)$):**
   * **Mechanism:** Using pre-processed normalized ranks (`to_ranks`) in the range $[0, N-1]$, the algorithm processes integers bit-by-bit (Least Significant Bit first). For each bit position, elements with bit `0` are pushed to Stack B while elements with bit `1` are rotated in Stack A. The process repeats for $\lceil \log_2(N) \rceil$ bits.
   * **Complexity Bounds:** Time $O(N \log N)$ Push_swap operations; $O(N)$ auxiliary space.

4. **Adaptive Strategy Thresholds (`--adaptive`):**
   * **Low Disorder ($D < 0.20$ / $< 20\%$):** Runs the `SIMPLE` method ($O(N^2)$), exploiting the low inversion count to complete sorting with minimal overhead.
   * **Medium Disorder ($0.20 \le D < 0.50$ / $20\% \le D < 50\%$):** Runs the `MEDIUM` method ($O(N \sqrt{N})$), optimizing partition shifts across chunks.
   * **High Disorder ($D \ge 0.50$ / $\ge 50\%$):** Runs the `COMPLEX` method ($O(N \log N)$), guaranteeing deterministic bounds even under worst-case inputs.

---

## ⚙️ Compilation & Usage

### Prerequisites
* C Compiler (`cc` or `gcc`)
* `make` utility

### Compilation Commands

Build the main `push_swap` binary:
```bash
make
```

Build the bonus `checker` binary:
```bash
make bonus
```

Clean object files (`.o`) and binaries:
```bash
make clean
make fclean
make re
```

---

## 🚀 Execution Examples

### Default Execution (Adaptive Mode)
```bash
./push_swap 4 67 3 87 23
```

### Forcing a Specific Strategy
```bash
./push_swap --simple 5 4 3 2 1
./push_swap --medium 4 67 3 87 23
./push_swap --complex 8 3 1 5 2 4 7 6
```

### Benchmark Mode (`--bench`)
The benchmark summary is printed to `stderr`, leaving the instruction stream clean on `stdout`:

```bash
./push_swap --bench --adaptive 4 67 3 87 23
```

**Sample Output (`stderr`):**
```text
[bench] disorder:  40.00%
[bench] strategy:  Adaptive / O(n*sqrt(n))
[bench] total_ops: 13
[bench] sa: 0 sb: 0 ss: 0 pa: 5 pb: 5
[bench] ra: 2 rb: 1 rr: 0 rra: 0 rrb: 0 rrr: 0
```

### Verifying with `checker` (Bonus)
```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
# Expected Output: OK
```

### Random Testing & Operation Counting
```bash
ARG=$(shuf -i 0-9999 -n 100 | tr '
' ' '); ./push_swap $ARG | wc -l
```

---

## 📚 Resources & AI Usage

### References
* **Knuth, Donald E.** — *The Art of Computer Programming, Volume 3: Sorting and Searching*.
* **Big-O & Algorithm Analysis:** Theoretical asymptotic time and space complexity models.
* **42 School Subject Specification (Push_swap v1.1).**

### AI Usage Declaration
In accordance with 42 AI guidelines:
* **Documentation & Markdown Formatting:** LLM assistance was utilized to format Markdown tables, LaTeX mathematical equations, and README structure.
* **Code Review & Edge Case Analysis:** AI tools were consulted to discuss potential edge cases (e.g., integer overflows beyond 32-bit limits, duplicate values, memory leak checks).
* **Peer Verification:** All generated/discussed logic was audited, tested, and validated in person by the pair before final submission.
