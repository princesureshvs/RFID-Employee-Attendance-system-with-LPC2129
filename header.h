#include <LPC21XX.H>

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed char s8;
typedef signed int s32;

extern void delay_sec(u32);
extern void delay_ms(u32);

extern void uart0_init(u32);
extern void uart0_tx(u8);
extern u8 uart0_rx();
extern void uart0_tx_string(u8*);
extern void uart0_rx_string();
extern void uart1_init(u32);
extern void uart1_tx(u8);
extern u8 uart1_rx();
extern void uart1_tx_string(u8*);
extern void uart1_rx_string(u8*, s32);

extern void lcd_data(u8 data);
extern void lcd_cmd(u8 cmd);
extern void lcd_init(void);
extern void lcd_string(s8 *);

extern void i2c_init(void);
extern void i2c_byte_write_frame(u8, u8, u8);
extern u8 i2c_byte_read_frame(u8, u8);

