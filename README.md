*This project has been created as part of the 42 curriculum by alesferr, ahideo-k.*

# push_swap

## Description

`push_swap` is a sorting project developed in C as part of the 42 curriculum.

The program receives a list of unique integers in Stack A and must sort them in ascending order using an auxiliary Stack B and a restricted set of operations.

The main program prints the sequence of operations required to sort the numbers. The project also contains:

- four sorting strategies with different complexity classes;
- an adaptive strategy based on the initial disorder of the input;
- a benchmark mode that reports execution metrics;
- stacks implemented with circular arrays.

---

## Authors and Contributions

### Alessandra — `alesferr`

Responsible for:

- implementation of the stack operations;
- implementation of the sorting algorithms;
- small-input sorting;
- Simple strategy;
- Medium strategy;
- Complex strategy;
- Adaptive strategy integration.

### André — `ahideo-k`

Responsible for:

- command-line argument parsing;
- strategy and benchmark flag parsing;
- numeric input validation;
- duplicate detection;
- integer overflow and underflow validation;
- disorder metric calculation;
- rank normalization;
- benchmark calculation and reporting.

Both learners participated in project integration, testing, debugging, code review, and validation of the final implementation.

---

## Project Features

- Parsing of integers passed as separate arguments or inside quoted strings.
- Validation of non-numeric arguments.
- Validation of values outside the `int` range.
- Duplicate detection.
- Circular-array implementation of Stack A and Stack B.
- Initial disorder calculation before any sorting operation.
- Conversion of original values into normalized ranks.
- Four required strategies:
  - Simple: \(O(n^2)\)
  - Medium: \(O(n\sqrt{n})\)
  - Complex: \(O(n\log n)\)
  - Adaptive
- Optional benchmark mode.
- Complete memory cleanup on normal execution and errors.

---

## Circular Array Data Structure

The two stacks are implemented as circular arrays instead of linked lists.

```c
typedef struct s_stack
{
	int	*v;
	int	cap;
	int	top;
	int	size;
}	t_stack;
```

Each field has a specific purpose:

| Field | Description |
|---|---|
| `v` | Pointer to the dynamically allocated integer array. |
| `cap` | Maximum number of elements that can be stored. |
| `top` | Physical array index of the logical top of the stack. |
| `size` | Current number of elements stored in the stack. |

A logical position is converted into a physical array position with:

```c
(top + i) % cap
```

This calculation is implemented by `st_get`:

```c
int	st_get(t_stack *s, int i)
{
	return (s->v[(s->top + i) % s->cap]);
}
```

For example, consider:

```text
cap  = 5
top  = 3
size = 3
```

The logical elements are accessed as follows:

```text
Logical position 0 → v[(3 + 0) % 5] → v[3]
Logical position 1 → v[(3 + 1) % 5] → v[4]
Logical position 2 → v[(3 + 2) % 5] → v[0]
```

The logical stack therefore wraps around the end of the physical array:

```text
Physical array indexes:  0    1    2    3    4
Logical order:           [2]  [ ]  [ ]  [0]  [1]
                                       ↑
                                      top
```

The circular-array design allows rotations and pushes to update indexes instead of shifting every element in memory.

### Advantages

- `swap` changes only two array positions;
- `push` updates the source and destination top indexes;
- `rotate` advances the top index;
- `reverse rotate` moves the top index backward;
- no linked-list node allocation is required;
- no full-array shift is required for each rotation;
- stack operations are performed in constant time, \(O(1)\).

Both Stack A and Stack B receive capacity for all input numbers because, during sorting, every element may temporarily move from one stack to the other.

---

## Supported Operations

