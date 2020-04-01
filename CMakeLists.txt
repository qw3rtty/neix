cmake_minimum_required(VERSION 3.13)

project(crss)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lcurl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lncurses")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(crss
    ${src}
)

option(enable-tests "Enables test suite" YES)
if(enable-tests)
    enable_testing()
    add_subdirectory(test)
    add_test(Test-Application /bin/tests)
endif()

INSTALL(TARGETS crss RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")