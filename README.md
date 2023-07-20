
# Thread-Safe Stack

[![badge](https://img.shields.io/badge/license-MIT-blue)](https://github.com/thread-safe-stack/master/LICENSE)

Thread-Safe Stack is a simple, C++ header-only library that provides a thread-safe implementation of a stack data structure. It allows concurrent access from multiple threads without causing data corruption or crashes.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [License](#license)

## Introduction
<a name="introduction"></a>

In multi-threaded applications, using a regular stack can lead to race conditions and undefined behavior when accessed concurrently. The Thread-Safe Stack library provides a safe and efficient solution to this problem by utilizing a mutex to synchronize access to the stack. This allows multiple threads to push and pop elements without conflicts or data integrity issues.

## Features

- Thread-safe implementation of a stack data structure.
- Supports push and pop operations with automatic synchronization.
- Header-only library, easy to integrate into existing projects.
- Exception-safe pop operation with strong exception guarantee.
- Well-documented code with simple and clear API.

## Getting Started


### Prerequisites

- C++11 or later.

### Installation

1. Download the `thread_safe_stack.h` file from the [include](./include) directory in this repository.

2. Copy the `thread_safe_stack.h` file into your project's include directory.

### Building and Running Tests

To build and run the unit tests, you need CMake and a C++ compiler that supports C++11 or later.

```bash
mkdir build && cd build
cmake ..
cmake --build .
ctest
```

## License
<a name="license"></a>
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.



