FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.cpp)
FILE(GLOB testFeedLoader ${PROJECT_SOURCE_DIR}/test/feed/FeedLoader.cpp)
FILE(GLOB testFeedParser ${PROJECT_SOURCE_DIR}/test/feed/FeedParser.cpp)

add_executable(test-feedloader
    ${src}
    ${feed}
    ${testFeedLoader}
)

add_executable(test-feedparser
    ${src}
    ${feed}
    ${testFeedParser}
)