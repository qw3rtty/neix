cmake_minimum_required(VERSION 3.13)

project(crss)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lcmocka")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lcurl")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lncurses")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wpedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-parameter")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.c)

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