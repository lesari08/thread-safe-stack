cmake_minimum_required(VERSION 3.14)
project(unitTests_threadSafeStack_PJ)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEST1 unitTests_threadSafeStack)


# include FetchContent module
include(FetchContent)
FetchContent_Declare(
  googletest
  URL "${PROJECT_SOURCE_DIR}/lib/googletest-03597a01ee50ed33e9dfd640b249b4be3799d395.zip"
)

# # For Windows: Prevent overriding the parent project's compiler/linker settings
# # set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable( ${TEST1} "${PROJECT_SOURCE_DIR}/unitTests_threadSafeStack.cpp")

target_include_directories(${TEST1} PUBLIC "${CMAKE_SOURCE_DIR}/include")

target_link_libraries( ${TEST1} GTest::gtest_main)


#look for tests in the given executable
include(GoogleTest)
gtest_discover_tests(
${TEST1} 
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  XML_OUTPUT_DIR unit_test_results

)


