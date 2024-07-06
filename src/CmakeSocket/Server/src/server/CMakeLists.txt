cmake_minimum_required(VERSION 3.27)

project(server)

aux_source_directory(. server_files)

add_library(server_static STATIC ${server_files})
add_library(server_shared SHARED ${server_files})

target_include_directories(server_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(server_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(server_static PROPERTIES OUTPUT_NAME "server")
set_target_properties(server_shared PROPERTIES OUTPUT_NAME "server")

install(TARGETS server_static server_shared
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)