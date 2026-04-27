# C++ Module 06 — C++ Type Casting

> **42KL Core — Module 5**

Covers the four C++ type-casting operators: `static_cast`, `dynamic_cast`, `reinterpret_cast`, and `const_cast`. Three exercises explore scalar type conversion, pointer serialisation/deserialisation, and runtime type identification using `dynamic_cast`.

---

## 📁 Project Structure

```
m5/CPP06/
├── ex00/   # Conversion of scalar types — ScalarConverter
├── ex01/   # Serialization — Serializer (reinterpret_cast)
└── ex02/   # Identify real type — dynamic_cast type identification
```

---

## 📝 Exercises

### ex00 — ScalarConverter

**Concepts:** `static_cast`, string-to-type parsing, special float/double literals.

`ScalarConverter` is a non-instantiable utility class (private constructor) with a single static method:

```cpp
static void convert(const std::string& input);
```

Takes a **string literal** and converts it to all four scalar types, printing each:

```
char:   <value> or Non displayable / impossible
int:    <value> or impossible
float:  <value>f or nanf / +inff / -inff
double: <value> or nan / +inf / -inf
```

**Input detection rules:**

| Type | Detection |
|---|---|
| `char` | Single printable character not a digit |
| `int` | Numeric string without `.` or `f` suffix |
| `float` | Numeric string ending in `f` (e.g. `42.0f`) |
| `double` | Numeric string with `.` but no `f` |
| Special | `nan`, `nanf`, `+inf`, `-inf`, `+inff`, `-inff` |

**Key files:** `include/ScalarConverter.hpp`, `src/ScalarConverter.cpp`

```bash
./convert 42
./convert 42.0f
./convert 'a'
./convert nan
```

---

### ex01 — Serializer

**Concepts:** `reinterpret_cast`, `uintptr_t`, pointer round-trip through integer representation.

`Serializer` is a non-instantiable utility class with two static methods:

```cpp
static uintptr_t serialize(Data* ptr);
static Data*     deserialize(uintptr_t raw);
```

`serialize` converts a `Data*` to a `uintptr_t` using `reinterpret_cast`.  
`deserialize` converts the integer back to a `Data*`.

The test verifies that deserialising the serialised pointer gives back the original pointer value and that the data members are intact.

**`Data` struct:**

```cpp
struct Data {
    std::string str;
    int val;
};
```

**Key files:** `include/Serializer.hpp`, `src/Serializer.cpp`

---

### ex02 — Real Type Identification

**Concepts:** `dynamic_cast`, runtime type identification (RTTI), random instantiation.

`Base` is an abstract class with a virtual destructor. `A`, `B`, and `C` inherit from it publicly with no additional members.

Two identification functions:

```cpp
void identify(Base* p);   // uses dynamic_cast<Type*>
void identify(Base& p);   // uses dynamic_cast<Type&> + try/catch
```

Both print the actual runtime type (`A`, `B`, or `C`).

A `generate()` function randomly allocates one of `A`, `B`, or `C` and returns it as a `Base*`.

**Key files:** `include/Base.hpp`, `include/A.hpp`, `include/B.hpp`, `include/C.hpp`, `src/`

---

## 🔑 C++ Casting Operators

| Cast | Purpose |
|---|---|
| `static_cast<T>(x)` | Compile-time numeric/type conversions; upcasts/downcasts with no runtime check |
| `dynamic_cast<T>(x)` | Safe downcast with runtime check (requires at least one `virtual` method); returns `nullptr` (pointer) or throws `std::bad_cast` (reference) on failure |
| `reinterpret_cast<T>(x)` | Bit-level reinterpretation of a value; use only when you know what you're doing |
| `const_cast<T>(x)` | Add or remove `const`/`volatile` qualification |

---

## 🛠️ Build

```bash
cd ex00 && make && ./convert 42.5f
cd ex01 && make && ./serializer
cd ex02 && make && ./identify
```

```bash
make clean / make fclean / make re
```

