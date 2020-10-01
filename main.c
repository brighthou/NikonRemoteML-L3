#include<reg52.h>
#include<intrins.h>

sbit LED=P1^0;            //设置红外LED发射引脚为P0.0口
sbit KEY=P3^2;            //设置红外LED发射开关为P3.2口（外部中断0）

void Delay4us()            //4us延时子函数@12.000MHz
{                  //因延时时间极短，无法通过下方的DelayUs2x实现
}

void DelayUs2x(unsigned char t)    //2us级延时子函数@12.000MHz
{   
  while(--t);
}

void DelayMs(unsigned char t)    //ms级延时子函数@12.000MHz
{                  //本函数需先声明上方2us级延时子函数后才能使用
  while(t--)
  {
    DelayUs2x(245);
    DelayUs2x(245);
  }
}


void exint0() interrupt 0           //外部中断0服务子函数，中断号0，中断位置0003H
{                  //以下是生成红外遥控脉冲的全过程：
  while(1)            //死循环，见71行，只有KEY松开后才能跳出中断，
  {                //便于实现连拍动作
    unsigned int j=158;
    while(j)          //这个循环产生79个38KHz红外脉冲周期，变化158次
    {              //大约耗时2毫秒。整个脉冲时序请参阅红外时序图
      LED=!LED;
      Delay4us();
      j--;
    }
    LED=1;            //根据硬件设计，P1.0在低电平时红外发射管点亮，
    DelayMs(28);        //此时熄灭红外发射管并延时28ms
    j=30;
    while(j)          //这个循环产生15个38KHz红外脉冲周期，变化30次
    {                           //大约耗时400微秒
      LED=!LED;
      Delay4us();
      j--;
    }
    LED=1;            //熄灭红外发射管
    DelayMs(1);          //延时1580微秒
    DelayUs2x(255);
    DelayUs2x(17);
    j=30;
    while(j)
    {
      LED=!LED;
      Delay4us();
      j--;
    }
    LED=1;
    DelayMs(3);          //延时3580微秒
    DelayUs2x(255);
    DelayUs2x(19);
    j=30;
    while(j)
    {
      LED=!LED;
      Delay4us();
      j--;
    }
    LED=1;            //红外遥控信号发射结束
    DelayMs(5);          //延时5毫秒，便于将两个红外遥控信号明显区分开
    if(KEY==1)          //如果按键没有松开，继续发送红外遥控信号
      return;          //如果按键松开了，跳出中断服务函数
  }
}

void main()
{
  IT0 = 1;                        //设置外部中断0下降沿触发
  EX0 = 1;                        //使能外部中断0
  EA = 1;                         //打开中断总开关
  while (1);            //单片机工作主循环，防止程序跑飞
}
