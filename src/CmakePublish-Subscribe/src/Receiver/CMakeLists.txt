cmake_minimum_required(VERSION 3.27)

project(receiver)

aux_source_directory(. receiver_files)

add_library(receiver_static STATIC ${receiver_files})
# add_library(receiver_shared SHARED ${receiver_files})

target_include_directories(receiver_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(receiver_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(receiver_static PROPERTIES OUTPUT_NAME "receiver")
# set_target_properties(receiver_shared PROPERTIES OUTPUT_NAME "receiver")

install(TARGETS receiver_static
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)