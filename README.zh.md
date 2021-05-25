Tars-Test单元测试说明
----
Tars-Test单元测试的开发主要基于GoogleTest测试框架，关于GoogleTest的具体细节请见[官方说明文档](https://github.com/abseil/googletest/blob/master/googletest/docs/primer.md)。Tars-Test中目前提供的用例已经覆盖了RPC服务的基本场景。

1、环境搭建
----
由于Tars-Test以GoogleTest为基础，因此需要安装GoogleTest及生成覆盖率的相关文件，如下命令：
```c
[sudo] yum install gtest-devel lcov
```
2、使用说明
----

在tarscpp/build下编译:
```
cmake .. -DONLY_LIB=OFF
make -j8
make run-unittest
```
<!-- 进入tars-uniittest下的script文件夹内，运行run_test.sh脚本,即可输出用例运行结果：
```c
cd ./tars-unittest/script/
./run_test.sh 
```
若想得到覆盖率结果，可加入运行选项-l，系统将在tars-test下生成result文件夹，其中即包含了覆盖率文件。如下：
```c
./run_test.sh -l
```
目前主要统计servant代码的覆盖率，其他的待完善
tips: 统计覆盖率时，需要修改编译tarscpp的编译选项(在tarscpp/CMakelists.txt中修改)，添加-fprofile-arcs -ftest-coverage选项，然后重新编译tarscpp代码，以便后续统计覆盖率时能生成gcno和gcda文件

还可以根据具体需求选择选项：-c为测试用例全量编译，-a为测试用例和框架代码全量编译，-d为gdb方式运行等。 -->

3、测试用例添加
---
当前工程中的测试用例代码主要在testcode文件夹中，后续可根据需要在其中添加文件和测试用例。新的测试用例可以复用现有的OBJ、服务和应用，如果需要部署新的服务或OBJ，可在protocol文件夹中添加服务端的相关代码，新增服务端的配置文件可加入到conf文件夹中。
