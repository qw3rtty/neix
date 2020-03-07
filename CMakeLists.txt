cmake_minimum_required(VERSION 3.13)

project(crss)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lncurses")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(crss
    ${src}
)

INSTALL(TARGETS crss RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")