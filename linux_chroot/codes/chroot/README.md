# chroot使用方法

chroot通过使用linux api中的`int chroot(char *path)`接口，模拟实现了简单的
chroot命令功能。

## 使用方法

```bash

# 使用cmake生成makefile文件
cmake .

```

```bash

# 使用make编译为程序
make

```

测试结果如下：

![chroot事例](../../images/chroot_test.png)
