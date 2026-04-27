# C++ Module 08 — Templated Containers, Iterators, and Algorithms

> **42KL Core — Module 5**

Covers the C++ Standard Template Library (STL): templated containers (`std::vector`, `std::list`, `std::stack`), iterators, and algorithms (`std::find`, `std::min_element`, `std::max_element`). Three exercises build generic utilities that work across any STL-compatible container.

---

## 📁 Project Structure

```
m5/CPP08/
├── ex00/   # Easy find — generic container search with iterators
├── ex01/   # Span — integer span container
└── ex02/   # MutantStack — iterable stack adapter
```

---

## 📝 Exercises

### ex00 — EasyFind

**Concepts:** Function template, iterator return, `std::find`, exception on not-found.

```cpp
template <typename T>
typename T::iterator easyfind(T& container, int value);
```

Searches for `value` in any STL integer container using `std::find`. Returns an iterator to the found element. Throws an exception if the value is not found.

```cpp
std::vector<int> v;
v.push_back(1);
v.push_back(2);
v.push_back(3);
v.push_back(4);
v.push_back(5);

std::vector<int>::iterator it = easyfind(v, 3);    // returns iterator to 3
easyfind(v, 99);                                   // throws NotFoundException

std::list<int> l;
l.push_back(10);
l.push_back(20);
l.push_back(30);

easyfind(l, 20);                                   // works with any container
```

**Key files:** `include/EasyFind.hpp`, `include/EasyFind.tpp`

---

### ex01 — Span

**Concepts:** STL container member, `std::min_element`/`std::max_element`, range-based adding with iterators.

`Span` stores up to `N` unsigned integers and computes spans:

| Member | Description |
|---|---|
| `Span(unsigned int N)` | Constructs a span with maximum capacity `N` |
| `addNumber(unsigned int n)` | Adds one number; throws if already at capacity |
| `shortestSpan()` | Minimum difference between any two stored numbers |
| `longestSpan()` | Maximum difference between any two stored numbers |
| `autoRandElement(unsigned int max)` | Adds a random element in range `[0, max)` |
| `begin()` / `end()` | Iterators over the internal container |

Both span functions throw if fewer than 2 numbers are stored.

```cpp
Span sp(5);
sp.addNumber(6);
sp.addNumber(3);
sp.addNumber(17);
sp.addNumber(9);
sp.addNumber(11);

std::cout << sp.shortestSpan();  // 2
std::cout << sp.longestSpan();   // 14
```

**Bulk insert using iterators:**

```cpp
std::vector<int> src;
src.push_back(1);
src.push_back(2);
src.push_back(3);
src.push_back(4);
src.push_back(5);
Span sp(10);
// Use iterator range constructor or addNumber in a loop
```

**Key files:** `include/Span.hpp`, `src/Span.cpp`

---

### ex02 — MutantStack

**Concepts:** Class template inheritance from STL container, adding iterator support via `container_type`.

`std::stack` is a container adaptor that intentionally hides iterators. `MutantStack<T>` extends `std::stack<T>` to expose iterators from the underlying `container_type` (default: `std::deque<T>`):

```cpp
template<typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator       iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;
};
```

```cpp
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);
mstack.push(3);

MutantStack<int>::iterator it = mstack.begin();
MutantStack<int>::iterator ite = mstack.end();
while (it != ite)
    std::cout << *it++ << " ";   // iterates from bottom to top
```

All standard `std::stack` operations (`push`, `pop`, `top`, `size`, `empty`) continue to work.

**Key files:** `include/MutantStack.hpp`, `include/MutantStack.tpp`

---

## 🔑 Key C++ Concepts Covered

- **STL iterators** — `begin()` / `end()`, iterator categories, dereferencing and incrementing
- **STL algorithms** — `std::find`, `std::min_element`, `std::max_element`
- **STL containers** — `std::vector`, `std::list`, `std::stack`, `std::deque`
- **Template containers** — writing generic code that works with any container exposing `::iterator`
- **Container adaptor inheritance** — exposing hidden internals through public inheritance and `container_type`
- **Exception safety** — throwing on capacity overflow or insufficient data

---

## 🛠️ Build

```bash
cd ex00 && make && ./easyfind
cd ex01 && make && ./span
cd ex02 && make && ./mutantstack
```

```bash
make clean / make fclean / make re
```

---

## 📝 Notes

- All exercises compile with `-Wall -Wextra -Werror -std=c++98`.
- Template implementations (`.tpp` files) are included at the bottom of their respective `.hpp` headers.
- `MutantStack` inherits publicly from `std::stack` — this is generally inadvisable in production code (STL containers have non-virtual destructors), but is acceptable for this exercise.
- `Span::shortestSpan()` requires sorting a copy of the stored integers; the sorted-adjacent-difference approach is O(N log N) rather than the naïve O(N²).
