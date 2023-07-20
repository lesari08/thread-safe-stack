#include <gtest/gtest.h>
#include <numeric>
#include <memory>
#include <thread>
#include "ThreadSafeStack.h"


// Define fixture for the SafeStack tests
class SafeStackTest : public ::testing::Test {
protected:
    ts::SafeStack<int> stack;
};

// Test basic push and pop functionality
TEST_F(SafeStackTest, PushAndPop) {
    stack.push(1);
    stack.push(2);

    int val;
    stack.pop(val);
    EXPECT_EQ(val, 2);

    stack.pop(val);
    EXPECT_EQ(val, 1);
}

// Test if stack is empty after construction
TEST_F(SafeStackTest, IsEmptyInitially) {
    EXPECT_TRUE(stack.empty());
}

// Test popping from an empty stack
TEST_F(SafeStackTest, PopFromEmptyStack) {
    int val;
    EXPECT_THROW(stack.pop(val), ts::empty_stack);
}

// Test popping using shared_ptr
TEST_F(SafeStackTest, PopSharedPtr) {
    stack.push(42);
    std::shared_ptr<int> ptr = stack.pop();

    EXPECT_EQ(*ptr, 42);
}

// Test concurrent push and pop operations
TEST(SafeStackConcurrentTest, ConcurrentPushAndPop) {
    ts::SafeStack<int> stack;

    const int num_threads = 4;
    const int num_pushes = 10000;
    std::vector<std::thread> threads;

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&stack, num_pushes] {
            for (int j = 0; j < num_pushes; ++j) {
                stack.push(j);
                int val;
                stack.pop(val);
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // At this point, all threads have completed their push and pop operations.
    // Check if the stack is empty.
    EXPECT_TRUE(stack.empty());
}
