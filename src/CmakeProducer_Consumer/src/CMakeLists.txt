cmake_minimum_required(VERSION 3.27)

project(producerConsumer)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# 进入三方库文件夹
add_subdirectory(producerConsumer)

# 将源代码添加到此项目的可执行文件。
aux_source_directory(. main_files)
add_executable(${PROJECT_NAME} ${main_files})

# 链接库头文件路径
target_include_directories(${PROJECT_NAME}
       PUBLIC ./producerConsumer)

# 链接库文件
# 如果动态链接库和静态链接库同名，优先调用静态链接库
target_link_libraries(${PROJECT_NAME}
        PUBLIC
        producer_consumer_static)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})
