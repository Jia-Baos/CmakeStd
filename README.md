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