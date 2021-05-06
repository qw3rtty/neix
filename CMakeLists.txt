cmake_minimum_required(VERSION 3.12)
project(neix)

include(GNUInstallDirs)

# Check if 'curl' is installed
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

# Check if 'ncurses' is installed
SET(CURSES_NEED_NCURSES TRUE)
SET(CURSES_NEED_WIDE TRUE)
find_package(Curses)
if (NOT CURSES_FOUND)
    MESSAGE(STATUS "ncursesw not found. Include only ncurses.")
    SET(CURSES_NEED_WIDE FALSE)
    find_package(Curses REQUIRED)
endif()
 include_directories(${CURSES_INCLUDE_DIRS})

SET(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

# Prepare filesystem for installation
file(MAKE_DIRECTORY $ENV{HOME}/.config/neix/)

# Check for main config file
if(NOT EXISTS "$ENV{HOME}/.config/neix/neix.conf")
    configure_file(./config/neix.conf $ENV{HOME}/.config/neix/neix.conf)
endif()

# Check for feed config file
if(NOT EXISTS "$ENV{HOME}/.config/neix/feeds.conf")
    configure_file(./config/feeds.conf $ENV{HOME}/.config/neix/feeds.conf)
endif()

# Version
set(neixVersion "0.1.5")
add_compile_definitions(VERSION="v${neixVersion}")

# User Agent for CURL
set(neixUserAgent "neix/${neixVersion}")
add_compile_definitions(NEIX_USER_AGENT="${neixUserAgent}")

# Add default config URL's
add_compile_definitions(DEFAULT_MAIN_CONFIG="${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/neix/neix.conf")
add_compile_definitions(DEFAULT_FEEDS_CONFIG="${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATAROOTDIR}/neix/feeds.conf")

# Path for main neix config file
set(MainConfigPath "$ENV{HOME}/.config/neix/neix.conf")
add_compile_definitions(MAIN_CONFIG_PATH="${MainConfigPath}")

# Path for feed config file
set(FeedConfigPath "$ENV{HOME}/.config/neix/feeds.conf")
add_compile_definitions(FEED_CONFIG_PATH="${FeedConfigPath}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/library)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

FILE(GLOB main ${PROJECT_SOURCE_DIR}/src/*.cpp)
FILE(GLOB application ${PROJECT_SOURCE_DIR}/src/application/*.cpp)
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)
FILE(GLOB parser ${PROJECT_SOURCE_DIR}/src/parser/*.cpp)
FILE(GLOB config ${PROJECT_SOURCE_DIR}/src/config/*.cpp)
FILE(GLOB helper ${PROJECT_SOURCE_DIR}/src/helper/*.cpp)

add_library(neixApplication STATIC ${application})
add_library(neixFeed STATIC ${feed})
add_library(neixParser STATIC ${parser})
add_library(neixConfig STATIC ${config})
add_library(neixHelper STATIC ${helper})

add_executable(neix ${main})
target_link_libraries(neix neixApplication ${CURSES_LIBRARIES})
target_link_libraries(neix neixFeed ${CURL_LIBRARY})
target_link_libraries(neix neixParser)
target_link_libraries(neix neixConfig)
target_link_libraries(neix neixHelper)

option(ENABLE-TESTS "Enables test suite" OFF)
if(ENABLE-TESTS MATCHES ON)
	# Download and configure google test
	include(CMake/CMakeLists.googletest.txt)

    add_subdirectory(test)
endif()

# Install definitons
install(TARGETS neix RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
install(FILES ./doc/neix.1 DESTINATION "${CMAKE_INSTALL_PREFIX}/share/man/man1")

install(FILES ./config/neix.conf DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/neix")
install(FILES ./config/feeds.conf DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/neix")

# Uninstall definitins
add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "CMake/uninstall.cmake"
)

