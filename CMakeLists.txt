cmake_minimum_required(VERSION 3.0.0)
project(libsvm_test VERSION 0.1.0)

add_compile_options("-std=gnu++11")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(LibSVM)

include_directories(${LIBSVM_INCLUDE_DIRS})
link_libraries(${LIBSVM_LIBRARY})
add_executable(libsvm_test main.cpp)
# target_link_libraries(libsvm_test ${LIBSVM_LIBRARIES})
