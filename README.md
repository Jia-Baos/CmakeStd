# 使用指南

## 平台

在Windows10下采用Debug模式进行编译

## 编译命令

```C++
cmake -B build -G "MinGW Makefiles"

cmake --build build --config Debug --target install
```

[Link](https://github.com/Jia-Baos/Notes/blob/master/CMake/cmake-command.md)

## 删除本地分支和远程分支

```
git branch -d master
git push origin -d master
```
