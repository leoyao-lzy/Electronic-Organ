#include "msp430.h"
int rym[9] = {1,262,294,330,165,196,220,247,440};
int puzi1[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,6,6};  //�����������ӡ����ӵ�һ��
int puzi2[24] = {3,3,3,6,1,3,2,2,2,5,7,2,1,1,1,6,7,1,7,7,7,7,4,4};  //�����������ӡ����ӵڶ���
int puzi3[24] = {3,3,3,2,1,2,3,3,3,3,8,8,3,3,3,2,1,2,3,3,3,3,0,1};  //�����������ӡ�����������
int puzi4[24] = {2,2,2,2,2,3,6,6,6,6,0,6,1,1,1,1,1,2,7,7,7,7,4,4};  //�����������ӡ�����������
int puzi5[24] = {3,3,3,2,1,2,3,3,3,3,0,8,3,3,3,2,1,2,3,3,3,3,0,1};  //�����������ӡ�����������
int puzi6[23] = {2,2,2,2,2,3,6,6,6,6,0,5,6,6,6,1,7,6,0,6,6,6,6};    //�����������ӡ�����������

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
