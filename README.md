# 技术文档

## vscode中cmake插件的文档

[cmake插件链接](https://vector-of-bool.github.io/docs/vscode-cmake-tools/index.html)

## 扫描电脑上所有编译器

点击vscode左下角的工具包设置（cmake配置下），之后再跳出的框中点击扫描工具包，之后就获取电脑上所有的编译工具。

## 编译命令

### Windows

```
cmake -B build -G "MinGW Makefiles"

cmake --build build --config Release --target install
```

[Link](https://github.com/Jia-Baos/Notes/blob/master/CMake/cmake-command.md)

### Linux

```
sudo mkdir build && cd build

sudo cmake ..

sudo make

sudo make install
```

## git添加子模块

```
git submodule add https://github.com/google/benchmark.git 3rdparty/benchmark

git submodule add https://github.com/google/googletest.git 3rdparty/googletest
```

若出现错误信息`fatal: 'benchmark' already exists in the index`，则按下面方式删除记录后再重新添加即可。

```
git rm -r --cached 3rdparty/benchmark

git rm -r --cached 3rdparty/googletest
```

## Bugs

### bug1

在使用前面给的Linux编译命令后，使用vs-code中的快捷键编译提示没有权限

```
CMake Error: : System Error: Permission denied
```

推测原因为建立文件夹时没有使用```sudo```权限，使得用快捷键进行编译时没有写入权限，实测删除build文件夹后，重新编译其可

递归修改文件夹的权限目前无法解决上述问题，有待进一步探索（时间：2024-06-09 22：02）

```
sudo chmod -R 777 [Dir]
```

问题定位及解决方案：新建build文件夹及执行cmake命令时，不要使用```sudo```权限。

### bug2

下面CMake文件在编译代码时出现了错误，后面改变头文件所在文件夹的名称解决问题

[参考链接](https://blog.csdn.net/weixin_47468969/article/details/123311983)

```
cmake_minimum_required(VERSION 3.27)

project(event_bus)

message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "Project Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(event_bus)
# add_subdirectory(event_bus_utils) # 修改后

# 将源代码添加到此项目的可执行文件。
aux_source_directory(. main_files)
add_executable(${PROJECT_NAME} ${main_files})

# 链接库头文件路径
target_include_directories(${PROJECT_NAME} PUBLIC ./event_bus)

# 链接库文件夹
# 如果动态链接库和静态链接库同名，优先调用静态链接库
target_link_libraries(${PROJECT_NAME} PUBLIC event_bus_static)

install(TARGETS ${PROJECT_NAME}
        ARCHIVE DESTINATION lib/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME})

```
