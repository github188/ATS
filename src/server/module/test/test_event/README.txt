测试项目相关(TEST_EVENT)


1. 如何添加一个测试项目

	1. 新建文件，比如版本测试，添加:version_test.c
	2. 实现ATS_TestEvent对象中的相关接口，可以参照dummy_test.c
	3. 修改/etc/ats/下的相关配置文件，添加对应的测试项目test_event的配置。
	4. 在xml_parse.cpp中实现XML的解析。
	5. 把2中实现的测试项目添加到table.c中的表中。
	6. 重新编译，把编译好的库拷贝到/usr/lib/ats中，重新运行server端程序即可。
