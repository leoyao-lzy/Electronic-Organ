#include "msp430.h"
int rym[9] = {1,262,294,330,165,196,220,247,440};
int puzi1[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,6,6};  //《闪亮的日子》谱子第一行
int puzi2[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,4,4};  //《闪亮的日子》谱子第二行
int puzi3[24] = {3,3,3,2,1,2,3,3,3,3,8,8,3,3,3,2,1,2,3,3,3,3,0,1};  //《善良的日子》第三行谱子
int puzi4[24] = {2,2,2,2,2,3,6,6,6,6,0,6,1,1,1,1,1,2,7,7,7,7,4,4};  //《善良的日子》第四行谱子
int puzi5[24] = {3,3,3,2,1,2,3,3,3,3,0,8,3,3,3,2,1,2,3,3,3,3,0,1};  //《善良的日子》第五行谱子
int puzi6[23] = {2,2,2,2,2,3,6,6,6,6,0,5,6,6,6,1,7,6,0,6,6,6,6};    //《善良的日子》第六行谱子

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
        for(i=0;i<24;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi1[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
        }
        for(i=0;i<24;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi2[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
        }
        for(i=0;i<24;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi3[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
        }
        for(i=0;i<24;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi4[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
        }
        for(i=0;i<24;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi5[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
        }
        for(i=0;i<18;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi6[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
        }
        if(i==18)
        {
            TA1CCR0=(int)(((double)32768/(double)rym[puzi6[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x50);
        }
        for(i=19;i<23;i++){
            TA1CCR0=(int)(((double)32768/(double)rym[puzi6[i]])-1);
            TA1CCR1=(int)(0.1*TA1CCR0);
            delay(0x6fff);
        }
    };
}
