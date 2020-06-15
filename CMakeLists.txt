cmake_minimum_required(VERSION 3.13)

project(crss)

# Version
set(crssVersion "0.1.0")
add_compile_definitions(VERSION="${crssVersion}")

# Path for feed config file
set(FeedConfigPath "$ENV{HOME}/.config/crss/feeds.conf")
add_compile_definitions(FEED_CONFIG_PATH="${FeedConfigPath}")

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
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)
FILE(GLOB parser ${PROJECT_SOURCE_DIR}/src/parser/*.cpp)
FILE(GLOB commands ${PROJECT_SOURCE_DIR}/src/commands/*.cpp)
FILE(GLOB config ${PROJECT_SOURCE_DIR}/src/config/*.cpp)
FILE(GLOB helper ${PROJECT_SOURCE_DIR}/src/helper/*.cpp)

add_executable(crss
    ${src}
    ${helper}
    ${feed}
    ${parser}
    ${config}
)

option(enable-tests "Enables test suite" YES)
if(enable-tests)
    enable_testing()
    add_subdirectory(test)
    add_test(FeedLoader /bin/test-feedloader)
    add_test(Parser /bin/test-parser)
    add_test(Feeds /bin/test-feeds)
	add_test(Commands /bin/test-commands)
	add_test(Config /bin/test-config)
    add_test(Helper /bin/test-helper)
endif()

INSTALL(TARGETS crss RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
