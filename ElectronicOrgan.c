#include <msp430.h> 
int flag=0;      //����ѡ�񲥷�����
int key=0;       //���ڵ���ʱѡ������
int convert =0;  //����ģʽ�л�
int a;           //a=1ʱΪ���ţ�a=2ʱΪ����
//����ֻ�ϻ����������
const int TwoTigers_rym[10] = {1,262,294,330,349,392,440,494,523,196};                              //����ֻ�ϻ�������Ƶ��
const int TwoTigers1[18] = {1,2,3,1,0,1,2,3,1,3,4,5,5,3,4,5,5,0};                                   //����ֻ�ϻ�����һ������
const int TwoTigers2[35] = {5,6,5,4,3,3,1,1,5,6,5,4,3,3,1,1,0,1,1,9,9,1,1,1,1,0,1,1,9,9,1,1,1,1,0}; //����ֻ�ϻ����ڶ�������
//��һ��һ�����������������
const int LittleStars_rym[10] = {1,262,294,330,349,392,440,494,523,196};                            //��һ��һ��������������Ƶ��
const int LittleStars1[44] = {1,0,1,5,0,5,6,0,6,5,0,4,0,4,3,
                              0,3,2,0,2,1,0,5,0,5,4,0,4,3,0,3,2,0,5,0,5,4,0,4,3,0,3,2,0};//��һ��һ��������������
