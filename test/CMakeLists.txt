FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.cpp)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.cpp)

add_executable(tests
    ${src}
    ${tests}
)
