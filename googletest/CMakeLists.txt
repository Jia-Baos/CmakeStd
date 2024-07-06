cmake_minimum_required(VERSION 3.27)

project(googletest_mini_circle)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

aux_source_directory(. main_files)

add_executable(${PROJECT_NAME} ${main_files})

target_include_directories(${PROJECT_NAME} PUBLIC ../src/MiniCircle)

target_link_libraries(${PROJECT_NAME} PUBLIC mini_circle_static gtest gtest_main)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)
