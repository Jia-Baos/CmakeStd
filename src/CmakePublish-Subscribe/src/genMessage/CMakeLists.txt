cmake_minimum_required(VERSION 3.27)

project(gen_message)

aux_source_directory(. gen_message_files)

add_library(gen_message_static STATIC ${gen_message_files})
# add_library(gen_message_shared SHARED ${gen_message_files})

target_include_directories(gen_message_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(gen_message_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(gen_message_static PROPERTIES OUTPUT_NAME "gen_message")
# set_target_properties(gen_message_shared PROPERTIES OUTPUT_NAME "gen_message")

install(TARGETS gen_message_static
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)