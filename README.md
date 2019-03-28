# cpp 调用
> 注：代码还有问题
+ darknet 生成链接库，加到 cmakefile.list 中编译调用程序；
+ main() 函数调用定义在 src/detect_obj.cpp 中的两个函数：
  + load_net() 加载网络
  + to_detection() 进行检测
+ 问题：
  + ① `detect_obj.cpp` 中读取网络层信息失败 `l_last = get_layer(net, net->n-1);`，所以在下面的程序中用 80 代替的 `l_last.classes`，其实网络加载并没有问题，只是在 cpp 程序中读取有问题；
  + ② `get_layer()` 函数是我在 `darknet/src/network.c` 中添加的读取网络层信息的函数，在 cpp 文件中能读取但后面会报错 `Segmentation fault (core dumped) `，所以注释掉了没用，还不知道怎么解决
  
---
2019.03.28
wuyanminmax@gmail.com
