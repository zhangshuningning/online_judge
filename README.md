# online_judge

负载均衡的在线oj系统

# 负载均衡

本系统将oj系统网页服务(oj_server)和在线编译服务(compile_server)分离，一般可以在一台服务器上启动oj_server服务，并同时在多台服务器上启动compile_server，oj_server在获取用户编译请求时，会选择向当前最空闲的编译服务器请求编译服务。

![在这里插入图片描述](https://img-blog.csdnimg.cn/75cb2f1400cf45c8b7964acaacc73fe0.png)



# Makefile

![在这里插入图片描述](https://img-blog.csdnimg.cn/7ba3b808b58340f98657398503cda1c4.png)

1. 在当前目录下执行

```shell
make
```

可执行文件*oj_server*和*compile_server*分别被存在**./oj_server**和**compile_server**路径下，如下图：

![在这里插入图片描述](https://img-blog.csdnimg.cn/1b35978e1ea849e2bd5c3e4da23f72e7.png)


![在这里插入图片描述](https://img-blog.csdnimg.cn/5edfd65c5a364f91becc30d7aad4f307.png)


2. 先执行**oj_server**再执行**compile_server**(需要开两个会话)

```shell
./oj_server #默认8080端口

./compile_server port
```



![在这里插入图片描述](https://img-blog.csdnimg.cn/4004ac4d674840918754aedf71abbca8.png)



![在这里插入图片描述](https://img-blog.csdnimg.cn/b6595aebb3f14d168114a1cc54b5cd90.png)

# 效果展示

![在这里插入图片描述](https://img-blog.csdnimg.cn/e2b49d84d72d4143b51a0e9c3474d0e3.png)

![在这里插入图片描述](https://img-blog.csdnimg.cn/40895b735b474edea933617e499f51a7.png)


![在这里插入图片描述](https://img-blog.csdnimg.cn/15de3b0765a542b48d3cffe7a0afa8ab.png)
