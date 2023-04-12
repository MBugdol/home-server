message(NOTICE "Starting work on library's test suite")

set(CMAKE_CXX_STANDARD 20)

add_executable(demo testsuite1.cpp)
target_link_libraries(demo PRIVATE HoseBackendLib)
add_test(NAME EntryValidTests COMMAND demo)