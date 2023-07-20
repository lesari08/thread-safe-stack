
# Thread-Safe Stack

[![Build Status](https://travis-ci.com/lesari08/thread-safe-stack.svg?branch=main)](https://travis-ci.com/lesari08/thread-safe-stack)

Thread-Safe Stack is a simple, C++ header-only library that provides a thread-safe implementation of a stack data structure. It allows concurrent access from multiple threads without causing data corruption or crashes.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

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
