cmake_minimum_required(VERSION 3.27)

project(notifier)

aux_source_directory(. notifier_files)

add_library(notifier_static STATIC ${notifier_files})
# add_library(notifier_shared SHARED ${notifier_files})

target_include_directories(notifier_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(notifier_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(notifier_static PROPERTIES OUTPUT_NAME "notifier")
# set_target_properties(notifier_shared PROPERTIES OUTPUT_NAME "notifier")

install(TARGETS notifier_static
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)