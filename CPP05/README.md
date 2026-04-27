# C++ Module 05 — Exceptions and Error Handling

> **42KL Core — Module 5**

Introduces C++ exception handling using `try`/`catch`/`throw` and nested exception classes. The module centres on a bureaucratic office simulation where `Bureaucrat` objects sign and execute `Form` (later `AForm`) objects, with exceptions thrown for invalid grades or unauthorised operations.

---

## 📁 Project Structure

```
m5/CPP05/
├── ex00/   # Mommy, when I grow up, I want to be a bureaucrat! — Bureaucrat with exceptions
├── ex01/   # Form up, maggots! — Form class, sign/execute
├── ex02/   # No, you need form 28B, not 28C — AForm abstract + concrete forms
└── ex03/   # At least this beats coffee making — Intern creates forms
```

---

## 📝 Exercises

### ex00 — Bureaucrat

**Concepts:** Nested exception classes, `what()` override, grade validation.

`Bureaucrat` has a `const` name and a grade (1 = highest, 150 = lowest).

**Nested exceptions:**

| Exception | Thrown when |
|---|---|
| `GradeTooHighException` | Grade would go below 1 |
| `GradeTooLowException` | Grade would go above 150 |

**Member functions:**

| Function | Description |
|---|---|
| `getName()` | Returns the bureaucrat's name |
| `getGrade()` | Returns the current grade |
| `promote()` | Decrements grade (higher rank); throws if already 1 |
| `demote()` | Increments grade (lower rank); throws if already 150 |
| `operator<<` | Prints `<name>, bureaucrat grade <grade>` |

```cpp
try {
    Bureaucrat b("Alice", 1);
    b.promote();   // throws GradeTooHighException
} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
}
```

**Key files:** `include/Bureaucrat.hpp`, `src/Bureaucrat.cpp`

---

### ex01 — Form

**Concepts:** Associating exceptions with objects, `const` member variables, cross-object method calls.

`Form` (later renamed `AForm`) has:
- A `const` name
- A boolean `isSigned` flag
- A `const` grade required to sign
- A `const` grade required to execute

**Member functions:**

| Function | Description |
|---|---|
| `beSigned(Bureaucrat&)` | Signs the form if the bureaucrat's grade is high enough; throws `GradeTooLowException` otherwise |
| `operator<<` | Prints form name, signed status, and grade requirements |

`Bureaucrat::signForm(Form&)` calls `beSigned()` and prints an appropriate success/failure message.

---

### ex02 — AForm (Abstract) + Concrete Forms

**Concepts:** Abstract base class, polymorphic `execute()`, derived form classes.

`Form` becomes `AForm` — an abstract class with a pure virtual `execute()`:

```cpp
virtual void execute(Bureaucrat const & executor) const = 0;
```

Three concrete form types:

| Form | Sign Grade | Exec Grade | Effect |
|---|---|---|---|
| `ShrubberyCreationForm` | 145 | 137 | Creates `<target>_shrubbery` file with ASCII trees |
| `RobotomyRequestForm` | 72 | 45 | 50% chance of robotomising `<target>`; drills sounds |
| `PresidentialPardonForm` | 25 | 5 | Announces that `<target>` has been pardoned by Zaphod Beeblebrox |

`Bureaucrat::executeForm(AForm const&)` calls `execute()` and prints success/failure.

---

### ex03 — Intern

**Concepts:** Table-driven object creation, eliminating long `if`/`else` chains with arrays.

`Intern` class with a single member function:

```cpp
AForm* makeForm(std::string formName, std::string target);
```

Uses a lookup table (array of form names + function pointers or lambdas) to instantiate the correct form without `if`/`else` chains. Returns `NULL` and prints an error if the form name is unknown.

```cpp
Intern someRandomIntern;
AForm* rrf = someRandomIntern.makeForm("robotomy request", "Bender");
```

**Key files:** `include/Intern.hpp`, `src/Intern.cpp`

---

## 🔑 Key C++ Concepts Covered

- **`try` / `catch` / `throw`** — structured exception handling
- **Nested exception classes** — inner classes inheriting from `std::exception`
- **`what()` override** — custom exception messages
- **Abstract classes** with pure virtual functions
- **`const` member variables** — set only at construction
- **Polymorphic method calls** through base class pointers/references
- **Table-driven design** — using arrays to eliminate repetitive `if`/`else`

---

## 🛠️ Build

```bash
cd ex00 && make && ./bureaucrat
cd ex01 && make && ./bureaucrat
cd ex02 && make && ./forms
cd ex03 && make && ./intern
```

```bash
make clean / make fclean / make re
```