//�����������ӡ��������
const int ShiningDays_rym[9] = {1,262,294,330,165,196,220,247,440};
const int ShiningDays1[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,6,6};  //�����������ӡ����ӵ�һ��
const int ShiningDays2[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,4,4};  //�����������ӡ����ӵڶ���
const int ShiningDays3[24] = {3,3,3,2,1,2,3,3,3,3,8,8,3,3,3,2,1,2,3,3,3,3,0,1};  //�����������ӡ�����������
const int ShiningDays4[24] = {2,2,2,2,2,3,6,6,6,6,0,6,1,1,1,1,1,2,7,7,7,7,4,4};  //�����������ӡ�����������
const int ShiningDays5[24] = {3,3,3,2,1,2,3,3,3,3,0,8,3,3,3,2,1,2,3,3,3,3,0,1};  //�����������ӡ�����������
const int ShiningDays6[24] = {2,2,2,2,2,3,6,6,6,6,0,5,6,6,6,1,7,6,0,6,6,6,6,0};  //�����������ӡ�����������
//�������岿��
void delay(unsigned int i);
void TwoTigers_play();
void LittleStars_play();
void ShiningDays_play();
void TwoTigers_show();    //L4��һ��
void LittleStars_show();  //L4������
void ShiningDays_show();  //L4������
//����ͨ�Ų���
void UARTA0_init( );
void TxtOut(char string[]);     //����ַ�������
void TxtIn(char string[], int num); //����ַ�������
int  CodeCheck(char buffer[],char Code[],int num);  //������������Ƿ���ȷ����
char buffer[11]="12345678\r\n\0";
char code[] = "12345678";     //�������������
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
    //���ö�ʱ��TA1
    P2SEL |=BIT1;              //��P2.1Ϊ��ʱ��TA1��PWM�������
    P2SEL2 &=~BIT1;
    P2DIR |=BIT1;              //��P2.1Ϊ�Ƚ���1��PWM�������
    TA1CTL |=TASSEL0;          //ѡ��ACLKΪTA1����ʱ�ӣ�ACLKʹ���ϵ縴λ���ã����ⲿ����32768Hz
    TA1CCTL1|=OUTMOD1;         //��TA1�Ƚ���1��PWM���Ϊģʽ2�� ������CCR1ֵ��ת����CCR0ֵ��0
    TA1CTL |=TACLR+MC0;        //����������ʽ��ʹ��������0��ʼ������������TA1CCR0���ִ�0����
    //�ж��������
    P1SEL &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);//P1.0~P1.7(��P1.1��P1.2�⣩�ֱ��K1~K8��������K2,K3�⣩
    P1SEL2 &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1OUT |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1REN |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1DIR &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1IES |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1IFG &= ~(BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P1IE |= (BIT0+BIT3+BIT4+BIT5+BIT6+BIT7+BIT8);
    P2SEL &=~(BIT0+BIT2+BIT4+BIT5);//P2.0���ⲿ����Kb���ӣ��л�ģʽ���ܣ���P2.2���ⲿ����Ka���ӣ������������ܣ���P2.4��K2������P2.5��K3����
    P2SEL2 &=~(BIT0+BIT2+BIT4+BIT5);
    P2OUT |=(BIT0+BIT2+BIT4+BIT5);
    P2REN |=(BIT0+BIT2+BIT4+BIT5);
    P2DIR &=~(BIT0+BIT2+BIT4+BIT5);
    P2IES |=(BIT0+BIT2+BIT4+BIT5);
    P2IFG &=~(BIT0+BIT2+BIT4+BIT5);
    P2IE |=(BIT0+BIT2+BIT4+BIT5);
    _EINT();    //���ж�����
    //����LED�ƶ˿����ã�P2.3-L4��
    P2SEL &=~BIT3;
    P2SEL2 &=~BIT3;
    P2OUT |=BIT3;
    P2DIR |=BIT3;
    //����ͨ��
    UARTA0_init( );                 //��ʼ������
    //����ʱ���ó�ʼ����
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
    //��ʼ���ò��ֵ��˽���
    while(1)
    {
        //��������ģʽ
        if(flag == 1)   //���š���ֻ�ϻ���
        {
          TwoTigers_show();
          TxtOut(TwoTigers);
          TwoTigers_play();
          flag=0;
        }
        else if (flag == 2)//���š�һ��һ����������
        {
          LittleStars_show();
          TxtOut(LittleStars);
          LittleStars_play();
          flag=0;
        }
        else if (flag == 3)//���š����������ӡ�
        {
          ShiningDays_show();
          TxtOut(ShiningDays);
          ShiningDays_play();
          flag=0;
        }
        else if (flag == 4)//�������Ʋ���
        {
          TxtOut(Choices);
          TxtIn(buffer,1);
          CheckPoint = CodeCheck(buffer,one,1);
          if (CheckPoint==1){    //�������Ʋ��š���ֻ�ϻ���
              TwoTigers_show();
              TxtOut(TwoTigers);
              TwoTigers_play();
              flag=0;
          }
          else if (CheckPoint==0){
              CheckPoint = CodeCheck(buffer,two,1);
              if(CheckPoint==1){     //�������Ʋ��š�һ��һ����������
                  LittleStars_show();
                  TxtOut(LittleStars);
                  LittleStars_play();
                  flag=0;
              }
              else if(CheckPoint==0){
                  CheckPoint = CodeCheck(buffer,three,1);
                  if(CheckPoint==1){     //�������Ʋ��š����������ӡ�
                      ShiningDays_show();
                      TxtOut(ShiningDays);
                      ShiningDays_play();
                      flag=0;
                  }
                  else if(CheckPoint==0){   //��������
                      TxtOut(nosongs);
                  }
              }
          }
        }
        //��������ģʽ
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
__interrupt  void port_ISR( ) //�ж��ӳ���
{
    if((P2IFG&BIT0)!=0)     // �ж���P2.0�ϵ��жϣ�Ka�Ƿ��£�
 {
     convert = convert+1;
     P2IFG &=~BIT0;
 }
   if (convert%2==1){a=1;}   // convert������
   else if(convert%2==0){a=2;}//convert��ż��
 if(a==1)     //��������ģʽ
   {
     if ( (P1IFG&BIT0)!=0 )  //�ж���P1.0�ϵ��ж�
    {
        flag = 1;           //��Ӧ���š���ֻ�ϻ���
        P1IFG &=~BIT0;
    }
    else if((P2IFG&BIT4)!=0)//�ж���P2.6�ϵ��ж�
    {
        flag = 2;           //��Ӧ���š�һ��һ����������
        P2IFG &=~BIT4;
    }
    else if((P2IFG&BIT5)!=0)//�ж���P2.5�ϵ��ж�
    {
        flag = 3;           //��Ӧ���š����������ӡ�
        P2IFG &=~BIT5;
    }
    else if ( (P1IFG&BIT3)!=0 )  //�ж���P1.3�ϵ��ж�
    {
         flag = 4;           //�������Ʋ���ģʽ
         P1IFG &=~BIT3;
    }
   }
 if(a==2)      //��������ģʽ
 {
     if ((P1IFG&BIT0)!=0)  //�ж���P1.0�ϵ��ж�
     {
         key = key+1;
         P1IFG &=~BIT0;
     }
     else if((P2IFG&BIT4)!=0)//�ж���P1.1�ϵ��ж�
     {
         key = key+2;
         P2IFG &=~BIT4;
     }
     else if((P2IFG&BIT5)!=0)//�ж���P1.2�ϵ��ж�
     {
         key = key+3;
         P2IFG &=~BIT5;
     }
     else if((P1IFG&BIT3)!=0)//�ж���P1.3�ϵ��ж�
     {
         key = key+4;
         P1IFG &=~BIT3;
     }
     else if((P1IFG&BIT4)!=0)//�ж���P1.4�ϵ��ж�
     {
         key = key+5;
         P1IFG &=~BIT4;
     }
     else if((P1IFG&BIT5)!=0)//�ж���P1.5�ϵ��ж�
     {
         key = key+6;
         P1IFG &=~BIT5;
     }
     else if((P1IFG&BIT6)!=0)//�ж���P1.6�ϵ��ж�
     {
         key = key+7;
         P1IFG &=~BIT6;
     }
     else if((P1IFG&BIT7)!=0)//�ж���P1.7�ϵ��ж�
     {
         key = 10;
         P1IFG &=~BIT7;
     }
     else if((P2IFG&BIT2)!=0)//�ж���P2.2�ϵ��ж�
     {
         key = 20;
         P2IFG &=~BIT2;
     }
 }

}
//��ʱ����
void delay(unsigned int i)
{   unsigned int j;             //����ֲ�����
    for (j=0; j<i; j++);
}
//����ֻ�ϻ������ź���
void TwoTigers_play()
{

    int i=0;   //����ֻ�ϻ���
      for(i=0;i<4;i++){
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x6fff);

      }
      if(i==4)  //��������ֻ�ϻ���֮���ͣ��
      {
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=5;i<17;i++){    //���ܵÿ죬�ܵÿ족
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x6fff);
      }
      if(i==17){  //���ܵÿ족�͡�һֻû�ж��䡱�м�ͣ��
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers1[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=0;i<16;i++){//��һֻû�ж��䣬һֻû��β�͡�
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0.5*0x6fff);
      }
      if(i==16){//��һֻû��β�͡��͡�����֡�֮��ͣ��
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=17;i<25;i++){//������֡�
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0.5*0x6fff);
      }
      if(i==25){//����������֡�֮��ͣ��
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0x50);
      }
      for(i=26;i<34;i++){//������֡�
          TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
          TA1CCR1=(int)(0.1*TA1CCR0);
          delay(0.5*0x6fff);
      }
      if(i==34){//������֡��͡���ֻ�ϻ���֮��ͣ��
         TA1CCR0=(int)(((double)32768/(double)TwoTigers_rym[TwoTigers2[i]])-1);
         TA1CCR1=(int)(0.1*TA1CCR0);
         delay(0x50);
      }
}
//��һ��һ�������������ź���
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
//�����������ӡ����ź���
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
//���š���ֻ�ϻ���ʱ�����L4��һ��
void TwoTigers_show()
{
    P2OUT &=~BIT3;
    delay(0xf000);
    P2OUT |=BIT3;
    delay(0xf000*2);
}
//���š�һ��һ����������ʱ�����L4������
void LittleStars_show()
{
    unsigned int i;
    for (i=0; i<4; i++)
  {
    P2OUT ^=BIT3;     //�����������
    delay(0xffff);
  };
}
//���š����������ӡ�ʱ�����L4������
void ShiningDays_show()
{
    unsigned int i;
    for (i=0; i<6; i++)
  {
    P2OUT ^=BIT3;     //�����������
    delay(0xffff);
  };
}
void  UARTA0_init( )
{   UCA0CTL1|= UCSWRST;      //�������λλswrstΪ1
    P1SEL |= BIT1+BIT2;             //��P1.1��P1.2Ϊ���нӿ��ա������Ź���
    P1SEL2 |= BIT1+BIT2;        //���ݸ�ʽѡ���ϵ縴λ���ã���У�飬8λ���ݣ�1��ֹͣλ���첽����ͨ��
    UCA0CTL1|=UCSSEL0+UCRXEIE; //������ʱ��ѡ���ϵ縴λʱ��ACLK��32.768KHz���Դ����
    UCA0BR0 = 3;              //������9600
    UCA0BR1 = 0;
    UCA0MCTL=UCBRF_0+UCBRS_3;
    UCA0CTL1 &=~UCSWRST;        //�������λλswrstΪ0�������������
}
void TxtOut(char string[]){
    int j = 0;
    while(string[j]!='\0')              //�����ʾ��Ϣ
    {   while((IFG2&UCA0TXIFG)==0);     //��ⷢ�ͻ����Ƿ��
             UCA0TXBUF=string[j];       //ȡһ�����ݷ���
             j++;
     };
}
void TxtIn(char string[], int num ){
    int j = 0;
    while(j < num)           //�����ַ���
    {while((IFG2&UCA0RXIFG)==0);     //�����ջ������Ƿ���
          string[j] = UCA0RXBUF;       //����һ�����ݲ�����
          j++;
    };
}
int  CodeCheck(char buffer[],char Code[],int num){
    int rec = 0;
    int j = 0;
       while(j < num)//�Ƚ�������ַ���buffer���趨�������ַ���code�Ƿ����
       {
           if(buffer[j] == Code[j]){rec++;}
           j++;
       };
     if(rec == num) //���
         return 1;
     else          //����
         return 0;
}
