cmake_minimum_required(VERSION 3.27)

project(client)

aux_source_directory(. client_files)

add_library(client_static STATIC ${client_files})
add_library(client_shared SHARED ${client_files})

target_include_directories(client_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(client_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(client_static PROPERTIES OUTPUT_NAME "client")
set_target_properties(client_shared PROPERTIES OUTPUT_NAME "client")

install(TARGETS client_static client_shared
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)