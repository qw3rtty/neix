FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.cpp)
FILE(GLOB test_feed ${PROJECT_SOURCE_DIR}/test/feed/*.cpp)

add_executable(tests
    ${src}
    ${feed}
    ${tests}
    ${test_feed}
)
