## 在linux环境下制作静态库
需要通过gcc编译，汇编源文件为二进制文件，再使用ar（archive）对.o文件进行打包为.a文件
```
gcc -c add.c sub.c div.c mult.c
```
这对对于每一个源文件生成一个.o后缀的文件
然后我们需要用ar命令进行打包
```
ar rcs libxxx.a xxx.o xxx.o xxx.o
```
**r - 将文件传入备存文件中 </br>**
**c - 建立备存文件 </br>**
**s - 索引 </br>**