| Operation | Name | Description |
|---|---|---|
| `sa` | Swap A | Swaps the first two elements of Stack A. |
| `sb` | Swap B | Swaps the first two elements of Stack B. |
| `ss` | Swap Both | Executes `sa` and `sb` simultaneously. |
| `pa` | Push A | Moves the top element of Stack B to Stack A. |
| `pb` | Push B | Moves the top element of Stack A to Stack B. |
| `ra` | Rotate A | Moves the top element of Stack A to the bottom. |
| `rb` | Rotate B | Moves the top element of Stack B to the bottom. |
| `rr` | Rotate Both | Executes `ra` and `rb` simultaneously. |
| `rra` | Reverse Rotate A | Moves the bottom element of Stack A to the top. |
| `rrb` | Reverse Rotate B | Moves the bottom element of Stack B to the top. |
| `rrr` | Reverse Rotate Both | Executes `rra` and `rrb` simultaneously. |

All operations pass through `do_op`, which:

1. executes the requested operation;
2. increments the corresponding operation counter;
3. prints the operation when quiet mode is disabled.

---

## Parsing and Validation

The program accepts numbers passed separately:

```bash
./push_swap 4 67 3 87 23
```

It also accepts multiple numbers inside the same argument:

```bash
./push_swap "4 67 3" "87 23"
```

The parser performs the following validations:

- each argument must contain at least one numeric token;
- optional `+` and `-` signs are accepted;
- each sign must be followed by at least one digit;
- values must remain between `INT_MIN` and `INT_MAX`;
- characters other than digits, signs, spaces, and string terminators are rejected;
- duplicate integer values are rejected;
- invalid strategy flags are rejected.

When an error is detected, the program frees allocated memory and prints:

```text
Error
```

to the standard error output.

---

## Disorder Metric

The disorder metric is calculated before any sorting operation.

It measures the proportion of inverted pairs in the initial Stack A.

A pair is considered inverted when a larger value appears before a smaller value.

For a stack with \(n\) elements, the total number of possible pairs is:

\[
pairs = n * (n-1) / 2
\]

The program counts the inverted pairs as `mistakes` and calculates:

\[
disorder = ((mistakes * 10000) + pairs / 2) / pairs
\]

Examples:

```text
[1, 2, 3] → 0.00% disorder
[2, 1, 3] → 33.33% disorder
[3, 2, 1] → 100.00% disorder
```

The implementation stores the result as an integer between `0` and `10000`:

```text
0     →   0.00%
2000  →  20.00%
5000  →  50.00%
10000 → 100.00%
```

This representation allows the program to keep two decimal places without using floating-point numbers.

---

## Rank Normalization

Before sorting, the original integers are converted into ranks from `0` to `n - 1`.

The rank of a number is equal to the number of values smaller than it.

Example:

```text
Original values: [50, 10, 30]
Ranks:           [ 2,  0,  1]
```

The relative order remains unchanged:

```text
50 > 30 > 10
 2 >  1 >  0
```

Rank normalization provides the following advantages:

- negative and positive values are treated uniformly;
- very large differences between original values no longer matter;
- the Complex strategy can inspect binary bits safely;
- the set of normalized values is always between `0` and `n - 1`.

The rank calculation uses a temporary array. After all ranks are calculated, they replace the original values, and the temporary array is freed.

---

## Sorting Strategies

### Small-Input Optimization

When Adaptive mode is active and the input contains at most five numbers, the project uses `sort_small`.

Its behavior is:

- two elements: use `sa` when necessary;
- three elements: use predefined comparisons and operations;
- four or five elements:
  - move the smallest values to Stack B;
  - sort the remaining three values;
  - push the stored values back to Stack A.

This avoids running a general-purpose strategy for very small inputs.

---

### Simple Strategy — \(O(n^2)\)

The Simple strategy uses minimum extraction.

For each iteration:

1. find the logical position of the smallest value in Stack A;
2. choose the shortest rotation direction;
3. rotate the minimum value to the top;
4. execute `pb` to move it to Stack B;
5. continue until the remaining Stack A is ordered;
6. execute `pa` until every value returns to Stack A.

The function `min_pos` searches for the minimum value, while `rot_to_top` decides between normal and reverse rotation.

In the worst case, finding and positioning each minimum requires a linear number of operations for a linear number of elements.

Therefore, the Push_swap operation complexity is:

\[
O(n^2)
\]

