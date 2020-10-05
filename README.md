# NikonRemoteML-L3
A DIY camera remote control SCM program using C51 language. / 使用C51语言实现的一个相机遥控单片机程序。

## FILES / 文件内容
#### main.c
Source code / 源代码

#### nikon_remote_init.hex
The compiled machine code file used for SCM Burning / 编译的用于单片机烧写的十六进制机器码文件

#### CircuitDiagram.jpg
电路连接图

## Circuit Connections / 电路连接方法
Connect the SCM minimum sys normally;

Connect the Pin 1.1 with the IR LED cathode;

Connect the Pin 3.2 with a button switch;

View the file "CircuitDiagram.jpg" for detailed connection method.



正常连接单片机最小系统

P1.1引脚接红外发光二极管阴极

P3.2引脚接按键开关

具体连接方法参阅CircuitDiagram文件
