[点我查看中文版](README.zh.md)

## Description of Tars-Test
The development of Tars-Test(unit testcase of Tarscpp) is mainly based on the GoogleTest test framework. For details on GoogleTest, please see [Official Documentation] (https://github.com/abseil/googletest/blob/master/googletest/docs/primer.md) .   
The current testcases have covered the basic scenario of the RPC service.

### Dependent environment
Since Tars-Test is based on GoogleTest, you need to install GoogleTest and generate related files for coverage, as follows:  

```c
[sudo] yum install gtest-devel lcov
```
### instructions for use


在tarscpp/build下编译:
```
cmake .. -DONLY_LIB=OFF
make -j8
make run-unittest
```
<!-- 
Enter the script folder under unittest(Tars-Test) and run the run_test.sh script to output the use case results:    

```c
cd ./tars-unittest/script/
./run_test.sh
```
If you want to get the coverage result, you can add the run the script with option '-l', the system will generate the result folder under unittest(Tars-Test), which contains the coverage file. as follows:  

```c
./run_test.sh -l
```
At present, we support the coverage statistics of servant's code mainly, the rest part is to be improved.  
Tips:  
When calculating the coverage, you need to modify the compile option before compiling tarscpp (modified in tarscpp/CMakelists.txt), add the -fprofile-arcs -ftest-coverage option, and then recompile the tarscpp code so that gcno and gcda files can be generated when you run the testcases.  -->

### How to add one testcase 
The test case code in the current project is mainly in the testcode folder, and subsequent files and test cases can be added as needed. New test cases can reuse existing OBJs, services, and applications. If you need to deploy new services or OBJs, you can add services to the protocol folder. Related code, the new server configuration file can be added to the conf folder.
