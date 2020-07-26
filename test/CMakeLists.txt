# Path for feed config file tests
set(FeedConfigPathTest "${PROJECT_SOURCE_DIR}/test/testFeeds.conf")
add_compile_definitions(FEED_CONFIG_PATH_TEST="${FeedConfigPathTest}")

# Assets for testing
set(TestAssetsPath "${PROJECT_SOURCE_DIR}/test/assets")
add_compile_definitions(TEST_ASSET_ATOM="${TestAssetsPath}/atom.xml")
add_compile_definitions(TEST_ASSET_REDDIT="${TestAssetsPath}/reddit.xml")
add_compile_definitions(TEST_ASSET_RSS091="${TestAssetsPath}/rss0.91.xml")
add_compile_definitions(TEST_ASSET_RSS092="${TestAssetsPath}/rss0.92.xml")
add_compile_definitions(TEST_ASSET_RSS2="${TestAssetsPath}/rss2.0.xml")

FILE(GLOB src ${PROJECT_SOURCE_DIR}/src/*.cpp)
LIST(REMOVE_ITEM src ${PROJECT_SOURCE_DIR}/src/main.cpp)
FILE(GLOB feed ${PROJECT_SOURCE_DIR}/src/feed/*.cpp)
FILE(GLOB parser ${PROJECT_SOURCE_DIR}/src/parser/*.cpp)
FILE(GLOB config ${PROJECT_SOURCE_DIR}/src/config/*.cpp)
FILE(GLOB helper ${PROJECT_SOURCE_DIR}/src/helper/*.cpp)

FILE(GLOB tests ${PROJECT_SOURCE_DIR}/test/*.cpp)
FILE(GLOB testApplication ${PROJECT_SOURCE_DIR}/test/application/ApplicationWindow.cpp)
FILE(GLOB testParser ${PROJECT_SOURCE_DIR}/test/parser/Parser.cpp)
FILE(GLOB testFeedLoader ${PROJECT_SOURCE_DIR}/test/feed/FeedLoader.cpp)
FILE(GLOB testFeeds ${PROJECT_SOURCE_DIR}/test/feed/Feeds.cpp)
FILE(GLOB testConfig ${PROJECT_SOURCE_DIR}/test/config/ConfigReader.cpp)
FILE(GLOB testHelper ${PROJECT_SOURCE_DIR}/test/helper/helper.cpp)

add_executable(tests
    ${src}
    ${tests}

    ${testConfig}
    ${testHelper}
    ${testFeedLoader}
    ${testFeeds}
    ${testParser}
    ${testApplication}
)
target_link_libraries(tests gtest)
target_link_libraries(tests neixFeed)
target_link_libraries(tests neixParser)
target_link_libraries(tests neixConfig)
target_link_libraries(tests neixHelper)
target_link_libraries(tests neixApplication)
