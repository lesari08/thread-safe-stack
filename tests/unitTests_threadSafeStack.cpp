#include <gtest/gtest.h>
#include <numeric>
#include <memory>
#include <thread>
#include "ThreadSafeStack.h"

// Define fixture for the SafeStack tests
class SafeStackTest : public ::testing::Test
{
protected:
    ts::SafeStack<int> stack;
};

// Test basic push and pop functionality
TEST_F(SafeStackTest, PushAndPop)
{
    stack.push(1);
    stack.push(2);

    int val;
    stack.pop(val);
    EXPECT_EQ(val, 2);

    stack.pop(val);
    EXPECT_EQ(val, 1);
}

// Test if stack is empty after construction
TEST_F(SafeStackTest, IsEmptyInitially)
{
    EXPECT_TRUE(stack.empty());
}

// Test popping from an empty stack
TEST_F(SafeStackTest, PopFromEmptyStack)
{
    int val;
    EXPECT_THROW(stack.pop(val), ts::empty_stack);
}

// Test popping using shared_ptr
TEST_F(SafeStackTest, PopSharedPtr)
{
    stack.push(42);
    std::shared_ptr<int> ptr = stack.pop();

    EXPECT_EQ(*ptr, 42);
}

// Test concurrent push and pop operations
TEST(SafeStackConcurrentTest, ConcurrentPushAndPop)
{
    ts::SafeStack<int> stack;

    const int num_threads = 4;
    const int num_pushes = 10000;
    std::vector<std::thread> threads;

    auto pushFuncPtr =[&stack, num_pushes]{
        for (int j = 0; j < num_pushes; ++j){
            stack.push(j);
            int val;
            stack.pop(val);
        }
    };

    for (int i = 0; i < num_threads; ++i)
    {
        threads.emplace_back(pushFuncPtr);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }

    // At this point, all threads have completed their push and pop operations.
    // Check if the stack is empty.
    EXPECT_TRUE(stack.empty());

}

// Test concurrent push operations from multiple threads
TEST(SafeStackConcurrentTest, ConcurrentPush)
{
    ts::SafeStack<int> stack;

    const int num_threads = 4;
    const int num_pushes = 10000;
    std::vector<std::thread> threads;

    auto pushFuncPtr = [&stack, num_pushes] {
        for (int j = 0; j < num_pushes; ++j) {
            stack.push(j);
        }
    };

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(pushFuncPtr);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // At this point, all threads have completed their push operations.
    // The stack should have a total of num_threads * num_pushes elements.
    int count = 0;
    int val;
    while (!stack.empty()) {
        stack.pop(val);
        ++count;
    }

    EXPECT_EQ(count, num_threads * num_pushes);
}

// Test concurrent pop operations using shared_ptr from multiple threads
TEST(SafeStackConcurrentTest, ConcurrentPopSharedPtr)
{
    ts::SafeStack<int> stack;

    const int num_threads = 4;
    const int num_pushes = 10000;

    // Fill the stack with values first
    for (int i = 0; i < num_threads * num_pushes; ++i) {
        stack.push(i);
    }

    std::vector<std::thread> threads;
    std::vector<std::shared_ptr<int>> popped_values;

    auto popFuncPtr = [&stack, &popped_values, num_pushes] {
        for (int j = 0; j < num_pushes; ++j) {
            popped_values.push_back(stack.pop());
        }
    };

    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(popFuncPtr);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    // At this point, all threads have completed their pop operations.
    // Verify that all the popped values are unique and correct.
    std::sort(popped_values.begin(), popped_values.end());
    popped_values.erase(std::unique(popped_values.begin(), popped_values.end()), popped_values.end());

    EXPECT_EQ(popped_values.size(), num_threads * num_pushes);
}