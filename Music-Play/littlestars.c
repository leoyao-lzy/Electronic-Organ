#include <msp430.h> 
int rym[10] = {1,262,294,330,349,392,440,494,523,196};
int puzi1[44] = {1,0,1,5,0,5,6,0,6,5,0,4,0,4,3,0,3,2,0,2,1,0,5,0,5,4,0,4,3,0,3,2,0,5,0,5,4,0,4,3,0,3,2,0};
//int puzi2[22] = {5,0,5,4,0,4,3,0,3,2,0,5,0,5,4,0,4,3,0,3,2,0};
void delay(unsigned int i)     //��ʱ����
{   unsigned int j;             //����ֲ�����
    for (j=0; j<i; j++);
}
int main ( void )
{
    WDTCTL = WDTPW + WDTHOLD;       //�رտ��Ź�
        P2SEL |=BIT1+BIT4;              //��P2.1�� P2.4Ϊ��ʱ��TA1��PWM�������
        P2SEL2 &=~(BIT1+BIT4);              //��P2.1Ϊ�Ƚ���1��PWM�������
        P2DIR |=BIT1+BIT4;          //��P2.4Ϊ�Ƚ���2��PWM�������

        TA1CTL |=TASSEL0;   //ѡ��ACLKΪTA1����ʱ�ӣ�ACLKʹ���ϵ縴λ���ã����ⲿ����32768Hz
        //TA1CCR0=32767;            //����PWM���ڣ�����= (TA1CCR0+1)*T =(TA1CCR0+1)/����ʱ��Ƶ��
                //�������PWM����Ƶ��=1/PWM����=����ʱ��Ƶ��/(TA1CCR0+1)
        TA1CCTL1|=OUTMOD1;  //��TA1�Ƚ���1��PWM���Ϊģʽ2�� ������CCR1ֵ��ת����CCR0ֵ��0
        //TA1CCR1=3277;             //��TA1�Ƚ���1�趨ֵCCR1��TA1CCR1=TA1CCR0*(1-PWM����ռ�ձ�25%)

        //TA1CCTL2|=OUTMOD1;    //�ñȽ���2��PWM���Ϊģʽ2�� ������CCR2ֵ��ת����CCR0ֵ��0
        //TA1CCR2=16383;            //��TA1�Ƚ���2�趨ֵCCR2��TA1CCR2=TA1CCR0*(1-PWM����ռ�ձ�50%)

        TA1CTL |=TACLR+MC0; //����������ʽ��ʹ��������0��ʼ������������TA1CCR0���ִ�0������
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
