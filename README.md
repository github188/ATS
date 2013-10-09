Auto Test System Framework
================

一、介绍

    1. gui: ATS系统前端GUI部分
    2. server: ATS系统后端服务部分



二、使用方法
    
    A. 准备
    
        1. 编译前，请保证系统中有 GNU/Make (>= 3.81), Mingw32(for windows) 或者 GCC (for linux).
    
    B. GUI部分：
    
        1. 进入gui/src目录，执行
        2. qmake && make即可生成GUI可执行程序.
        3. 运行生成的gui程序
    
    C. SERVER部分：
    
        1. Linux终端中，运行source ./scripts/envsetup.sh
        2. 运行make即可生成服务端elf可执行程序。
        3. 拷贝out/{version}-{type}/{host/target}/lib/目录下的动态库到/usr/lib/ats/目录下。
        4. 运行./out/{version}-{type}/{host/target}/bin/main即可运行。


三、多平台编译


    1. 系统支持跨平台，如果需要在linux下运行，则编译前，修改工程根目录下的config.mk文件如下
    把 TOOL=MINGW32 一行修改为 TOOL=GCC，保存修改，重新make即可。同理，如果需要在WINDOWS下运行，则
    把 TOOL=GCC 一行修改为 TOOL=GCC，重新make即可。
    
    2. 由于厂家提供的部分SDK只支持单个平台，所以，如果编译出错，请检查是否是厂家的SDK和系统的平台不一样。
        
        
四、其他信息

    1. copyright : HangZhou TuoAn @ 2013
