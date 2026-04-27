# C++ Module 02 — Ad-hoc Polymorphism, Operator Overloading, and Fixed-Point Numbers

> **42KL Core — Module 4**

Introduces the **Orthodox Canonical Class Form** (OCF), **operator overloading**, and implements a **fixed-point number** type from scratch. The module culminates in a Binary Space Partitioning (BSP) exercise using the completed `Fixed` class.

---

## 📁 Project Structure

```
m4/CPP02/
├── ex00/   # My First Class in Orthodox Canonical Form
├── ex01/   # Towards a more useful fixed-point number class
├── ex02/   # Now we're talking
└── ex03/   # BSP
```

---

## 📝 Exercises

### ex00 — Orthodox Canonical Form (OCF)

**Concepts:** The four canonical class functions required by the C++98 standard.

Introduces `Fixed`, a class that stores a fixed-point number using **one integer member** and a **static constant** for fractional bits (8 bits).

**OCF methods implemented:**
1. Default constructor (initialises raw value to 0)
2. Copy constructor
3. Copy assignment operator
4. Destructor

Also adds:
- `getRawBits()` — returns the raw integer value
- `setRawBits(int raw)` — sets the raw integer value

**Key files:** `include/Fixed.hpp`, `src/Fixed.cpp`

---

### ex01 — Useful Fixed-Point

**Concepts:** Converting between `int`, `float`, and fixed-point representation; `roundf`; `std::ostream` insertion operator.

Extends `Fixed` with:

| Member | Description |
|---|---|
| `Fixed(int n)` | Constructs from int — shifts left by fractional bits |
| `Fixed(float f)` | Constructs from float — `roundf(f * (1 << frac_bits))` |
| `toInt() const` | Converts fixed-point to int (truncating) |
| `toFloat() const` | Converts fixed-point to float |
| `operator<<` | Outputs the float representation to a stream |

**Key files:** `include/Fixed.hpp`, `src/Fixed.cpp`

---

### ex02 — Full Operator Overloading

**Concepts:** Comparison operators, arithmetic operators, increment/decrement (pre/post), static min/max methods.

Adds a comprehensive set of operators to `Fixed`:

**Comparison operators:** `>`, `<`, `>=`, `<=`, `==`, `!=`

**Arithmetic operators:** `+`, `-`, `*`, `/`

**Increment / Decrement:**

| Operator | Behaviour |
|---|---|
| `++f` (pre) | Increments by smallest representable step, returns new value |
| `f++` (post) | Increments by smallest representable step, returns old value |
| `--f` / `f--` | Decrement equivalents |

**Static utility functions:**
- `Fixed& min(Fixed& a, Fixed& b)` — returns reference to the smaller value
- `Fixed& max(Fixed& a, Fixed& b)` — returns reference to the larger value
- `const` overloads of the above

**Key files:** `include/Fixed.hpp`, `src/Fixed.cpp`

---

### ex03 — BSP (Binary Space Partitioning)

**Concepts:** Using `Fixed` in a geometric algorithm; `Point` class; BSP triangle test.

Implements a `Point` class (two `Fixed` members `x` and `y`) and a `bsp` function:

```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point);
```

Returns `true` if `point` lies **strictly inside** the triangle `abc` (not on any edge or vertex), using the sign of the cross product of each edge with the point.

**Key files:** `include/Fixed.hpp`, `include/Point.hpp`, `include/BSP.hpp`, `src/`

---

## 🔑 Key C++ Concepts Covered

- **Orthodox Canonical Form** — default constructor, copy constructor, copy assignment operator, destructor
- **Fixed-point arithmetic** — integer with implicit fractional bits
- **`operator` overloading** — arithmetic, comparison, increment/decrement, stream insertion
- **`const` correctness** — const member functions, const overloads
- **Static member functions** — class-level utilities (`min`, `max`)
- **Geometric algorithms** — cross-product sign test for point-in-triangle

---

## 🛠️ Build

```bash
cd ex00 && make && ./fixed
cd ex01 && make && ./fixed
cd ex02 && make && ./fixed
cd ex03 && make && ./bsp
```

```bash
make clean / make fclean / make re
```
