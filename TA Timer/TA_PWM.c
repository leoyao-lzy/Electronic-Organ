#include "msp430.h"

int main ( void )
{   WDTCTL = WDTPW + WDTHOLD;   	//�رտ��Ź�
    P2SEL |=BIT1+BIT4;      		//��P2.1�� P2.4Ϊ��ʱ��TA1��PWM�������
    P2SEL2 &=~(BIT1+BIT4);      		//��P2.1Ϊ�Ƚ���1��PWM�������
    P2DIR |=BIT1+BIT4;   		//��P2.4Ϊ�Ƚ���2��PWM�������

    TA1CTL |=TASSEL0;	//ѡ��ACLKΪTA1����ʱ�ӣ�ACLKʹ���ϵ縴λ���ã����ⲿ����32768Hz
    TA1CCR0=32767;          	//����PWM���ڣ�����= (TA1CCR0+1)*T =(TA1CCR0+1)/����ʱ��Ƶ��
			//�������PWM����Ƶ��=1/PWM����=����ʱ��Ƶ��/(TA1CCR0+1)
    TA1CCTL1|=OUTMOD1; 	//��TA1�Ƚ���1��PWM���Ϊģʽ2�� ������CCR1ֵ��ת����CCR0ֵ��0
    TA1CCR1=24575;          	//��TA1�Ƚ���1�趨ֵCCR1��TA1CCR1=TA1CCR0*(1-PWM����ռ�ձ�25%)

    TA1CCTL2|=OUTMOD1; 	//�ñȽ���2��PWM���Ϊģʽ2�� ������CCR2ֵ��ת����CCR0ֵ��0
    TA1CCR2=16383;          	//��TA1�Ƚ���2�趨ֵCCR2��TA1CCR2=TA1CCR0*(1-PWM����ռ�ձ�50%)

    TA1CTL |=TACLR+MC0;	//����������ʽ��ʹ��������0��ʼ������������TA1CCR0���ִ�0������
			
      while(1){  };      		// ��ѭ����CPU������������
}
