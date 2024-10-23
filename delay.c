#include "header.h"

void delay_sec(u32 sec){
	int a[]={15,60,30,15,15};
	unsigned int PCLK;
	PCLK=a[VPBDIV]*1000000;
	T0PC=0;
	T0PR=PCLK-1;
	T0TC=0;
	T0TCR=1;
	while(T0TC<sec);
	T0TCR=0;
}


void delay_ms(u32 ms){
	int a[]={15,60,30,15,15};
	unsigned int PCLK;
	PCLK=a[VPBDIV]*1000;
	T0PC=0;
	T0PR=PCLK-1;
	T0TC=0;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}