# C++ Module 03 — Inheritance

> **42KL Core — Module 4**

Explores class inheritance, constructor/destructor chaining, access specifiers in derived classes, and multiple inheritance including the **diamond problem**. The module builds a hierarchy of robot classes: `ClapTrap` → `ScavTrap` / `FragTrap` → `DiamondTrap`.

---

## 📁 Project Structure

```
m4/CPP03/
├── ex00/   # Aaaaand... OPEN! — ClapTrap base class
├── ex01/   # Serena, my love! — Single inheritance (ScavTrap)
├── ex02/   # Repetita iuvant — Single inheritance (FragTrap)
└── ex03/   # Now it's weird! — Multiple inheritance (DiamondTrap)
```

---

## 📝 Exercises

### ex00 — ClapTrap (Base Class)

`ClapTrap` is a robot that can attack, take damage, and repair itself.

| Attribute | Starting Value |
|---|---|
| Hit Points | 10 |
| Energy Points | 10 |
| Attack Damage | 0 |

**Member functions:**

| Function | Description |
|---|---|
| `attack(target)` | Deals `attackDamage` to target; costs 1 energy point |
| `takeDamage(amount)` | Reduces hit points by `amount` |
| `beRepaired(amount)` | Restores hit points by `amount`; costs 1 energy point |

All actions check that the robot has enough energy points and is not dead. Constructor/destructor messages are printed.

**Key files:** `include/ClapTrap.hpp`, `src/ClapTrap.cpp`

---

### ex01 — ScavTrap (Derived from ClapTrap)

`ScavTrap` inherits from `ClapTrap` and overrides its stats and gains a special ability.

| Attribute | ScavTrap Value |
|---|---|
| Hit Points | 100 |
| Energy Points | 50 |
| Attack Damage | 20 |

**Additional function:**
- `guardGate()` — prints that ScavTrap is now in Gate keeper mode.

Constructor chain: `ClapTrap(name)` → `ScavTrap(name)`.  
Destructor chain reverses: `ScavTrap` → `ClapTrap`.

**Key files:** `include/ScavTrap.hpp`, `src/ScavTrap.cpp`

---

### ex02 — FragTrap (Derived from ClapTrap)

`FragTrap` is another `ClapTrap` derivative with different stats and its own special ability.

| Attribute | FragTrap Value |
|---|---|
| Hit Points | 100 |
| Energy Points | 100 |
| Attack Damage | 30 |

**Additional function:**
- `highFivesGuys()` — prints a positive high-fives request.

**Key files:** `include/FragTrap.hpp`, `src/FragTrap.cpp`

---

### ex03 — DiamondTrap (Multiple Inheritance)

`DiamondTrap` inherits from both `ScavTrap` and `FragTrap`, which both derive from `ClapTrap`. This creates the **diamond problem** — solved with **virtual inheritance** so that only one `ClapTrap` subobject exists.

| Attribute | DiamondTrap Value |
|---|---|
| Hit Points | FragTrap's (100) |
| Energy Points | ScavTrap's (50) |
| Attack Damage | FragTrap's (30) |
| `attack()` | Uses ScavTrap's implementation |

**Additional function:**
- `whoAmI()` — prints both the DiamondTrap name and the ClapTrap name.

DiamondTrap has two names: its own name and the ClapTrap name set to `<name>_clap_name`.

**Inheritance diagram:**

```
        ClapTrap (virtual base)
       /         \
  ScavTrap      FragTrap
       \         /
       DiamondTrap
```

**Key files:** `include/DiamondTrap.hpp`, `src/DiamondTrap.cpp`

---

## 🔑 Key C++ Concepts Covered

- **Single inheritance** — derived class extending a base class
- **Constructor/destructor chaining** — order of construction (base → derived) and destruction (derived → base)
- **Access control in inheritance** — `public`/`protected`/`private` base
- **Function overriding** — derived class replacing a base class member function
- **Multiple inheritance** — a class with two or more base classes
- **Diamond problem** — ambiguous base class subobject when two bases share a common ancestor
- **Virtual inheritance** — ensures a single shared base subobject in diamond hierarchies
- **`using` directive** — bringing specific base-class functions into scope

---

## 🛠️ Build

```bash
cd ex00 && make && ./claptrap
cd ex01 && make && ./scavtrap
cd ex02 && make && ./fragtrap
cd ex03 && make && ./diamondtrap
```

```bash
make clean / make fclean / make re
```

