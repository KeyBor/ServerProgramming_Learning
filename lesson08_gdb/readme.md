## GDB调试
使用gdb调试，需要在生成可执行文件时使用 -g 参数
如：
```
gcc main.c -o test -g
```

一些gdb的使用
```
#启动和退出
gdb 可执行程序
quit

#给程序设置参数和获取设置的参数
set args 10 20
show args

#gdb使用帮助
help

#设置断点
b/break 行号
b/braek 函数名
b/braek 文件名:行号
b/break 文件名:函数


#查看断点
i/info b/break

#删除断点
d/del/delete 断点编号

#设置断点无效
dis/disbale 断点编号

#设置断点生效
ena/enable 断点编号

#设置条件断点
b/break 10 if i==5


#运行GDB程序
start（程序停在第一行）
run（遇到断点才停）

#继续运行，到下一个断点停
c/continue

#向下执行一行代码（不会进入函数体）
n/next

#变量操作
p/print 变量名（打印变量值）
ptype 变量名（打印变量类型）

#向下单步调试（遇到函数进入函数体）
s/step
finish（跳出函数体）

#自动变量操作
display num（自动打印指定变量的值）
i/info display
undisplay 编号

#其他操作
set var 变量名=变量值
until （跳出循环）
```