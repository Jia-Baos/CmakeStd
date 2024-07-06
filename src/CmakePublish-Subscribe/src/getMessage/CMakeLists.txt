cmake_minimum_required(VERSION 3.27)

project(get_message)

aux_source_directory(. get_message_files)

add_library(get_message_static STATIC ${get_message_files})
# add_library(get_message_shared SHARED ${get_message_files})

target_include_directories(get_message_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(get_message_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(get_message_static PROPERTIES OUTPUT_NAME "get_message")
# set_target_properties(get_message_shared PROPERTIES OUTPUT_NAME "get_message")

install(TARGETS get_message_static
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)