# C++ Module 07 — C++ Templates

> **42KL Core — Module 5**

Introduces C++ **function templates** and **class templates**. Three exercises implement generic utility functions and a type-safe dynamic array, exploring template type deduction, specialisation, and the use of templates in header-only implementations.

---

## 📁 Project Structure

```
m5/CPP07/
├── ex00/   # Start with a few functions — generic swap, min, max
├── ex01/   # Iter — generic array iterator
└── ex02/   # Array — generic dynamic array class template
```

---

## 📝 Exercises

### ex00 — Generic Functions

**Concepts:** Function templates, template type deduction, `const` references.

Three header-only template functions in `Whatever.hpp`:

| Function | Signature | Description |
|---|---|---|
| `swap` | `void swap(T& a, T& b)` | Swaps two values of the same type |
| `min` | `const T& min(const T& a, const T& b)` | Returns the smaller of two values; if equal, returns `b` |
| `max` | `const T& max(const T& a, const T& b)` | Returns the larger of two values; if equal, returns `b` |

All three work with any type that supports `<`, `==`, and copy-assignment.

```cpp
int a = 2, b = 3;
::swap(a, b);              // a=3, b=2
std::cout << ::min(a, b);  // 2
std::cout << ::max(a, b);  // 3
```

**Key files:** `include/Whatever.hpp`

---

### ex01 — Iter

**Concepts:** Function pointer as template parameter, `const` overload, generic array traversal.

`iter` is a function template that applies a function to every element of an array:

```cpp
template <typename T, typename U>
void iter(T* arr, U len, void (*f)(T&));

template <typename T, typename U>
void iter(const T* arr, U len, void (*f)(const T&));
```

The third argument is a **function pointer** (or a template function instantiation) that takes a reference to the element type.

```cpp
void doubleInt(int &x) { x *= 2; }

int arr[] = {1, 2, 3, 4, 5};
::iter(arr, 5, doubleInt);
```

**Key files:** `include/Iter.hpp`

---

### ex02 — Array Class Template

**Concepts:** Class templates, operator overloading (`[]`), custom exception, template member functions.

`Array<T>` is a generic dynamic array:

| Member | Description |
|---|---|
| `Array()` | Default constructor — creates empty array |
| `Array(unsigned int n)` | Creates array of `n` default-initialised elements |
| `Array(const Array& other)` | Deep copy constructor |
| `operator=(const Array&)` | Deep copy assignment |
| `~Array()` | Destructor — releases heap memory |
| `operator[](unsigned int idx)` | Element access with bounds checking |
| `size()` | Returns the number of elements |

**Bounds checking:** `operator[]` throws `std::exception` if `idx >= size`.

```cpp
Array<int> arr(5);
arr[0] = 42;
std::cout << arr.size();  // 5

Array<std::string> strs(3);
strs[0] = "hello";

Array<int> copy(arr);     // deep copy — modifying copy does not affect arr
```

Implementation is split across `Array.hpp` (class definition) and `Array.tpp` (method implementations), included at the bottom of `Array.hpp`.

**Key files:** `include/Array.hpp`, `include/Array.tpp`

---

## 🔑 Key C++ Concepts Covered

- **Function templates** — generic functions parameterised by type
- **Template type deduction** — compiler infers `T` from arguments
- **Class templates** — generic class parameterised by type
- **Header-only templates** — template definitions must be visible at instantiation (`.tpp` included in `.hpp`)
- **`const` overloads** — separate templates for mutable and const arrays/elements
- **Exception safety** — throwing on out-of-bounds access
- **Deep copy** in a templated class

---

## 🛠️ Build

```bash
cd ex00 && make && ./whatever
cd ex01 && make && ./iter
cd ex02 && make && ./array
```

```bash
make clean / make fclean / make re
```
