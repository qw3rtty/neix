FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)
FILE(GLOB parser ${PROJECT_SOURCE_DIR}/src/parser/*.cpp)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.cpp)
FILE(GLOB testParser ${PROJECT_SOURCE_DIR}/test/parser/Parser.cpp)
FILE(GLOB testFeedLoader ${PROJECT_SOURCE_DIR}/test/feed/FeedLoader.cpp)
FILE(GLOB testFeeds ${PROJECT_SOURCE_DIR}/test/feed/Feeds.cpp)

add_executable(test-feedloader
    ${src}
    ${feed}
    ${parser}
    ${testFeedLoader}
)

add_executable(test-parser
    ${src}
    ${feed}
    ${parser}
    ${testParser}
)

add_executable(test-feeds
    ${src}
    ${feed}
    ${parser}
    ${testFeeds}
)