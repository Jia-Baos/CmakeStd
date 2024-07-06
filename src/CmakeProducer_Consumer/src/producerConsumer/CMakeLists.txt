cmake_minimum_required(VERSION 3.27)

project(producer_consumer)

aux_source_directory(. producer_consumer_files)

add_library(producer_consumer_static STATIC ${producer_consumer_files})
# add_library(producer_consumer_shared SHARED ${producer_consumer_files})

target_include_directories(producer_consumer_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(producer_consumer_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(producer_consumer_static PROPERTIES OUTPUT_NAME "producer_consumer")
# set_target_properties(producer_consumer_shared PROPERTIES OUTPUT_NAME "producer_consumer")

install(TARGETS producer_consumer_static
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)