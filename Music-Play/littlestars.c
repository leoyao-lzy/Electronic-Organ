#include <msp430.h> 
int rym[10] = {1,262,294,330,349,392,440,494,523,196};
int puzi1[44] = {1,0,1,5,0,5,6,0,6,5,0,4,0,4,3,0,3,2,0,2,1,0,5,0,5,4,0,4,3,0,3,2,0,5,0,5,4,0,4,3,0,3,2,0};
//int puzi2[22] = {5,0,5,4,0,4,3,0,3,2,0,5,0,5,4,0,4,3,0,3,2,0};
void delay(unsigned int i)     //延时函数
{   unsigned int j;             //定义局部变量
    for (j=0; j<i; j++);
}
int main ( void )
{
    WDTCTL = WDTPW + WDTHOLD;       //关闭看门狗
        P2SEL |=BIT1+BIT4;              //置P2.1和 P2.4为定时器TA1的PWM输出引脚
        P2SEL2 &=~(BIT1+BIT4);              //置P2.1为比较器1的PWM输出引脚
        P2DIR |=BIT1+BIT4;          //置P2.4为比较器2的PWM输出引脚

        TA1CTL |=TASSEL0;   //选择ACLK为TA1计数时钟，ACLK使用上电复位设置，即外部晶振32768Hz
        //TA1CCR0=32767;            //设置PWM周期，周期= (TA1CCR0+1)*T =(TA1CCR0+1)/计数时钟频率
                //即输出的PWM波形频率=1/PWM周期=计数时钟频率/(TA1CCR0+1)
        TA1CCTL1|=OUTMOD1;  //置TA1比较器1的PWM输出为模式2： 计数到CCR1值翻转，到CCR0值置0
        //TA1CCR1=3277;             //置TA1比较器1设定值CCR1，TA1CCR1=TA1CCR0*(1-PWM波形占空比25%)

        //TA1CCTL2|=OUTMOD1;    //置比较器2的PWM输出为模式2： 计数到CCR2值翻转，到CCR0值置0
        //TA1CCR2=16383;            //置TA1比较器2设定值CCR2，TA1CCR2=TA1CCR0*(1-PWM波形占空比50%)

        TA1CTL |=TACLR+MC0; //置增计数方式，使计数器从0开始计数，计数到TA1CCR0后又从0计数。
       while(1)
       {
           int i = 0;
           if(i==0)
           {
             TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
             TA1CCR1=(int)(0.1*TA1CCR0);
             delay(0x6fff);
           }
           i++;
           if(i==1)
           {
             TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
             TA1CCR1=(int)(0.1*TA1CCR0);
             delay(0x50);
            }
           for(i=2;i<4;i++){
             TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
             TA1CCR1=(int)(0.1*TA1CCR0);
             delay(0x6fff);
                            }
           if(i==4)
           {
             TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
             TA1CCR1=(int)(0.1*TA1CCR0);
             delay(0x50);
           }
           for(i=5;i<7;i++){
             TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
             TA1CCR1=(int)(0.1*TA1CCR0);
             delay(0x6fff);
           }
           if(i==7)
           {
             TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
             TA1CCR1=(int)(0.1*TA1CCR0);
             delay(0x50);
           }
           for(i=8;i<12;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
           }
           if(i==12)
          {
               TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0x50);
          }
           for(i=13;i<15;i++){
               TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0x6fff);
                      }
           if(i==15)
         {
              TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
              TA1CCR1=(int)(0.1*TA1CCR0);
              delay(0x50);
         }
           for(i=16;i<18;i++){
              TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
              TA1CCR1=(int)(0.1*TA1CCR0);
              delay(0x6fff);
                             }
           if(i==18)
         {
              TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
              TA1CCR1=(int)(0.1*TA1CCR0);
              delay(0x50);
         }
           for(i=19;i<23;i++){
              TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
              TA1CCR1=(int)(0.1*TA1CCR0);
              delay(0x6fff);
                              }
           if(i==23)
                    {
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x50);
                    }
           for(i=24;i<26;i++){
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x6fff);
                                       }
                      if(i==26)
                      {
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x50);
                      }
                      for(i=27;i<29;i++){
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x6fff);
                      }
                      if(i==29)
                      {
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x50);
                      }
                      for(i=30;i<34;i++){
                       TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                       TA1CCR1=(int)(0.1*TA1CCR0);
                       delay(0x6fff);
                      }
                      if(i==34)
                     {
                          TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                          TA1CCR1=(int)(0.1*TA1CCR0);
                          delay(0x50);
                     }
                      for(i=35;i<37;i++){
                          TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                          TA1CCR1=(int)(0.1*TA1CCR0);
                          delay(0x6fff);
                                 }
                      if(i==37)
                    {
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x50);
                    }
                      for(i=38;i<40;i++){
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x6fff);
                                        }
                      if(i==40)
                    {
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x50);
                    }
                      for(i=41;i<44;i++){
                                               TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
                                               TA1CCR1=(int)(0.1*TA1CCR0);
                                               delay(0x6fff);
                                                              }
           /*if(m ==0)
                      {
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x6fff);
                      }
                      i++;
                      if(m ==1)
                      {
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x50);
                       }
                      for(m=2;m<4;m++){
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x6fff);
                                       }
                      if(m==4)
                      {
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x50);
                      }
                      for(m=5;m<7;m++){
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x6fff);
                      }
                      if(m==7)
                      {
                        TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                        TA1CCR1=(int)(0.1*TA1CCR0);
                        delay(0x50);
                      }
                      for(m=8;m<12;m++){
                       TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                       TA1CCR1=(int)(0.1*TA1CCR0);
                       delay(0x6fff);
                      }
                      if(m==12)
                     {
                          TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                          TA1CCR1=(int)(0.1*TA1CCR0);
                          delay(0x50);
                     }
                      for(m=13;m<15;m++){
                          TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                          TA1CCR1=(int)(0.1*TA1CCR0);
                          delay(0x6fff);
                                 }
                      if(m==15)
                    {
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x50);
                    }
                      for(m=16;m<18;m++){
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x6fff);
                                        }
                      if(m==18)
                    {
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x50);
                    }
                      for(m=19;m<22;m++){
                         TA1CCR0=(int)(((double)32768/(double)rym[puzi2[m]])-1);
                         TA1CCR1=(int)(0.1*TA1CCR0);
                         delay(0x6fff);
                                         }*/
       };
}
