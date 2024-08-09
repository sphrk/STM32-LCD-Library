#include "lcd.h"
#include "delay.h"

typedef struct {
	GPIO_TypeDef *GPIO;
	uint32_t PinMask;
} lcd_pin_t;

/* ####################################################################### */

#define LCD_PIN_SET(LCD_PIN)		(LCD_PIN.GPIO->BSRR |= (LCD_PIN.PinMask & 0x0000FFFFUL))
#define LCD_PIN_CLR(LCD_PIN)		(LCD_PIN.GPIO->BRR |= LCD_PIN.PinMask)

//#define LCD_PIN_SET(LCD_SET) 	LL_GPIO_SetOutputPin(LCD_PIN.GPIO, LCD_PIN.PinMask)
//#define LCD_PIN_CLR(LCD_SET) 	LL_GPIO_ResetOutputPin(LCD_PIN.GPIO, LCD_PIN.PinMask)

/* ####################################################################### */

lcd_pin_t lcd_pin_rs = {.GPIO=LCD_PIN_RS_GPIO, .PinMask=LCD_PIN_RS_PinMask};
lcd_pin_t lcd_pin_rw = {.GPIO=LCD_PIN_RW_GPIO, .PinMask=LCD_PIN_RW_PinMask};
lcd_pin_t lcd_pin_en = {.GPIO=LCD_PIN_EN_GPIO, .PinMask=LCD_PIN_EN_PinMask};

#if LCD_MODE == 4
	lcd_pin_t lcd_pin_data[4] = {
		{.GPIO =LCD_PIN_DATA4_GPIO, .PinMask=LCD_PIN_DATA4_PinMask},
		{.GPIO =LCD_PIN_DATA5_GPIO, .PinMask=LCD_PIN_DATA5_PinMask},
		{.GPIO =LCD_PIN_DATA6_GPIO, .PinMask=LCD_PIN_DATA6_PinMask},
		{.GPIO =LCD_PIN_DATA7_GPIO, .PinMask=LCD_PIN_DATA7_PinMask},
	};
#elif LCD_MODE == 8
	lcd_pin_t lcd_pin_data[8] = {
		{.GPIO =LCD_PIN_DATA0_GPIO, .PinMask=LCD_PIN_DATA0_PinMask},
		{.GPIO =LCD_PIN_DATA1_GPIO, .PinMask=LCD_PIN_DATA1_PinMask},
		{.GPIO =LCD_PIN_DATA2_GPIO, .PinMask=LCD_PIN_DATA2_PinMask},
		{.GPIO =LCD_PIN_DATA3_GPIO, .PinMask=LCD_PIN_DATA3_PinMask},
		{.GPIO =LCD_PIN_DATA4_GPIO, .PinMask=LCD_PIN_DATA4_PinMask},
		{.GPIO =LCD_PIN_DATA5_GPIO, .PinMask=LCD_PIN_DATA5_PinMask},
		{.GPIO =LCD_PIN_DATA6_GPIO, .PinMask=LCD_PIN_DATA6_PinMask},
		{.GPIO =LCD_PIN_DATA7_GPIO, .PinMask=LCD_PIN_DATA7_PinMask}
	};
#endif

/* ####################################################################### */

//void delay_us(uint32_t usDelay){
//}

void lcd_EN_h2l_pulse(){
	LCD_PIN_SET(lcd_pin_en);
	delay_us(1);
	LCD_PIN_CLR(lcd_pin_en);
}

void lcd_write_to_data_pins(uint8_t data){
	uint8_t i;
	for(i = 0; i < LCD_MODE; i++){
		if(data & 0x01){
			//set Di pin
			//LL_GPIO_SetOutputPin(lcd_pin_data[i].GPIO, lcd_pin_data[i].PinMask);
			LCD_PIN_SET(lcd_pin_data[i]);
		}else{
			// clear Di pin
			// LL_GPIO_ResetOutputPin(lcd_pin_data[i].GPIO, lcd_pin_data[i].PinMask);
			LCD_PIN_CLR(lcd_pin_data[i]);
		}
		data >>= 1; // d = d >> 1;
	}
}

void lcd_write(uint8_t data){
	// RW = 0
	LCD_PIN_CLR(lcd_pin_rw);
	
	/* MODE 4-BIT */
	#if LCD_MODE == 4
		// write high nibble
		lcd_write_to_data_pins(data >> 4);
		lcd_EN_h2l_pulse();
		delay_us(100);
		
		// write low nibble
		lcd_write_to_data_pins(data);
		lcd_EN_h2l_pulse();
		delay_us(100);
	#elif LCD_MODE == 8
		lcd_write_to_data_pins(data);
		lcd_EN_h2l_pulse();
		delay_us(100);
	#else
		#error "INVALID 'LCD_MODE'"
	#endif
}

void lcd_write_command(uint8_t cmd){
	// RS = 0
	LCD_PIN_CLR(lcd_pin_rs);
	
	lcd_write(cmd);
	if((cmd == 0x01) || (cmd == 0x02)){ //clear or ... cmd 
		delay_us(2000);
	}else{
		delay_us(100);
	}
}

void lcd_write_data(uint8_t data){
	// RS = 1
	LCD_PIN_SET(lcd_pin_rs);
	
	lcd_write(data);
	delay_us(100);
}

void lcd_init(void){
	// set pin to output
	
	LCD_PIN_CLR(lcd_pin_en);
	delay_us(15000); //wait for init
	
	#if LCD_MODE == 4
		// init 4-BIT MODE
		lcd_write_command(0x33);
		lcd_write_command(0x32);
	
		lcd_write_command(0x28); // 4-BIT MODE
	#elif LCD_MODE == 8
		lcd_write_command(0x38); // 8-BIT MODE
	#else
		#error "INVALID 'LCD_MODE'"
	#endif
	
	lcd_write_command(0x0e);	// Display On, curser blink
	lcd_write_command(0x01);	// Clear
	lcd_write_command(0x06);	// shift cursor right
}


void lcd_clear(void){
	lcd_write_command(LCD_CMD_CLEAR);
}

void lcd_print(uint8_t *s){
	uint32_t i;
	for(i = 0; s[i] != '\0'; i++){
		lcd_write_data(s[i]);
	}
}

void lcd_gotoxy(uint8_t x, uint8_t y){
}

