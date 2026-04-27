# C++ Module 09 — STL Containers in Practice

> **42KL Core — Module 5**

Applies STL containers to three distinct algorithmic problems: a Bitcoin exchange rate calculator (`std::map`), a Reverse Polish Notation (RPN) evaluator (`std::list`/stack), and the Ford-Johnson merge-insert sort algorithm (`std::vector` + `std::deque`). Each exercise may only use **one** specific STL container internally.

---

## 📁 Project Structure

```
m5/CPP09/
├── ex00/   # Bitcoin Exchange — date-indexed price lookup with std::map
├── ex01/   # RPN — Reverse Polish Notation calculator
└── ex02/   # PmergeMe — Ford-Johnson merge-insert sort
```

---

## 📝 Exercises

### ex00 — Bitcoin Exchange

**Concepts:** `std::map`, CSV parsing, lower-bound date lookup, input validation.

Reads a historical Bitcoin price database (`data.csv`) and an input file containing `date | value` pairs, then prints each date's Bitcoin value multiplied by the corresponding historical price.

**Data file format (`data.csv`):**
```
date,exchange_rate
2011-01-03,0.3
2011-01-08,0.22
...
```

**Input file format:**
```
date | value
2011-01-03 | 3
2012-01-11 | 100.0
```

**Key behaviours:**

| Condition | Output |
|---|---|
| Date found exactly | `2011-01-03 => 3 = 0.9` |
| Date not found — use nearest earlier date | Uses closest lower date |
| No earlier date exists | `Error: bad input => <date>` |
| Value < 0 | `Error: not a positive number` |
| Value > 1000 | `Error: too large a number` |
| Malformed line | `Error: bad input` |

**Class:** `BitcoinExchange` — loads the DB into a `std::map<std::string, float>`, uses `lower_bound` for date lookup.

```bash
./btc input.txt
```

**Key files:** `include/BitcoinExchange.hpp`, `src/BitcoinExchange.cpp`, `data.csv`

---

### ex01 — RPN (Reverse Polish Notation)

**Concepts:** Stack-based expression evaluation, `std::list` as stack, tokenisation.

Evaluates a **Reverse Polish Notation** expression passed as a single command-line argument (tokens separated by spaces). Supports `+`, `-`, `*`, `/` on single-digit non-negative operands.

**How RPN works:**
- Push operands onto the stack.
- When an operator is encountered, pop the top two values, apply the operator, and push the result.

```bash
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
# Output: 42

./RPN "7 7 * 7 -"
# Output: 42
```

**Error handling:** Prints `Error` to stderr for malformed expressions, division by zero, or insufficient operands.

**Class:** `RPN` — tokenises the input into a `std::list<std::string>`, processes tokens left to right.

**Key files:** `include/RPN.hpp`, `src/RPN.cpp`

---

### ex02 — PmergeMe (Ford-Johnson Merge-Insert Sort)

**Concepts:** `std::vector`, `std::deque`, benchmarking with `clock()`, algorithmic complexity comparison.

Implements the **Ford-Johnson merge-insert sort** (also known as merge-insertion sort) on two containers simultaneously — once using `std::vector` and once using `std::deque` — then reports the time taken for each.

**How Ford-Johnson sort works (simplified):**
1. Pair up elements; keep the larger of each pair as the "main chain".
2. Recursively sort the main chain.
3. Binary-insertion sort the smaller elements into the sorted main chain using the optimal insertion sequence (Jacobsthal numbers).

```bash
./PmergeMe 3 5 9 7 4
# Before: 3 5 9 7 4
# After:  3 4 5 7 9
# Time to process a range of 5 elements with std::vector : 0.00031 us
# Time to process a range of 5 elements with std::deque  : 0.00015 us
```

**Class:** `PmergeMe` — stores `std::vector<std::size_t>` and `std::deque<std::size_t>` internally; runs both sorts independently and times them with `clock()`.

**Key files:** `include/PmergeMe.hpp`, `src/PmergeMe.cpp`

---

## 🔑 Key C++ Concepts Covered

- **`std::map`** — ordered associative container; O(log N) lookup with `lower_bound`
- **`std::list`** — doubly-linked list; efficient front/back insertion as a stack
- **`std::vector`** and **`std::deque`** — random-access sequence containers
- **CSV / custom format parsing** — `std::getline`, `std::istringstream`, string trimming
- **Error handling** — validation with descriptive error messages
- **Algorithm complexity** — understanding why Ford-Johnson achieves the minimum number of comparisons
- **Benchmarking** — `clock()` / `CLOCKS_PER_SEC` for performance measurement

---

## 🛠️ Build

```bash
cd ex00 && make && ./btc input.txt
cd ex01 && make && ./RPN "3 4 +"
cd ex02 && make && ./PmergeMe 3 5 9 7 4
```

```bash
make clean / make fclean / make re
```
