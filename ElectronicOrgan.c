#include <msp430.h> 
int flag=0;      //用于选择播放音乐
int key=0;       //用于弹奏时选择音符
int convert =0;  //用于模式切换
int a;           //a=1时为播放，a=2时为弹奏
//《两只老虎》相关数组
const int TwoTigers_rym[10] = {1,262,294,330,349,392,440,494,523,196};                              //《两只老虎》音符频率
const int TwoTigers1[18] = {1,2,3,1,0,1,2,3,1,3,4,5,5,3,4,5,5,0};                                   //《两只老虎》第一行谱子
const int TwoTigers2[35] = {5,6,5,4,3,3,1,1,5,6,5,4,3,3,1,1,0,1,1,9,9,1,1,1,1,0,1,1,9,9,1,1,1,1,0}; //《两只老虎》第二行谱子
//《一闪一闪亮晶晶》相关数组
const int LittleStars_rym[10] = {1,262,294,330,349,392,440,494,523,196};                            //《一闪一闪亮晶晶》音符频率
const int LittleStars1[44] = {1,0,1,5,0,5,6,0,6,5,0,4,0,4,3,
                              0,3,2,0,2,1,0,5,0,5,4,0,4,3,0,3,2,0,5,0,5,4,0,4,3,0,3,2,0};//《一闪一闪亮晶晶》谱子
