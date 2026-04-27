# C++ Module 01 — Memory Allocation, Pointers, References, and File Streams

> **42KL Core — Module 4**

Explores how C++ manages memory on the stack vs. the heap, the distinction between pointers and references, `new`/`delete`, pointer-to-member-functions, and file I/O with `std::fstream`. Seven exercises build progressively on these concepts.

---

## 📁 Project Structure

```
m4/CPP01/
├── ex00/   # BraiiiiiiinnnzzzZ — Stack vs heap allocation
├── ex01/   # Moar brainz! — Array allocation with new[]
├── ex02/   # HI THIS IS BRAIN — Pointer vs reference comparison
├── ex03/   # Unnecessary violence — References vs pointers to objects
├── ex04/   # Sed is for losers — File string replacement
├── ex05/   # Harl 2.0 — Pointer-to-member-function
└── ex06/   # Harl filter — switch on log level
```

---

## 📝 Exercises

### ex00 — BraiiiiiiinnnzzzZ

**Concepts:** Stack allocation, heap allocation (`new`/`delete`), object lifetime, constructors/destructors.

Creates a `Zombie` class with a `name` and an `announce()` function. Demonstrates:
- `newZombie(name)` — allocates on the heap, returns pointer (caller must `delete`)
- `randomChump(name)` — allocates on the stack (destroyed at end of scope)

**Key files:** `include/Zombie.hpp`, `src/`

---

### ex01 — Moar brainz!

**Concepts:** Array allocation (`new[]`/`delete[]`), uniform constructor calls.

`zombieHorde(int N, std::string name)` allocates an array of `N` zombies on the heap in a **single allocation**, sets each zombie's name, and returns the pointer. The caller must `delete[]`.

**Key files:** `include/ZombieHorde.hpp`, `src/`

---

### ex02 — HI THIS IS BRAIN

**Concepts:** Pointer vs. reference — address comparison, dereference.

Declares a `string`, a pointer to it, and a reference to it. Prints the memory addresses and values of all three to demonstrate that a reference is just an alias (same address as the original).

---

### ex03 — Unnecessary violence

**Concepts:** References vs pointers to class instances, `const` references.

`Weapon` class with a `getType()` const reference getter and a `setType()` setter.  
`HumanA` holds a **reference** to a weapon (must be set at construction, cannot be null).  
`HumanB` holds a **pointer** to a weapon (can be set later, may be null).

**Key files:** `include/Weapon.hpp`, `include/HumanA.hpp`, `include/HumanB.hpp`, `src/`

---

### ex04 — Sed is for losers

**Concepts:** `std::ifstream`, `std::ofstream`, `std::string::find`, string replacement without `std::string::replace`.

Reads a file, replaces all occurrences of string `s1` with string `s2`, and writes the result to `<filename>.replace`. Does not use `std::string::replace()` internally.

```bash
./sed <filename> <s1> <s2>
```

---

### ex05 — Harl 2.0

**Concepts:** Pointer-to-member-function arrays — eliminates long `if`/`else` chains.

`Harl` class has four private member functions (`debug`, `info`, `warning`, `error`) that are invoked via a **pointer-to-member-function array** indexed by the complaint level string.

```cpp
void (Harl::*funcs[4])() = { &Harl::debug, &Harl::info,
                              &Harl::warning, &Harl::error };
```

---

### ex06 — Harl filter

**Concepts:** `switch` statement on a matched level index, fall-through behaviour.

Extends ex05: `harlFilter` takes a log level and prints all messages **at that level and above** using `switch` fall-through.

```bash
./harl WARNING
# prints WARNING and ERROR messages only
```

---

## 🔑 Key C++ Concepts Covered

- `new` / `delete` / `new[]` / `delete[]` — heap memory management
- Object lifetime: stack (automatic) vs. heap (manual)
- **References** as non-nullable aliases vs. **pointers** (nullable, reassignable)
- **Pointer-to-member-function** type and invocation syntax
- **`std::ifstream`** / **`std::ofstream`** — file read/write
- **`std::string::find`**, `substr`, manual string traversal
- `switch` fall-through as a dispatch mechanism

---

## 🛠️ Build

```bash
cd ex00 && make && ./zombie
cd ex01 && make && ./zombie_horde
cd ex02 && make && ./brain
cd ex03 && make && ./violence
cd ex04 && make && ./sed file.txt old new
cd ex05 && make && ./harl
cd ex06 && make && ./harl WARNING
```

```bash
make clean   # Remove object files
make fclean  # Remove object files + binary
make re      # Rebuild
```

