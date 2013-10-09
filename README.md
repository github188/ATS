Auto Test System Framework
================

一、介绍

    1. gui: ATS系统前端GUI部分
    2. server: ATS系统后端服务部分



二、使用方法
    
    gui部分：
    
    1. 进入gui/src目录，执行
    2. qmake && make即可生成GUI可执行程序.
    3. 运行生成的gui程序
    
    
    server部分：
    
    1. Linux终端中，运行source ./scripts/envsetup.sh
    2. 运行make即可生成服务端elf可执行程序。
    3. 拷贝out/{version}-{type}/{host/target}/lib/目录下的动态库到/usr/lib/ats/目录下。
    4. 运行./out/{version}-{type}/{host/target}/bin/main即可运行。


三、其他信息

    1. copyright : HangZhou TuoAn @ 2013