The strategy uses constant temporary storage beyond the two preallocated stacks.

---

### Medium Strategy — \(O(n\sqrt{n})\)

The Medium strategy uses chunk-based partitioning.

The approximate chunk size is calculated with:

```c
ft_isqrt(3 * size / 2) + 2
```

Its main steps are:

1. divide the normalized ranks into ranges of approximately \(\sqrt{n}\);
2. inspect the value at the top of Stack A;
3. push values belonging to the current range into Stack B;
4. rotate lower-ranked values inside Stack B to improve their placement;
5. rotate Stack A when the current value is outside the active range;
6. after Stack A becomes empty, repeatedly locate the maximum value in Stack B;
7. rotate the maximum to the top by the shortest path;
8. execute `pa` to rebuild Stack A in ascending order.

The number of chunks and the amount of work per chunk produce an operation complexity of:

\[
O(n\sqrt{n})
\]

The two stacks require \(O(n)\) total storage.

---

### Complex Strategy — \(O(n\log n)\)

The Complex strategy uses binary LSD Radix Sort.

Because all numbers have already been converted into ranks from `0` to `n - 1`, the algorithm can process their binary representations.

For each bit, beginning with the least significant bit:

1. inspect the current top value of Stack A;
2. execute `pb` when the current bit is `0`;
3. execute `ra` when the current bit is `1`;
4. repeat until every element has been inspected;
5. execute `pa` until Stack B becomes empty;
6. continue with the next bit.

The number of required bits is approximately:

\[
\log_2(n)
\]

Each bit processes all \(n\) elements, producing:

\[
O(n\log n)
\]

Push_swap operations.

The strategy uses the two \(O(n)\) stacks, while rank normalization temporarily uses an additional \(O(n)\) array.

---

### Adaptive Strategy

Adaptive mode is the default behavior when no strategy selector is provided.

The initial disorder determines the general strategy:

| Initial disorder | Selected strategy | Complexity |
|---|---|---|
| \(D < 0.20\) | Simple | \(O(n^2)\) |
| \(0.20 \le D < 0.50\) | Medium | \(O(n\sqrt{n})\) |
| \(D \ge 0.50\) | Complex | \(O(n\log n)\) |

Internally, the stored thresholds are:

```text
disorder < 2000  → Simple
disorder < 5000  → Medium
otherwise        → Complex
```

For inputs containing at most five elements, Adaptive mode uses the dedicated small-input algorithm regardless of the disorder percentage.

The thresholds provide:

- a simple baseline for low-disorder inputs;
- chunk-based processing for intermediate disorder;
- deterministic Radix Sort behavior for highly disordered inputs.

---

## Benchmark Mode

Every operation is counted in:

```c
long	count[11];
```

The array has one position for each operation:

```text
SA, SB, SS, PA, PB, RA, RB, RR, RRA, RRB, RRR
```

When `--bench` is enabled, the program reports:

- initial disorder percentage;
- selected strategy;
- theoretical complexity class;
- total number of operations;
- count of every individual operation.

The benchmark is printed to `stderr`, while sorting operations remain on `stdout`.

Example:

```bash
./push_swap --bench --adaptive 4 67 3 87 23
```

Example benchmark output:

```text
[bench] disorder:  40.00%
[bench] strategy:  Adaptive / O(n^2)
[bench] total_ops: 9
[bench] sa: 0 sb: 0 ss: 0 pa: 2 pb: 2
[bench] ra: 4 rb: 0 rr: 0 rra: 1 rrb: 0 rrr: 0
```

To hide the operations and display only the benchmark:

```bash
./push_swap --bench --adaptive 4 67 3 87 23 >/dev/null
```

---

## Instructions

### Requirements

The project requires:

- a C compiler such as `cc`;
- the `make` utility;
- a Unix-compatible environment.

### Compilation

Compile the mandatory program:

```bash
make
```

Remove object files:

```bash
make clean
```

Remove object files and executables:

```bash
make fclean
```

Recompile the project completely:

```bash
make re
```

---

### Basic Usage

```bash
./push_swap [flags] <integer list>
```

