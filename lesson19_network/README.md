# 网络基础
## MAC地址
MAC地址是12位16进制数，48位二进制数组成，其独一无二。它用于标识一块网卡，网卡处于OSI7层模型中的数据链路层设备，主要用于数据的封装与解封装、链路管理、数据编码与译码等

## IP地址
ip地址是逻辑地址，32位二进制数组成，分成4个八位二进制数。所以我这边简述其分为4段，而ip地址的类别划分也是由几段网络号划分，A类一段网络号，即255.0.0.0作为子网掩码，以此类推B类两段网络号，C类三段网络号。常见C类地址，三段网络号，一段主机号，最后一个网段在不划分子网的情况下可以容纳254台主机，全0和全1的主机号去除，全0代表网络号，全1代表广播地址

## 端口
端口由16位2进制数组成，共65536个，0-65535

## OSI七层模型
由上至下为：</br>
应用层：用户和应用程序交互的接口 </br>
表示层：数据的格式的转化和数据的加密，即将计算机能识别的转化为人能识别的，如图片、语音等</br>
会话层: 建立、管理和维护会话，通过传输层简历数据传输的通路</br>
传输层：传输就会涉及到协议，所以这一层主要与协议相关,如tcp、udp，主要将从下层接收的数据进行分段和传输，到达目的地址后进行重组，这一层数据叫做段</br>
网络层：和网络相关的主要是ip地址，这一层主要进行逻辑地址的寻址，在位于不同地理位置的的网络中，为两个主机提供链接和路径选择，管理链接和ip息息相关。</br>
数据链路层：上一层为网络ip相关，那么这一层就与硬件地址相关（MAC）组合数据为帧，用MAC地址访问介质</br>
物理层：主要就是数模转换、模数转换，毕竟需要将01数据转换为高低电平，数据叫做bit</br>