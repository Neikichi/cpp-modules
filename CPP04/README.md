# C++ Module 04 — Subtype Polymorphism, Abstract Classes, and Interfaces

> **42KL Core — Module 4**

Covers runtime polymorphism through **virtual functions**, **abstract classes** (pure virtual), **deep copy semantics**, and **interface patterns** using abstract base classes. Four exercises progress from basic virtual dispatch to a full interface-based Materia system.

---

## 📁 Project Structure

```
m4/CPP04/
├── ex00/   # Polymorphism — Animal, Dog, Cat, WrongAnimal
├── ex01/   # I don't want to set the world on fire — Brain and deep copy
├── ex02/   # Abstract class — prevent Animal instantiation
└── ex03/   # Interface & recap — AMateria, ICharacter, MateriaSource
```

---

## 📝 Exercises

### ex00 — Polymorphism

**Concepts:** Virtual functions, runtime dispatch, `WrongAnimal` non-virtual counter-example.

`Animal` base class with a virtual `makeSound()` method.  
`Dog` and `Cat` override `makeSound()` with their own sounds.  
`WrongAnimal` and `WrongCat` demonstrate non-virtual behaviour (static dispatch).

```cpp
Animal* a = new Dog();
a->makeSound();   // outputs Dog's sound (virtual dispatch)

WrongAnimal* w = new WrongCat();
w->makeSound();   // outputs WrongAnimal's sound (no virtual)
```

**Key insight:** Without `virtual`, the base class method is always called regardless of the actual object type.

**Key files:** `include/Animal.hpp`, `include/Dog.hpp`, `include/Cat.hpp`, `include/WrongAnimal.hpp`, `include/WrongCat.hpp`

---

### ex01 — Deep Copy

**Concepts:** Heap-allocated member objects, deep copy in copy constructor and copy assignment operator, memory management.

Adds a `Brain` class — an array of 100 `std::string` ideas.

`Dog` and `Cat` each own a `Brain*` (heap-allocated). The copy constructor and copy assignment operator must perform a **deep copy** (allocate a new `Brain` and copy contents), not a shallow copy (pointer copy).

```cpp
Dog a;
Dog b(a);       // b has its own Brain, not a's
b.brain->ideas[0] = "new idea";   // does not affect a
```

**Key files:** `include/Brain.hpp`, `include/Cat.hpp`, `include/Dog.hpp`

---

### ex02 — Abstract Class

**Concepts:** Pure virtual functions, preventing instantiation of a base class.

`Animal` becomes **abstract** by making `makeSound()` pure virtual:

```cpp
virtual void makeSound() const = 0;
```

Attempting to instantiate `Animal` directly now causes a compile-time error. Only `Dog` and `Cat` (which implement `makeSound()`) can be instantiated.

**Key files:** `include/Animal.hpp`

---

### ex03 — Interface & Recap

**Concepts:** Pure abstract interfaces (`ICharacter`, `IMateriaSource`), abstract base class (`AMateria`), interface-based polymorphism, `clone()` pattern.

A complete Materia/RPG-item system:

**Classes:**

| Class | Type | Description |
|---|---|---|
| `AMateria` | Abstract | Base for all materias; has `type`, `getType()`, pure virtual `clone()` and `use()` |
| `Ice` | Concrete | Extends `AMateria`; `use()` prints an ice spell message |
| `Cure` | Concrete | Extends `AMateria`; `use()` prints a heal message |
| `ICharacter` | Interface | Pure abstract: `equip(AMateria*)`, `unequip(int)`, `use(int, ICharacter&)` |
| `Character` | Concrete | Implements `ICharacter`; holds up to 4 materia slots |
| `IMateriaSource` | Interface | Pure abstract: `learnMateria(AMateria*)`, `createMateria(std::string)` |
| `MateriaSource` | Concrete | Implements `IMateriaSource`; stores up to 4 learned templates, clones on demand |

**Workflow:**

```cpp
IMateriaSource* src = new MateriaSource();
src->learnMateria(new Ice());
src->learnMateria(new Cure());

ICharacter* bob = new Character("Bob");
bob->equip(src->createMateria("ice"));   // clones the learned Ice
bob->use(0, *bob);                        // Bob uses ice on himself
```

**Key files:** `include/AMateria.hpp`, `include/ICharacter.hpp`, `include/IMateriaSource.hpp`, `include/Character.hpp`, `include/MateriaSource.hpp`, `include/Ice.hpp`, `include/Cure.hpp`

---

## 🔑 Key C++ Concepts Covered

- **`virtual` functions** — runtime polymorphic dispatch
- **Pure virtual functions** (`= 0`) — forces derived classes to implement the method
- **Abstract classes** — cannot be instantiated; serve as interfaces or base contracts
- **`virtual` destructors** — ensures proper cleanup when deleting through a base pointer
- **Deep copy** — copying heap-allocated members by value, not pointer
- **Interface pattern** — pure-abstract class with no data members, only virtual functions
- **`clone()` pattern** — virtual copy constructor idiom for polymorphic duplication
- **Memory management** — careful pairing of `new`/`delete` with polymorphic ownership

---

## 🛠️ Build

```bash
cd ex00 && make && ./animals
cd ex01 && make && ./animals
cd ex02 && make && ./animals
cd ex03 && make && ./materia
```

```bash
make clean / make fclean / make re
```
