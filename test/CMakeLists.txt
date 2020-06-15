# Path for feed config file tests
set(FeedConfigPathTest "$ENV{PWD}/test/testFeeds.conf")
add_compile_definitions(FEED_CONFIG_PATH_TEST="${FeedConfigPathTest}")

FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/Application.cpp)
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)
FILE(GLOB parser ${PROJECT_SOURCE_DIR}/src/parser/*.cpp)
FILE(GLOB commands ${PROJECT_SOURCE_DIR}/src/commands/*.cpp)
FILE(GLOB config ${PROJECT_SOURCE_DIR}/src/config/*.cpp)
FILE(GLOB helper ${PROJECT_SOURCE_DIR}/src/helper/*.cpp)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/test/main.cpp)
FILE(GLOB testParser ${PROJECT_SOURCE_DIR}/test/parser/Parser.cpp)
FILE(GLOB testFeedLoader ${PROJECT_SOURCE_DIR}/test/feed/FeedLoader.cpp)
FILE(GLOB testFeeds ${PROJECT_SOURCE_DIR}/test/feed/Feeds.cpp)
FILE(GLOB testCommands ${PROJECT_SOURCE_DIR}/test/commands/Commands.cpp)
FILE(GLOB testConfig ${PROJECT_SOURCE_DIR}/test/config/ConfigReader.cpp)
FILE(GLOB testHelper ${PROJECT_SOURCE_DIR}/test/helper/helper.cpp)

add_executable(test-feedloader
    ${src}
    ${feed}
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
    ${testFeeds}
)

add_executable(test-commands
    ${commands}
	${testCommands}
)

add_executable(test-config
	${config}
	${testConfig}
)

add_executable(test-helper
	${helper}
	${testHelper}
)
