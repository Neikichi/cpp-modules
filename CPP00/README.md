# C++ Module 00 — Namespaces, Classes, and Member Functions

> **42KL Core — Module 4**

An introduction to C++ fundamentals: namespaces, class definitions, member functions, access specifiers (`public`/`private`), the orthodox canonical class form, and file I/O streams. Three exercises build up from printing text to implementing a full PhoneBook application.

---

## 📁 Project Structure

```
m4/CPP00/
├── ex00/    # Megaphone — string uppercasing
├── ex01/    # PhoneBook — simple contact management
└── ex02/    # Account — fixed log file reconstruction
```

---

## 📝 Exercises

### ex00 — Megaphone

**Concepts:** Command-line arguments, `std::string`, character conversion, `std::cout`.

Converts all input text to uppercase and prints it.

```bash
./megaphone "Hello" "world"
# Output: HELLOWORLD
```

If no arguments are provided:
```
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

**Key files:** `src/main.cpp`

---

### ex01 — PhoneBook

**Concepts:** Classes, member variables, member functions, `private` access specifier, `std::cin`, formatted output (`std::setw`, `std::right`).

A simple in-memory phone book that stores up to **8 contacts**. If a 9th is added, the oldest entry is overwritten (circular buffer behaviour).

**Classes:**

| Class | Description |
|---|---|
| `Contact` | Stores a contact's first name, last name, nickname, phone number, and darkest secret |
| `PhoneBook` | Manages up to 8 `Contact` objects; provides `add` and `search` commands |

**Commands (interactive):**

| Command | Action |
|---|---|
| `ADD` | Prompts for all fields and saves a new contact |
| `SEARCH` | Displays a truncated list; user enters index to view full contact |
| `EXIT` | Exits the program |

**Output format:** Each column is exactly 10 characters wide; strings longer than 10 characters are truncated to 9 + `.`.

**Key files:** `include/Contact.hpp`, `include/PhoneBook.hpp`, `src/`

---

### ex02 — Account

**Concepts:** Static member variables, static member functions, constructor/destructor ordering, formatted output matching a reference log file.

Reconstructs the output of a banking `Account` class from a provided reference log file (`19920104_091532.log`). The implementation must match the expected log output exactly, including timestamps, deposit/withdrawal records, and account statistics.

**Key files:** `include/Account.hpp`, `src/`

---

## 🔑 Key C++ Concepts Covered

- **Namespace** (`std::`) and avoiding `using namespace std` in headers
- **Class** definition with `private` data and `public` interface
- **Member functions** defined both inline and in `.cpp` files
- **Constructors** and **destructors** (canonical form)
- **Static members** shared across all instances
- **`std::string`** manipulation (`toupper`, `length`, `substr`)
- **`std::cin`** / **`std::cout`** / **`std::cerr`** for I/O
- **Stream formatting** (`std::setw`, `std::right`, `std::left`)

---

## 🛠️ Build

Each exercise has its own Makefile:

```bash
cd ex00 && make && ./megaphone "hello 42"
cd ex01 && make && ./phonebook
cd ex02 && make && ./account
```

```bash
make clean   # Remove object files
make fclean  # Remove object files + binary
make re      # Rebuild from scratch
```

---

## 📝 Notes

- All exercises compile with `-Wall -Wextra -Werror` and the C++98 standard (`-std=c++98`).
- `Account.hpp` is provided as-is (do not modify); only the implementation `.cpp` must be written.
