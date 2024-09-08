cmake_minimum_required(VERSION 3.27)

project(event_bus)

aux_source_directory(. event_bus_files)

add_library(event_bus_static STATIC ${event_bus_files})
add_library(event_bus_shared SHARED ${event_bus_files})

target_include_directories(event_bus_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(event_bus_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(event_bus_static PROPERTIES OUTPUT_NAME "event_bus")
set_target_properties(event_bus_shared PROPERTIES OUTPUT_NAME "event_bus")

install(TARGETS event_bus_static event_bus_shared
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)
