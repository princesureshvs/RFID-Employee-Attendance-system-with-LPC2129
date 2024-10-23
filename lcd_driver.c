#include "header.h"

#define RS 1 << 17
#define RW 1 << 18
#define EN 1 << 19

void lcd_data(u8 data){
	u32 temp;
	IOCLR1 = 0xFE << 16;
	temp = (data & 0xF0) << 16;
	IOSET1 = temp;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
	IOCLR1 = 0xFE << 16;
	temp = (data & 0xF0) << 20;
	IOSET1 = temp;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
}

void lcd_cmd(u8 cmd){
	u32 temp;
	IOCLR1 = 0xFE << 16;
	temp = (cmd & 0xF0) << 16;
	IOSET1 = temp;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
	IOCLR1 = 0xFE << 16;
	temp = (cmd & 0xF0) << 20;
	IOSET1 = temp;
	IOSET1 = RS;
	IOCLR1 = RW;
	IOSET1 = EN;
	delay_ms(2);
	IOCLR1 = EN;
}

void lcd_init(){
	IODIR1 = 0xFE << 16;
	IOCLR1 = EN;
	PINSEL2 = 0x0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
}

void lcd_string(s8 *p){
	while(*p){
		lcd_data(*p);
		p++;
	}
}






















