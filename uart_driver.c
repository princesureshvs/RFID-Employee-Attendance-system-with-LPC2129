#include"header.h"

#define RDR0 (U0LSR&1)
#define THRE0 ((U0LSR>>5)&1)
#define RDR1 (U1LSR&1)
#define THRE1 ((U1LSR>>5)&1)

void uart0_init(u32 baud){
	int pclk;
	u32 result=0;
	int a[]={15,60,30,15,15};
	pclk=a[VPBDIV]*1000000;
	PINSEL0|=0x5;
	result=pclk/(16*baud);
	U0LCR=0x83;
	U0DLL=result&0xFF;
	U0DLM=(result>>8)&0xFF;
	U0LCR=0x03;
}

void uart0_tx(u8 data){
	U0THR=data;
	while(THRE0==0);
}

u8 uart0_rx(void){
	while(RDR0==0);
	return U0RBR;
}

void uart0_tx_string(u8 *p){
	while(*p!='\0'){
		U0THR=*p;
		while(THRE0==0);
		p++;
	}
	U0THR='\0';
	while(THRE0==0);
}

void uart0_rx_string(u8 *p,s32 n){
	s8 i;
	for(i=0;i<n;i++){
	while(RDR0==0);
	p[i]=U0RBR;
	if(p[i]=='\r')
	break;
	}
	p[i]='\0';
}

void uart0_tx_integer(s32 n){
	int i=0;
	char a[16];
	if(n==0){
		uart0_tx('0');
		return;
	}
	if(n<0){
		uart0_tx('-');
		n=-n;
	}
	while(n){
		a[i++]=n%10+48;
		n=n/10;
	}
	for(i--;i>=0;i--)
		uart0_tx(a[i]);
}


void uart1_init(u32 baud){
	int pclk;
	u32 result=0;
	int a[]={15,60,30,15,15};
	pclk=a[VPBDIV]*1000000;
	PINSEL0|=0x50000;
	result=pclk/(16*baud);
	U1LCR=0x83;
	U1DLL=result&0xFF;
	U1DLM=(result>>8)&0xFF;
	U1LCR=0x03;
}

void uart1_tx(u8 data){
	U1THR=data;
	while(THRE1==0);
}

u8 uart1_rx(void){
	while(RDR1==0);
	return U1RBR;
}


void uart1_tx_string(u8 *p){
	while(*p){
		uart1_tx(*p);
		p++;
	}
}

void uart1_rx_string(u8 *p,s32 n){
	s8 i;
	for(i=0;i<n;i++){
		while(RDR1==0);
		p[i]=U1RBR;
		if(p[i]=='\r')
		break;
	}
	p[i]='\0';
}

