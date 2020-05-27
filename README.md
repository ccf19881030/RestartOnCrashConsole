# RestartOnCrashConsole

#### 介绍
基于Win32的VC++控制台程序，监控外部应用程序，定时监控需要启动的进程，防止进程挂掉。
具体可结合本人的CSDN博客[VC++定时检测进程，被检测进程挂掉后启动](https://ccf19881030.blog.csdn.net/article/details/106387094)看。

#### 软件架构
软件架构说明
* 最近使用MFC写一个监控进程的后台程序，需要实现以下的功能：
1、遍历被监控的进程列表，定时（比如1分钟）检测进程列表，如果某个需要被监视的进程未运行，则启动它。
2、防止假死-使用心跳机制(UDP实现后台监控进程与被监控进程的心跳进制)
    - a、被检测进程定时，比如说每隔5秒给后台监控进程发送一个包含进程名称、进程所在绝对路径、发送心跳的时间戳等信息，后台监控进程定时检测遍历每个进程，如果该进程连续3次如15秒没有给监控进程发送心跳包，则说明该进程因为异常情况比如假死了，监控进程则先杀掉该进程然后再重启它。关于心跳包，使用JSON格式或者自定义的字符串格式都行，比如：@@AppName=UDPClientDemo;AppPath=E:\UDPClientDemo\UDPClientDemo.exe;CurrentTime=2020-05-26 10:29:00##
定义好头和尾部以及进程信息。
有些被检测程序死掉时，程序崩溃了，它就弹出一个错误对话框，如下图所示，并且如果不关掉掉这个框，程序就永远死在这个窗口上，不会退出，进程ID也不会变成0，那么就不能通过检测进程ID来判断程序是否崩溃。所以现在必须让程序崩溃后直接退出而不是死在错误窗口上。
    - b、被检测进程正常退出，不需要被检测时，可以给监控进程发送一条消息，说明该进程不需要被守护了。后台监控进程会在内存或者配置文件中维护一个被检测进程的映射表，将不需要检测的进程从该表中移除或者置某个字段(isDetected)为false即可。
为了简单起见，先编写一个基于Win32的控制台应用程序。


#### 安装教程

1.  系统采用Windows10系统，VS2017作为开发工具
2.  xxxx
3.  xxxx

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 码云特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5.  码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
