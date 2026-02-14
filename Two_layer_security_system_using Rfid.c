 #include<p18f4520.h>
#define RW PORTCbits.RC0   
#define RS PORTCbits.RC1 
#define EN PORTCbits.RC2
#define r0 PORTBbits.RB5
#define r1 PORTBbits.RB6
#define r2 PORTBbits.RB7
#define c0 PORTBbits.RB1
#define c1 PORTBbits.RB2
#define c2 PORTBbits.RB3
#define c3 PORTBbits.RB4
#define data_line PORTD 
void UART_init (void);
void trans(unsigned char);
unsigned char receive(void);
void lcd_string(unsigned char *p);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay(int);
void main (){
unsigned char str[15]="WELCOME";
unsigned char str1[15]="SCAN CARD";
unsigned char str2[15]="ENTER PASSWORD";
unsigned char str3[15]="ACCESS GRANTED";
unsigned char str4[15]="ACCESS DENIED";
int i;
 unsigned char x, tag[12],id[13]="090015FFEE0D";
unsigned char pass[4];
 TRISB=0X00;
PORTB=0X00;
lcd_init();
UART_init();
TRISB=0X1E;
ADCON1=0X0F;
INTCON2bits.RBPU=0;
while(1)
{
lcd_cmd(0X80);
lcd_string(str);
lcd_cmd (0XC0);
lcd_string(str1);
for(i=0;i<12;i++)
{
x= receive();
tag[i]=x;
trans(x);
}
if(tag[0]==id[0] && tag[1]==id[1] && tag[2]==id[2] && tag[3]==id[3] && tag[4]==id[4] && tag[5]==id[5] && tag[6]==id[6] && tag[7]==id[7] && tag[8]==id[8] && tag[9]==id[9] && tag[10]==id[10] && tag[11]==id[11] )
{
lcd_cmd (0X01);
lcd_cmd (0X80);
lcd_string(str2);
lcd_cmd (0Xc0);
i=0;
while(i<4)
{
r0=0;
r1=r2=1;
if(c0==0)
{
pass[i]=1;
i++;
lcd_data('1');
}
if(c1==0)
{pass[i]=2;
i++;
lcd_data('2');
}
if(c2==0)
{pass[i]=3;
i++;
lcd_data('3');
}
if(c3==0)
{pass[i]=4;
i++;
lcd_data('4');
}
r1=0;
r0=r2=1;
if(c0==0)
{pass[i]=5;
i++;
lcd_data('5');
}
if(c1==0)
{pass[i]=6;
i++;
lcd_data('6');
}
if(c2==0)
{pass[i]=7;
i++;
lcd_data('7');
}
if(c3==0)
{pass[i]=8;
i++;
lcd_data('8');
}
r2=0;
r0=r1=1;
if(c0==0)
{pass[i]=9;
i++;
lcd_data('9');
}
delay(200);
}
	if(pass[0]==1 && pass[1]==2 && pass[2]==3 && pass[3]==4)
		{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_string(str3);
	}
	else 
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
	lcd_string(str4);
	
}
}

}
}
void UART_init (void)
{
TRISC=0X80;
TXSTA=0X24;
RCSTA=0X90;
SPBRG=0X81;
}
void trans(unsigned char x)
{
TXREG=x;
while (TXSTAbits.TRMT==0);
}


unsigned char receive(void)
{
while( PIR1bits.RCIF==0);
return RCREG;
}


void lcd_init(void)
{
TRISD=0X00; 
TRISC=0X00; 
lcd_cmd(0X30);
lcd_cmd (0X38); 
lcd_cmd(0x01); 
lcd_cmd (0X80);
lcd_cmd (0X0C); 
}
void lcd_cmd(unsigned char d)
{
data_line=d;
RS=0;
RW=0;
EN=1;
delay(50);
EN=0;
}
void lcd_data(unsigned char c)
{
data_line=c;
RS=1;
RW=0;
EN=1;
delay(50);
EN=0;
}
void delay(int t)
{
int i,j;
`for(i=0;i<t;i++)
{ 
 for(j=0;j<300;j++);
}
}
void lcd_string(unsigned char *p)
{ 
while(*p!='\0')
{
 lcd_data(*p);
p++;
}
}


		









