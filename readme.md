# Micrograd (C++)

A lightweight scalar-based automatic differentiation engine built from scratch in C++, inspired by Andrej Karpathy's [Micrograd](https://github.com/karpathy/micrograd).

### Current Features
- Templated `Value` class for scalar values.
- Operator overloading for addition and multiplication.
- Computational graph construction using parent references.
- Memory management using `std::shared_ptr`.
- Graph inspection through overloaded `<<` operator.
- Automated tests using C++ assertions.

### Tech Stack
- C++17
- STL (vector, shared_ptr)
- GNU Make

### Build & Test

```bash
make test
```

### Roadmap
- [ ] Gradient computation
- [ ] Backpropagation using the chain rule
- [ ] Reverse topological graph traversal
- [ ] Activation functions
- [ ] Neural network implementation
- [ ] Gradient descent optimizer

**Goal:** Understand and implement the fundamentals of automatic differentiation and backpropagation from scratch in C++.