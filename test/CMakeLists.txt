FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.c)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.c)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.c)

include_directories(${CMOCKA_INCLUDE_DIR})
add_definitions(${CMOCKA_DEFINITIONS})

add_executable(tests
    ${src}
    ${tests}
)

target_link_libraries(tests
    pthread
    ${CMOCKA_LIBRARIES}
)