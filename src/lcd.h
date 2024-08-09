#ifndef __INC_LCD_H__
#define __INC_LCD_H__

#include "main.h"

/* ################################################################## */

#define LCD_PIN_RS_GPIO		GPIOA
#define LCD_PIN_RS_PinMask	(0x1UL << 1)

#define LCD_PIN_RW_GPIO		GPIOA
#define LCD_PIN_RW_PinMask	(0x1UL << 2)

#define LCD_PIN_EN_GPIO		GPIOA
#define LCD_PIN_EN_PinMask	(0x1UL << 3)

#define LCD_PIN_DATA4_GPIO	GPIOA
#define LCD_PIN_DATA4_PinMask (0x1UL << 4)

#define LCD_PIN_DATA5_GPIO	GPIOA
#define LCD_PIN_DATA5_PinMask (0x1UL << 5)

#define LCD_PIN_DATA6_GPIO	GPIOA
#define LCD_PIN_DATA6_PinMask (0x1UL << 6)

#define LCD_PIN_DATA7_GPIO	GPIOA
#define LCD_PIN_DATA7_PinMask (0x1UL << 7)

/* ################################################################## */

#ifndef LCD_PIN_RS_GPIO
	#error "lcd RS pin GPIO must be defined!"
#endif
#ifndef LCD_PIN_RS_PinMask
	#error "lcd RS pin PinMask must be defined!"
#endif

#ifndef LCD_PIN_RW_GPIO
	#error "lcd RW pin GPIO must be defined!"
#endif
#ifndef LCD_PIN_RW_PinMask
	#error "lcd RW pin PinMask must be defined!"
#endif

#ifndef LCD_PIN_EN_GPIO
	#error "lcd EN pin GPIO must be defined!"
#endif
#ifndef LCD_PIN_EN_PinMask
	#error "lcd EN pin PinMask must be defined!"
#endif

#ifndef LCD_MODE
	#define LCD_MODE	4
#endif

#if LCD_MODE == 4
	#if !(defined(LCD_PIN_DATA4_GPIO) && defined(LCD_PIN_DATA5_GPIO) && defined(LCD_PIN_DATA6_GPIO) && defined(LCD_PIN_DATA7_GPIO))
		#error "lcd Data[4:7] Pins GPIO must be defined"
	#endif
	#if !(defined(LCD_PIN_DATA4_PinMask) && defined(LCD_PIN_DATA5_PinMask) && defined(LCD_PIN_DATA6_PinMask) && defined(LCD_PIN_DATA7_PinMask))
		#error "lcd Data[4:7] Pins PinMask must be defined"
	#endif
#elif LCD_MODE == 8
	#if !(defined(LCD_PIN_DATA0_GPIO) && defined(LCD_PIN_DATA1_GPIO) && defined(LCD_PIN_DATA2_GPIO) && defined(LCD_PIN_DATA3_GPIO) && defined(LCD_PIN_DATA4_GPIO) && defined(LCD_PIN_DATA5_GPIO) && defined(LCD_PIN_DATA6_GPIO) && defined(LCD_PIN_DATA7_GPIO))
		#error "lcd Data[0:7] Pins GPIO must be defined"
	#endif
	#if !(defined(LCD_PIN_DATA0_PinMask) && defined(LCD_PIN_DATA1_PinMask) && defined(LCD_PIN_DATA2_PinMask) && defined(LCD_PIN_DATA3_PinMask) && defined(LCD_PIN_DATA4_PinMask) && defined(LCD_PIN_DATA5_PinMask) && defined(LCD_PIN_DATA6_PinMask) && defined(LCD_PIN_DATA7_PinMask))
		#error "lcd Data[0:7] Pins PinMask must be defined"
	#endif
#else
	#error "Invalid Value for LCD_MODE. LCD_MODE value Must be 4 or 8."
#endif

/* ################################################################## */

#define LCD_CMD_CLEAR		0x01
#define LCD_CMD_DEC_CURSOR	0x04
#define LCD_CMD_INC_CURSOR	0x06
#define LCD_CMD_DISPLAY_OFF_CUSOR_OFF	0x08
#define LCD_CMD_DISPLAY_OFF_CUSOR_ON	0x0A
#define LCD_CMD_DISPLAY_ON_CUSOR_OFF	0x0C
#define LCD_CMD_DISPLAY_ON_CUSOR_BLINK	0x0E

/* ################################################################## */

void lcd_write_command(uint8_t data);
void lcd_write_data(uint8_t data);
void lcd_init(void);
void lcd_clear(void);
void lcd_print(uint8_t *s);
void lcd_gotoxy(uint8_t x, uint8_t y);

/* ################################################################## */

#endif // end of file
	
	
