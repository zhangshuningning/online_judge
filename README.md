# online_judge

负载均衡的在线oj系统

# 负载均衡

本系统将oj系统网页服务(oj_server)和在线编译服务(compile_server)分离，一般可以在一台服务器上启动oj_server服务，并同时在多台服务器上启动compile_server，oj_server在获取用户编译请求时，会选择向当前最空闲的编译服务器请求编译服务。

![image-20230612232229070](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612232229070.png)

# Makefile

![image-20230612232346029](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612232346029.png)

1. 在当前目录下执行

```shell
make
```

可执行文件*oj_server*和*compile_server*分别被存在**./oj_server**和**compile_server**路径下，如下图：

![image-20230612232828865](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612232828865.png)

![image-20230612232854476](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612232854476.png)

2. 先执行**oj_server**再执行**compile_server**(需要开两个会话)

```shell
./oj_server #默认8080端口

./compile_server port
```



![image-20230612233318774](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612233318774.png)



![image-20230612233340337](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612233340337.png)

# 效果展示

![image-20230612233415016](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612233415016.png)

![image-20230612233531789](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612233531789.png)

![image-20230612233750012](C:\Users\49555\AppData\Roaming\Typora\typora-user-images\image-20230612233750012.png)