Example:

```bash
./push_swap 2 1 3 6 5 8
```

The program prints one operation per line:

```text
sa
pb
ra
...
```

When no arguments are provided, the program prints nothing.

---

### Strategy Flags

Force the Simple strategy:

```bash
./push_swap --simple 5 4 3 2 1
```

Force the Medium strategy:

```bash
./push_swap --medium 5 4 3 2 1
```

Force the Complex strategy:

```bash
./push_swap --complex 5 4 3 2 1
```

Force Adaptive mode:

```bash
./push_swap --adaptive 5 4 3 2 1
```

Run Adaptive mode implicitly:

```bash
./push_swap 5 4 3 2 1
```

Strategy and benchmark flags must appear before the numeric arguments.

Multiple flags can be combined:

```bash
./push_swap --bench --complex 5 4 3 2 1
```

---

### Verifying with the Checker

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | ./checker $ARG
```

Expected result:

```text
OK
```

---

### Counting Operations

```bash
ARG="4 67 3 87 23"
./push_swap $ARG | wc -l
```

---

### Testing with 100 Random Numbers

```bash
ARG=($(shuf -i 1-500 -n 100))
./push_swap "${ARG[@]}" | ./checker "${ARG[@]}"
```

Count the generated operations:

```bash
ARG=($(shuf -i 1-500 -n 100))
./push_swap "${ARG[@]}" | wc -l
```

---

### Testing with 500 Random Numbers

```bash
ARG=($(shuf -i 1-1000 -n 500))
./push_swap "${ARG[@]}" | ./checker "${ARG[@]}"
```

Count the generated operations:

```bash
ARG=($(shuf -i 1-1000 -n 500))
./push_swap "${ARG[@]}" | wc -l
```

---

## Project Structure

| File | Responsibility |
|---|---|
| `push_swap.h` | Enums, structures, includes, and function prototypes. |
| `main.c` | Main execution flow and strategy selection. |
| `stack.c` | Stack initialization, logical access, sorted-state verification, and cleanup. |
| `ops.c` | Implementation and execution of all Push_swap operations. |
| `parse.c` | Flag parsing and centralized error handling. |
| `parse_nums.c` | Token counting, integer conversion, stack filling, and duplicate detection. |
| `disorder.c` | Disorder calculation and rank normalization. |
| `sort_small.c` | Optimized sorting for up to five elements. |
| `sort_simple.c` | \(O(n^2)\) minimum-extraction strategy. |
| `sort_medium.c` | \(O(n\sqrt{n})\) chunk-based strategy. |
| `sort_complex.c` | \(O(n\log n)\) binary Radix Sort strategy. |
| `utils.c` | String, output, and integer square-root utilities. |
| `utils2.c` | Operation names, minimum search, and shortest-path rotation. |
| `bench.c` | Benchmark formatting and operation totals. |
| `Makefile` | Compilation rules for `push_swap` and `checker`. |

---

## Resources

### References

- 42 School — *Push_swap Subject, Version 1.1*.
- Donald E. Knuth — *The Art of Computer Programming, Volume 3: Sorting and Searching*.
- C manual pages for `malloc`, `free`, `read`, `write`, and `exit`.
- References on Big-O notation and asymptotic algorithm analysis.
- References on Selection Sort, chunk-based sorting, and binary LSD Radix Sort.
- 42 Norm documentation, Version 4.1.

Useful websites:
- https://push-swap-visualizer.vercel.app/
- https://labuladong.online/en/algo/data-structure-basic/cycle-array/

### AI Usage

AI tools were used as learning and review support for:

- explanations of C pointers, structures, arrays, and memory addresses;
- analysis of the real execution flow of the program;
- review of parsing and validation edge cases;
- discussion of integer overflow and underflow;
- verification of disorder and rank calculations;
- creation of test commands;
- review of benchmark behavior;
- README organization and Markdown formatting.

All code, algorithms, tests, and explanations were reviewed by both learners. The pair remained responsible for understanding, validating, and defending the complete implementation.
