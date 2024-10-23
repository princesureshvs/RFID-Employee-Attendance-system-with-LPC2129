#include "header.h"

s32 count=0,result;
s8 a[31],r[20];
s32 c=0,b=0;
u32 flag1=0,flag2=0;

__irq void uart1_handler(void){
	if(((U1IIR>>1)&7)==2){
		a[c]=U1RBR;
		if(a[c]=='\r'){
			a[c]='\0';
			flag1=1;
			c=0;
		}
		else if(c==11){
			a[12]='\0';
			c=0;
			flag1=1;
		}
		if(flag1==0)
			c=c+1;	 
	}	
	VICVectAddr=0;
}		

__irq void uart0_handler(void){
	if(((U0IIR>>1)&7)==2){
		r[b]=U0RBR;
		if(r[b]=='\r'){
			r[b]='\0';
			flag2=1;
			b=0;
		}
		else if(b==18){
			r[19]='\0';
			b=0;
		    flag2=1;
		}
		if(flag2==0)
			b=b+1;	 
	}
	VICVectAddr=0;
}		

void config_vic(void){
	VICIntSelect=0;
	VICVectAddr0=(u32)uart1_handler;
	VICVectAddr1=(u32)uart0_handler;
	VICVectCntl0=7|(1<<5);
	VICVectCntl1=6|(1<<5);
	VICIntEnable|=1<<6|1<<7;
}
void en_eint0(void){
	U0IER=1;
	U1IER=1;
} 

int main(){
	int hour,h,m,s,date,month,year,day;
	lcd_init();
	i2c_init();
	uart0_init(9600);
	uart1_init(9600);
	en_eint0();
	config_vic();
	i2c_byte_write_frame(0xD0,0x0,0x50);
	i2c_byte_write_frame(0xD0,0x1,0x59);
	i2c_byte_write_frame(0xD0,0x2,0x11|1<<6|1<<5); //1<<6 is to give 12 hour mode  and 1<<5 to set pm
	
	i2c_byte_write_frame(0xD0,0x3,0x1);
	i2c_byte_write_frame(0xD0,0x4,0x14);
	i2c_byte_write_frame(0xD0,0x5,0x3);
	i2c_byte_write_frame(0xD0,0x6,0x24);
	  
while(1){	
		lcd_cmd(0x80);
		hour=i2c_byte_read_frame(0xD0,0x2);
		h=hour&0X1F;
		m=i2c_byte_read_frame(0xD0,0x1);
		s=i2c_byte_read_frame(0xD0,0x0);
		day=i2c_byte_read_frame(0xD0,0x3);
		date=i2c_byte_read_frame(0xD0,0x4);
		month=i2c_byte_read_frame(0xD0,0x5);
		year=i2c_byte_read_frame(0xD0,0x6);

		lcd_cmd(0x80);
		lcd_data((h/0x10)+48);
		lcd_data((h%0x10)+48);
		lcd_data(':');
		
		lcd_data((m/0x10)+48);
		lcd_data((m%0x10)+48);
		lcd_data(':');
		
		lcd_data((s/0x10)+48);
		lcd_data((s%0x10)+48);
		if((hour>>5)&1){
			lcd_cmd(0x89);
			lcd_string("PM");
		}
		else{
		lcd_cmd(0x89);
		lcd_string("AM");
		}		 
		lcd_cmd(0xc0);
		lcd_data((date/0x10)+48);
		lcd_data((date%0x10)+48);
		lcd_data(':');
		lcd_data((month/0x10)+48);
		lcd_data((month%0x10)+48);
		lcd_data(':');
		lcd_string("20");
		
		lcd_data((year/0x10)+48);
		lcd_data((year%0x10)+48);


		lcd_cmd(0xCB);
		switch(day){
			case 1:lcd_string("Mon");break;
			case 2:lcd_string("Tue");break;
			case 3:lcd_string("Wed");break;
			case 4:lcd_string("Thu");break;
			case 5:lcd_string("Fri");break;
			case 6:lcd_string("Sat");break;
			case 7:lcd_string("Sun");break;
		}

	if(flag1==1){
		flag1=0;
		hour=i2c_byte_read_frame(0xD0,0x2);
		h=hour&0X1F;
		m=i2c_byte_read_frame(0xD0,0x1);
		s=i2c_byte_read_frame(0xD0,0x0);
		date=i2c_byte_read_frame(0xD0,0x4);
		month=i2c_byte_read_frame(0xD0,0x5);
		year=i2c_byte_read_frame(0xD0,0x6);
		a[12]=' ';
		a[13]=((h/0x10)+48);
		a[14]=((h%0x10)+48);
		a[15]=':';
		a[16]=((m/0x10)+48);
		a[17]=((m%0x10)+48);
		a[18]=':';
		a[19]=((s/0x10)+48);
		a[20]=((s%0x10)+48);
		a[21]=' ';
		a[22]=((date/0x10)+48);
		a[23]=((date%0x10)+48);
		a[24]='/';
		a[25]=((month/0x10)+48);
		a[26]=((month%0x10)+48);
		a[27]='/';
		a[28]=((year/0x10)+48);
		a[29]=((year%0x10)+48);
		a[30]='\0';
	    uart0_tx_string(a);
	}

	if(flag2==1){
		lcd_cmd(0x01);
 		flag2=0;
		lcd_string(r);
		delay_ms(1000);
		lcd_cmd(0x01);
	}
}
}	