//《闪亮的日子》相关数组
const int ShiningDays_rym[9] = {1,262,294,330,165,196,220,247,440};
const int ShiningDays1[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,6,6};  //《闪亮的日子》谱子第一行
const int ShiningDays2[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,4,4};  //《闪亮的日子》谱子第二行
const int ShiningDays3[24] = {3,3,3,2,1,2,3,3,3,3,8,8,3,3,3,2,1,2,3,3,3,3,0,1};  //《闪亮的日子》第三行谱子
const int ShiningDays4[24] = {2,2,2,2,2,3,6,6,6,6,0,6,1,1,1,1,1,2,7,7,7,7,4,4};  //《闪亮的日子》第四行谱子
const int ShiningDays5[24] = {3,3,3,2,1,2,3,3,3,3,0,8,3,3,3,2,1,2,3,3,3,3,0,1};  //《闪亮的日子》第五行谱子
const int ShiningDays6[24] = {2,2,2,2,2,3,6,6,6,6,0,5,6,6,6,1,7,6,0,6,6,6,6,0};  //《闪亮的日子》第六行谱子
//函数定义部分
void delay(unsigned int i);
void TwoTigers_play();
void LittleStars_play();
void ShiningDays_play();
void TwoTigers_show();    //L4亮一次
void LittleStars_show();  //L4亮两次
void ShiningDays_show();  //L4亮三次
//蓝牙通信部分
void UARTA0_init( );
void TxtOut(char string[]);     //输出字符串函数
void TxtIn(char string[], int num); //输出字符串函数
int  CodeCheck(char buffer[],char Code[],int num);  //检查输入密码是否正确函数
char buffer[11]="12345678\r\n\0";
char code[] = "12345678";     //进入电子琴密码
char welcome[]="Please input password>>>\r\n\0";
char sorry[]="Sorry!\r\n\0";
char retry[]="Please try again!\r\n\0";
char ok[]="Welcome!\r\n\0";
char TwoTigers[]="Playing <Two Tigers>\r\n\0";
char LittleStars[]="Playing <Twikle Twikle Little Star>\r\n\0";
char ShiningDays[]="Playing <Shining Days>\r\n\0";
char Choices[]="Please select a song that you want to play: \r\n1-<Two Tigers>\r\n2-<Twikle Twikle Little Star>\r\n3-<Shining Days>\r\n\0";
char one[]="1";
char two[]="2";
char three[]="3";
char nosongs[]="Error entering information.\r\n\0";
int CheckPoint = 0 ;
unsigned char j;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    //设置定时器TA1
    P2SEL |=BIT1;              //置P2.1为定时器TA1的PWM输出引脚
    P2SEL2 &=~BIT1;
    P2DIR |=BIT1;              //置P2.1为比较器1的PWM输出引脚
    TA1CTL |=TASSEL0;          //选择ACLK为TA1计数时钟，ACLK使用上电复位设置，即外部晶振32768Hz
    TA1CCTL1|=OUTMOD1;         //置TA1比较器1的PWM输出为模式2： 计数到CCR1值翻转，到CCR0值置0
    TA1CTL |=TACLR+MC0;        //置增计数方式，使计数器从0开始计数，计数到TA1CCR0后又从0计数
    //中断相关设置
    P1SEL &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);//P1.0~P1.7(除P1.1和P1.2外）分别和K1~K8相连（除K2,K3外）
    P1SEL2 &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1OUT |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1REN |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1DIR &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1IES |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1IFG &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1IE |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P2SEL &=~(BIT0+BIT2+BIT4+BIT5);//P2.0和外部按键Kb连接（切换模式功能），P2.2和外部按键Ka连接（低音发声功能），P2.4和K2相连，P2.5和K3相连
    P2SEL2 &=~(BIT0+BIT2+BIT4+BIT5);
    P2OUT |=(BIT0+BIT2+BIT4+BIT5);
    P2REN |=(BIT0+BIT2+BIT4+BIT5);
    P2DIR &=~(BIT0+BIT2+BIT4+BIT5);
    P2IES |=(BIT0+BIT2+BIT4+BIT5);
    P2IFG &=~(BIT0+BIT2+BIT4+BIT5);
    P2IE |=(BIT0+BIT2+BIT4+BIT5);
    _EINT();    //总中断允许
    //控制LED灯端口设置（P2.3-L4）
    P2SEL &=~BIT3;
    P2SEL2 &=~BIT3;
    P2OUT |=BIT3;
    P2DIR |=BIT3;
    //蓝牙通信
    UARTA0_init( );                 //初始化串口
    //进入时设置初始密码
    j=0;
    TxtOut(welcome);
    TxtIn(buffer,8);
    CheckPoint = CodeCheck(buffer,code,8);
    if(CheckPoint==1){TxtOut(ok);}
    else if(CheckPoint==0){
     do{
        TxtOut(sorry);
        TxtOut(retry);
        TxtOut(welcome);
        TxtIn(buffer,8);
        CheckPoint = CodeCheck(buffer,code,8);
       }while(CheckPoint!=1);
        TxtOut(ok);
    }
    //初始设置部分到此结束
    while(1)
    {
        //歌曲播放模式
        if(flag == 1)   //播放《两只老虎》
        {
          TwoTigers_show();
          TxtOut(TwoTigers);
          TwoTigers_play();
          flag=0;
        }
        else if (flag == 2)//播放《一闪一闪亮晶晶》
        {
          LittleStars_show();
          TxtOut(LittleStars);
          LittleStars_play();
          flag=0;
        }
        else if (flag == 3)//播放《闪亮的日子》
        {
          ShiningDays_show();
          TxtOut(ShiningDays);
          ShiningDays_play();
          flag=0;
        }
        else if (flag == 4)//蓝牙控制播放
        {
          TxtOut(Choices);
          TxtIn(buffer,1);
          CheckPoint = CodeCheck(buffer,one,1);
          if (CheckPoint==1){    //蓝牙控制播放《两只老虎》
              TwoTigers_show();
              TxtOut(TwoTigers);
              TwoTigers_play();
              flag=0;
          }
          else if (CheckPoint==0){
              CheckPoint = CodeCheck(buffer,two,1);
              if(CheckPoint==1){     //蓝牙控制播放《一闪一闪亮晶晶》
                  LittleStars_show();
                  TxtOut(LittleStars);
                  LittleStars_play();
                  flag=0;
              }
              else if(CheckPoint==0){
                  CheckPoint = CodeCheck(buffer,three,1);
                  if(CheckPoint==1){     //蓝牙控制播放《闪亮的日子》
                      ShiningDays_show();
                      TxtOut(ShiningDays);
                      ShiningDays_play();
                      flag=0;
                  }
                  else if(CheckPoint==0){   //输入有误
                      TxtOut(nosongs);
                  }
              }
          }
        }
        //按键弹奏模式
        else if(key==1)
           {
               TA1CCR0=(int)(((double)32768/(double)262)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==2)
           {
               TA1CCR0=(int)(((double)32768/(double)294)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==3)
           {
               TA1CCR0=(int)(((double)32768/(double)330)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==4)
           {
               TA1CCR0=(int)(((double)32768/(double)349)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==5)
           {
               TA1CCR0=(int)(((double)32768/(double)392)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==6)
           {
               TA1CCR0=(int)(((double)32768/(double)440)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==7)
           {
               TA1CCR0=(int)(((double)32768/(double)494)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==11)
           {
               TA1CCR0=(int)(((double)32768/(double)523)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==12)  
           {
               TA1CCR0=(int)(((double)32768/(double)587)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==13)
           {
               TA1CCR0=(int)(((double)32768/(double)659)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==14)
           {
               TA1CCR0=(int)(((double)32768/(double)698)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==15)
           {
               TA1CCR0=(int)(((double)32768/(double)784)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==16)
           {
               TA1CCR0=(int)(((double)32768/(double)880)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==17)
           {
               TA1CCR0=(int)(((double)32768/(double)988)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==21)
           {
               TA1CCR0=(int)(((double)32768/(double)247)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==22)
           {
               TA1CCR0=(int)(((double)32768/(double)220)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==23)
           {
               TA1CCR0=(int)(((double)32768/(double)196)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==24)
           {
               TA1CCR0=(int)(((double)32768/(double)175)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==25)
           {
               TA1CCR0=(int)(((double)32768/(double)165)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==26)
           {
               TA1CCR0=(int)(((double)32768/(double)147)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }
           else if(key==27)
           {
               TA1CCR0=(int)(((double)32768/(double)131)-1);
               TA1CCR1=(int)(0.1*TA1CCR0);
               delay(0xff);
               key = 0;
           }

    }
    //return 0;
}

#pragma  vector=PORT1_VECTOR
#pragma  vector=PORT2_VECTOR
__interrupt  void port_ISR( ) //中断子程序
{
    if((P2IFG&BIT0)!=0)     // 判断是P2.0上的中断（Ka是否按下）
 {
     convert = convert+1;
     P2IFG &=~BIT0;
 }
   if (convert%2==1){a=1;}   // convert是奇数
   else if(convert%2==0){a=2;}//convert是偶数
 if(a==1)     //歌曲播放模式
   {
     if ( (P1IFG&BIT0)!=0 )  //判断是P1.0上的中断
    {
        flag = 1;           //对应播放《两只老虎》
        P1IFG &=~BIT0;
    }
    else if((P2IFG&BIT4)!=0)//判断是P2.6上的中断
    {
        flag = 2;           //对应播放《一闪一闪亮晶晶》
        P2IFG &=~BIT4;
    }
    else if((P2IFG&BIT5)!=0)//判断是P2.5上的中断
    {
        flag = 3;           //对应播放《闪亮的日子》
        P2IFG &=~BIT5;
    }
    else if ( (P1IFG&BIT3)!=0 )  //判断是P1.3上的中断
    {
         flag = 4;           //蓝牙控制播放模式
         P1IFG &=~BIT3;
    }
   }
 if(a==2)      //按键弹奏模式
 {
     if ((P1IFG&BIT0)!=0)  //判断是P1.0上的中断
     {
         key = key+1;
         P1IFG &=~BIT0;
     }
     else if((P2IFG&BIT4)!=0)//判断是P1.1上的中断
     {
         key = key+2;
         P2IFG &=~BIT4;
     }
     else if((P2IFG&BIT5)!=0)//判断是P1.2上的中断
     {
         key = key+3;
         P2IFG &=~BIT5;
     }
     else if((P1IFG&BIT3)!=0)//判断是P1.3上的中断
     {
         key = key+4;
         P1IFG &=~BIT3;
     }
     else if((P1IFG&BIT4)!=0)//判断是P1.4上的中断
     {
         key = key+5;
         P1IFG &=~BIT4;
     }
     else if((P1IFG&BIT5)!=0)//判断是P1.5上的中断
     {
         key = key+6;
         P1IFG &=~BIT5;
     }
     else if((P1IFG&BIT6)!=0)//判断是P1.6上的中断
     {
         key = key+7;
         P1IFG &=~BIT6;
     }
     else if((P1IFG&BIT7)!=0)//判断是P1.7上的中断
     {
         key = 10;
         P1IFG &=~BIT7;
     }
     else if((P2IFG&BIT2)!=0)//判断是P2.2上的中断
     {
         key = 20;
         P2IFG &=~BIT2;
     }
 }

}
//延时函数
void delay(unsigned int i)
{   unsigned int j;             //定义局部变量
    for (j=0; j<i; j++);
}
//《两只老虎》播放函数
void TwoTigers_play()
{

    int i=0;   //“两只老虎”
      for(i=0;i<4;i++){
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x6fff);

      }
      if(i==4)  //两个“两只老虎”之间的停顿
      {
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=5;i<17;i++){    //“跑得快，跑得快”
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x6fff);
      }
      if(i==17){  //“跑得快”和“一只没有耳朵”中间停顿
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=0;i<16;i++){//“一只没有耳朵，一只没有尾巴”
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0.5*0x6fff);
      }
      if(i==16){//“一只没有尾巴”和“真奇怪”之间停顿
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=17;i<25;i++){//“真奇怪”
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0.5*0x6fff);
      }
      if(i==25){//两个“真奇怪”之间停顿
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=26;i<34;i++){//“真奇怪”
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0.5*0x6fff);
      }
      if(i==34){//“真奇怪”和“两只老虎”之间停顿
         TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
         TA1CCR1=(int)(0.1*TA1CCR0);
         delay(0x50);
      }
}
//《一闪一闪亮晶晶》播放函数
void LittleStars_play()
{

    int i = 0;
    if(i==0)
    {
      TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
      TA1CCR1=(int)(0.1*TA1CCR0);
      delay(0x6fff);
    }
    i++;
    if(i==1)
    {
      TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
      TA1CCR1=(int)(0.1*TA1CCR0);
      delay(0x50);
    }
    for(i=2;i<4;i++){
      TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
      TA1CCR1=(int)(0.1*TA1CCR0);
      delay(0x6fff);
    }
    if(i==4)
    {
      TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
      TA1CCR1=(int)(0.1*TA1CCR0);
      delay(0x50);
    }
    for(i=5;i<7;i++){
      TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
      TA1CCR1=(int)(0.1*TA1CCR0);
      delay(0x6fff);
    }
    if(i==7)
    {
      TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
      TA1CCR1=(int)(0.1*TA1CCR0);
      delay(0x50);
    }
    for(i=8;i<12;i++){
     TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
     TA1CCR1=(int)(0.1*TA1CCR0);
     delay(0x6fff);
    }
    if(i==12)
   {
        TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x50);
   }
    for(i=13;i<15;i++){
        TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
   }
    if(i==15)
   {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
   }
    for(i=16;i<18;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
   }
    if(i==18)
   {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
   }
    for(i=19;i<23;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
   }
    if(i==23)
  {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
  }
    for(i=24;i<26;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
  }
    if(i==26)
  {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
  }
    for(i=27;i<29;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
  }
    if(i==29)
  {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
  }
    for(i=30;i<34;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
  }
    if(i==34)
  {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
  }
    for(i=35;i<37;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
  }
    if(i==37)
  {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
  }
    for(i=38;i<40;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
  }
    if(i==40)
  {
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x50);
  }
   for(i=41;i<44;i++){
       TA1CCR0=(int)(((double)32768/(double)LittleStars_rym[LittleStars1[i]])-1);
       TA1CCR1=(int)(0.1*TA1CCR0);
       delay(0x6fff);
  }
}
//《闪亮的日子》播放函数
void ShiningDays_play()

{

    int i = 0;
    for(i=0;i<24;i++){
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays1[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
    }
    for(i=0;i<24;i++){
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays2[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
    }
    for(i=0;i<24;i++){
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays3[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
    }
    for(i=0;i<24;i++){
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays4[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
    }
    for(i=0;i<24;i++){
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays5[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
    }
    for(i=0;i<18;i++){
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays6[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
    }
    if(i==18)
    {
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays6[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x50);
    }
    for(i=19;i<24;i++){
        TA1CCR0=(int)(((double)32768/(double)ShiningDays_rym[ShiningDays6[i]])-1);
        TA1CCR1=(int)(0.1*TA1CCR0);
        delay(0x6fff);
    }
}
//播放《两只老虎》时晶体管L4亮一次
void TwoTigers_show()
{
    P2OUT &=~BIT3;
    delay(0xf000);
    P2OUT |=BIT3;
    delay(0xf000*2);
}
//播放《一闪一闪亮晶晶》时晶体管L4亮两次
void LittleStars_show()
{
    unsigned int i;
    for (i=0; i<4; i++)
  {
    P2OUT ^=BIT3;     //对引脚输出求反
    delay(0xffff);
  };
}
//播放《闪亮的日子》时晶体管L4亮三次
void ShiningDays_show()
{
    unsigned int i;
    for (i=0; i<6; i++)
  {
    P2OUT ^=BIT3;     //对引脚输出求反
    delay(0xffff);
  };
}
void  UARTA0_init( )
{   UCA0CTL1|= UCSWRST;      //置软件复位位swrst为1
    P1SEL |= BIT1+BIT2;             //置P1.1、P1.2为串行接口收、发引脚功能
    P1SEL2 |= BIT1+BIT2;        //数据格式选用上电复位设置：无校验，8位数据，1个停止位，异步串行通信
    UCA0CTL1|=UCSSEL0+UCRXEIE; //波特率时钟选择上电复位时的ACLK，32.768KHz，对错均收
    UCA0BR0 = 3;              //波特率9600
    UCA0BR1 = 0;
    UCA0MCTL=UCBRF_0+UCBRS_3;
    UCA0CTL1 &=~UCSWRST;        //置软件复位位swrst为0，串口设置完毕
}
void TxtOut(char string[]){
    int j = 0;
    while(string[j]!='\0')              //输出提示信息
    {   while((IFG2&UCA0TXIFG)==0);     //检测发送缓冲是否空
             UCA0TXBUF=string[j];       //取一个数据发送
             j++;
     };
}
void TxtIn(char string[], int num ){
    int j = 0;
    while(j < num)           //接收字符串
    {while((IFG2&UCA0RXIFG)==0);     //检测接收缓冲器是否满
          string[j] = UCA0RXBUF;       //接收一个数据并保存
          j++;
    };
}
int  CodeCheck(char buffer[],char Code[],int num){
    int rec = 0;
    int j = 0;
       while(j < num)//比较输入的字符串buffer和设定的密码字符串code是否相等
       {
           if(buffer[j] == Code[j]){rec++;}
           j++;
       };
     if(rec == num) //相等
         return 1;
     else          //不等
         return 0;
}
