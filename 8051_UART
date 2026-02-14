
#include<reg51.h>
sbit led=P1^1;
unsigned char receive();
void uart_init();
void delay();
void main(){
	unsigned char x;
	uart_init();

	while(1)
	{
		x=receive();
    if(x=='1')
		{
			led=1;
		}
		if(x=='0')
		{
			led=0;
		}
		
	}
}
unsigned char receive()
{
	while(RI==0);
	RI=0;
	return SBUF;
}

	void uart_init(){
		TMOD=0X20;
	TH1=0XFD;
	SCON=0X50;
	TR1=1;
}

	void delay(){
	int i,j;
	for(i=0;i<300;i++)
	{
		for(j=0;j<500;j++);
		{
		}
	}
}
