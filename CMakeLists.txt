cmake_minimum_required(VERSION 3.4.3)
project("SVF-SSE")

# set z3 env
if (DEFINED Z3_DIR)
    set(ENV{Z3_DIR} "${Z3_DIR}")
else()
    if (DEFINED ENV{Z3_DIR})
        set(Z3_DIR $ENV{Z3_DIR})
    else()
        message(FATAL_ERROR "\
WARNING: The Z3_DIR var was not set (required for an out-of-source build)!\n\
Please set this to environment variable to point to the SVF_DIR directory or set this variable to cmake configuration\n
(e.g. on linux: export Z3_DIR=/path/to/Z3/dir) \n or \n \n(make the project via: cmake -DZ3_DIR=your_path_to_Z3) ")
    endif()
endif()
set(Z3_HEADER "${Z3_DIR}/include/")
include_directories(${Z3_HEADER})
LINK_DIRECTORIES(${Z3_DIR}/bin)

add_executable(test0 test0.cpp)
add_executable(test2 test2.cpp)
add_executable(test3 test3.cpp)
add_executable(test4 test4.cpp)
add_executable(test5 test5.cpp)
target_link_libraries(test0 ${Z3_DIR}/bin/libz3.a )
target_link_libraries(test2 ${Z3_DIR}/bin/libz3.a )
target_link_libraries(test3 ${Z3_DIR}/bin/libz3.a )
target_link_libraries(test4 ${Z3_DIR}/bin/libz3.a )
target_link_libraries(test5 ${Z3_DIR}/bin/libz3.a )
