# StaticVector
## A fixed-capacity, header-only C++ vector implementation designed for embedded systems.

StaticVector is a lightweight, fixed-capacity container for C++ that works entirely on the stack. 
Unlike `std::vector`, it does **not allocate memory dynamically**, making it suitable for embedded systems where deterministic memory usage is critical. 

It manages object lifetimes manually, supports non-trivial types, and provides push, pop, and emplacement operations.

## Features
- Fixed capacity known at compile-time
- No dynamic memory allocation (heap-free)
- Supports non-trivial types with manual construction/destruction
- Placement new and perfect forwarding for `emplace_back`
- Optional STL-like interface: `operator[]`, `size()`, `capacity()`
- Rule of 5 compliant (copy/move constructors and assignment)

## Example

```cpp
#include "StaticVector.hpp"
#include <string>
#include <iostream>

int main() {
    StaticVector<std::string, 3> vec;

    vec.emplace_back("Hello");
    vec.emplace_back("Embedded");
    vec.emplace_back("World");

    for (std::size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << std::endl;

    vec.pop_back();
    std::cout << "Size after pop: " << vec.size() << std::endl;

    return 0;
}
```
---

## 5️⃣ Requirements

What someone needs to build it:

```markdown
## Requirements
- C++20 compiler (GCC, Clang, or MSVC)
- CMake >= 3.16

## Build

```bash
mkdir build
cd build
cmake ..
make
./static_vector    # runs the example
```
 
## Notes
- Objects are manually constructed and destroyed using placement new.
- Accessing elements beyond `size()` is undefined behavior.
- Designed for deterministic memory usage in embedded environments.
