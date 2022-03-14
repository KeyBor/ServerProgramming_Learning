## 在linux环境下使用静态库
根据上一节，我们打包完静态库libcalc.a后（lib是固定前缀，calc是库名，linux下.a为静态库，windows下.lib为静态库）</br>
根据library的文件目录，我们可以构建使用静态库的可执行文件</br>
**gcc在链接时，会将静态库文件打包到可执行文件中**
```
gcc main.c -o app -I ./include -l calc -L ./lib
```
其中</br>
-I 代表头文件的目录 </br>
-l 代表要链接的库名称 </br>
-L 代表要链接的包含静态库的路径 </br>