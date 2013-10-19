                        ATS


1. 名词简单描述
    
    1. 总线：用来组织元素的结构，如ATS系统中的设备总线
    2. 设备：ATS测试系统中的测试单元。
    3. 测试驱动：设备测试的过程
    4. 测试驱动文件：对某款设备测试过程的文本化描述，常由单个或者多个测试项组成。
    4. 测试项：测试的最小单位，是对一次测试的描述
    5. 测试用例：测试项的输入数据，用于具体的测试。
    6. 测试用例集：测试用例的集合
    7. 设备检测器：用来检测设备，判断设备是否存在等。
    
    
 
2. 目录结构
.
|-- common                      gui/server通用部分源文件
|-- doc                         文档
|-- inc                         头文件目录
|-- libs                        库目录
|   |-- libosa                  osa库(https://github.com/lzk90s/libosa)
|   |   |-- inc                 osa头文件
|   |   `-- src                 osa源文件
|   |       |-- common          osa linux/windows公用源文件
|   |       |-- linux           osa linux源文件
|   |       `-- win32           osa windows源文件
|   `-- libsdk                  sdk库
|       |-- inc                 sdk头文件
|       |-- src
|       |-- tool
|       `-- xm_sdk              雄迈(XM.CO.Ltd.)sdk插件
|           |-- Release
|           `-- xm_sdk
|               |-- Debug
|               |-- inc         头文件
|               |-- lib         库文件
|               |-- Release
|               `-- res
|-- scripts                     系统构建脚本(https://github.com/lzk90s/build_system)
|   |-- core                    核心部分
|   |   |-- build               构建模板
|   |   `-- class               类模板
|   |-- doc                     文档
|   |-- templete                模板
|   `-- test
|       |-- include
|       |-- lib
|       |   |-- libfunc_a
|       |   |   `-- inc
|       |   |-- libfunc_b
|       |   |   `-- inc
|       |   |-- libfunc_c
|       |   `-- libfunc_d
|       `-- main
|-- src                         ATS源文件目录
|   |-- gui                     GUI部分(QT实现)
|   |   |-- build-debug
|   |   |   |-- debug
|   |   |   `-- release
|   |   |-- inc
|   |   `-- src
|   |       `-- images
|   `-- server                  SERVER部分
|       |-- conf                系统相关配置文件
|       |   `-- drv             测试驱动文本描述文件
|       |-- inc                 server端头文件
|       |   `-- module          模块头文件
|       |-- module              server端模块
|       |   |-- dev_prober      设备检测模块
|       |   |   `-- prober      设备检测器
|       |   |-- erp             erp模块
|       |   |-- report          报告模块
|       |   |-- sys             系统模块
|       |   `-- test            测试模块
|       |       `-- test_event  测试项插件
|       `-- src                 源文件
`-- utils                       其他文件
    |-- cJSON                   cjson库(gui和server通信时使用)
    |   `-- tests
    `-- tinyxml                 tinyXML库(解析配置使用)

64 directories
