/*******************************************************************************
 *  @file thread_safe_stack.h
 *  @brief This file contains methods that define and implement a thread
 *  safe stack data structure
 *
 *  @author Leslie Aririguzo
 *******************************************************************************/

#ifndef TS_STACK
#define TS_STACK 1

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

namespace ts
{
    struct empty_stack : std::exception
    {
        const char *what() const throw()
        {
            return "ThreadSafeStack is empty";
        }
    };

    /*******************************************************************************
     * class SafeStack
     *
     *  @brief Simple wrapper that provides thread safe access to an STL stack
     *
     *  @tparam Type  Type of element.
     *
     *******************************************************************************/
    template <class T>
    class SafeStack
    {
    public:
        SafeStack();

        SafeStack(const SafeStack &);

        SafeStack &operator=(const SafeStack &) = delete;

        void push(T val);

        // Pop() method overloads design rationale:
        // For thread safety no version of pop() returns a pass-by-value object
        // because we want pop to offer a strong exception guarantee (i.e if an
        // exception is thrown, the data will be left in its original state).
        // Returning a popped elememt by value erases that strong guarantee b/c
        // the copy constructor of 'T' could throw an exception while returning.
        // Which would leave us with a modified stack and no way of recovering
        // the popped element
        //
        // The only seemingly safe way I can currently think of to return a popped
        // element by value is by only allowing the stack to be used with objects
        // that have no-thow move and no-throw copy constructors. However, that
        // greatly limit the number of objects that this class can support

        void pop(T &output_object);
        std::shared_ptr<T> pop();

        bool empty();

    private:
        std::stack<T> m_stack;
        std::mutex m_mutex;
    };

    /*******************************************************************************
     *  constructor
     *******************************************************************************/
    template <class T>
    SafeStack<T>::SafeStack() {}

    /*******************************************************************************
     *  constructor
     *******************************************************************************/
    template <class T>
    SafeStack<T>::SafeStack(const SafeStack &other)
    {
        std::scoped_lock<std::mutex> lk(other.m_mutex);
        m_stack = other.m_stack; 
    }

    /*******************************************************************************
     *  @brief add element to the top of the stack
     *  @param val element to add
     *******************************************************************************/
    template <class T>
    void SafeStack<T>::push(T val)
    {
        std::scoped_lock<std::mutex> lk(m_mutex);
        m_stack.push(std::move(val));
    }

    /*******************************************************************************
     *  @brief remove top element from the stack and return its value
     *  @param output object to store the popped value
     *******************************************************************************/
    template <class T>
    void SafeStack<T>::pop(T &output)
    {
        std::scoped_lock<std::mutex> lk(m_mutex);
        if (m_stack.empty())
        {
            throw empty_stack();
        }

        output = m_stack.top();
        m_stack.pop();
    }

    /*******************************************************************************
     *  @brief remove top element from the stack and return its value
     *  @return shared_ptr contained the value of the removed elememt
     *******************************************************************************/
    template <class T>
    std::shared_ptr<T> SafeStack<T>::pop()
    {
        std::scoped_lock<std::mutex> lk(m_mutex);
        if (m_stack.empty())
        {
            throw empty_stack();
        }

        std::shared_ptr<T> ptr = std::make_shared<T>(m_stack.top());
        m_stack.pop();
        return ptr;
    }

    /*******************************************************************************
     *  @brief check if stack has zero elements
     *  @return true if empty
     *******************************************************************************/
    template <class T>
    bool SafeStack<T>::empty()
    {
        std::scoped_lock<std::mutex> lk(m_mutex);
        return m_stack.empty();
    }
}
#endif // TS_STACK
