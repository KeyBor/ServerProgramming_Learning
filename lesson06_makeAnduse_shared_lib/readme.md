## 在linux环境下创建并使用动态库
在linux下动态库的后缀为.so，eg，libxxx.so(lib是固定前缀，xxx为库的名字，.so为后缀)
</br>
windows下动态库为libxxx.dll文件</br>
**gcc在链接时，不会将动态库文件打包进可执行文件中，程序启动后，动态库文件也将被加载到内存中，通过ldd命令（list dynamic dependencies）检查动态库依赖关系**

## 动态库的制作
gcc得到.o文件，得到和位置无关的代码</br>
```
gcc -c -fpic a.c b.c
```

### 构建动态库
```
gcc -shared a.o b.o -o libxxx.so
```


## 使用动态库构建可执行文件
```
gcc -c main.c -o main -I ./include -L ./lib -l calc
```
会生成可执行文件main，但是直接运行会报错，无法加载动态库文件

## 运行可执行文件时，会通过动态载入器寻找动态库的绝对路径，并将其载入到内存中
1、修改环境变量的方式
```
env   #查看linux环境下所有的环境变量

//export是添加环境变量的命令，但是是临时配置的，$后面的是获取当前变量值，：进行分割，后面添加lib当前的路径，让动态载入器可以找到动态库

export LD_LIBRARY_PATH = $LD_LIBRARY_PATH:动态库绝对路径

# 输出当前变量的值
echo $LD_LIBRARY_PATH
```

上述方式是临时配置，接下来阐述用户级别的配置：
修改/home/.bashrc即可，将上述的临时的export命令写入文件中</br>
写入后要使其生效
```
. .bashrc
或
source .bashrc
```


接下来阐述系统级别的修改：
修改/etc/profile文件，跟上述用户级写入的东西都是一致的，只是写入的地方不一致，最后都需要用source使其生效。

2、修改/etc/ld.so.cache文件
这个方式需要间接操作，因为这个文件是二进制文件，所以需要去修改：
/etc/ld.so.conf文件，直接将动态库路径添加进去，后面需要更新配置，使用
```
sudo ldconfig
```


3、将动态库文件放入/lib/，或/usr/lib/文件夹下即可（不建议)


其实上述这些方法也是对应于windows下配置环境变量或者添加库到系统目录下等操作，本质是一样的，都是为了让动态载入器能够通过配置去找到库的路径并加载