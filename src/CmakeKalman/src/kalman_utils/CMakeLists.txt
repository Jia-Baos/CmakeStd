cmake_minimum_required(VERSION 3.27)

project(kalman)

aux_source_directory(. main_files)

add_library(kalman_static STATIC ${main_files})
add_library(kalman_shared SHARED ${main_files})

target_include_directories(kalman_static
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Lib_Dir}
        )
target_include_directories(kalman_shared
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${Lib_Dir})

target_link_libraries(kalman_static
        PUBLIC
        Eigen3::Eigen)

target_link_libraries(kalman_shared
        PUBLIC
        Eigen3::Eigen)

set_target_properties(kalman_static PROPERTIES OUTPUT_NAME "kalman")
set_target_properties(kalman_shared PROPERTIES OUTPUT_NAME "kalman")

install(TARGETS kalman_static kalman_shared
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN "*.hpp"
        PATTERN "CMakeLists.txt" EXCLUDE)
