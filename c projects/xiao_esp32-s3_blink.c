#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

/*
The Seeed Studio "Getting Started with Seeed Studio XIAO ESP32-S3 Series" page shows a pinout where
the `USER_LED` is set to pin name `GPIO21`
https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/#xiao-esp32-s3-front

Most of the information I'm finding that lines up with the Packt Bare Metal C book is being found in
the ESP32-S3 Technical Reference Manual, while the book says that for ST chips this would be found
in the user datasheet. The datasheet does show the pin layout (Figure 2-1, pg 11) showing that GPIO21
is pin 27.

The data sheet also has the Address Mapping Structure (Figure 3-1, pg 28) showing the address range
for the Peripherals.

To find the boundaries for the different kinds of peripherals, this is in the technical reference
manual (Talbe 4.3-3, pg 408-409). Chapter 6 is about GPIO and I/O, with 6.5 being specifically about
Output. 6.14.1 (pg 496-497) provides the GPIO Matrix Register Summary, where offsets are listed relative
to the GPIO base address. 

To set a pin as output:
>> GPIO matrix can also be used for simple GPIO output. This can be done as below:
>> - Set the corresponding bit in GPIO_OUT_REG[31:0] or GPIO_OUT1_REG[21:0] to the desired GPIO output
>>   value.
>> Recommended operation: use corresponding W1TS and W1TC registers, such as GPIO_OUT_W1TS/GPIO_OUT_W1TC
>> to set or clear the registers GPIO_OUT_REG/GPIO_OUT1_REG.
*/

#define REG(addr)						(*(volatile unsigned int *)(addr))


// 1: Define base address for peripherals
#define PERIPH_BASE 					(0x60000000UL)	// 0x60 00 00 00

// 2: Offset for GPIO
#define GPIO_OFFSET						(0x00004000UL)	// 0x00 00 40 00

// 3: GPIO base address
#define GPIO_BASE						(PERIPH_BASE + GPIO_OFFSET) // 0x60 00 40 00

// 4: Offset for GPIO Out W1TS register
#define GPIO_OUT_W1TS_REG_OFFSET 		(0x0008UL)		// 0x00 08

/* 5: Address of GPIO_OUT_W1TS register
GPIO0~31 output set register. If the value 1 is written to a bit here, the corresponding bit in GPIO_OUT_REG 
will be set to 1. Recommended operation: use this register to set GPIO_OUT_REG.
*/
#define GPIO_OUT_W1TS_REG 				REG(GPIO_BASE + GPIO_OUT_W1TS_REG_OFFSET)

// 6: Offset for GPIO Out W1TC register
#define GPIO_OUT_W1TC_REG_OFFSET 		(0x000CUL)		// 0x00 0C

/* 7: Address of GPIO_OUT_W1TC register
GPIO0~31 output clear register. If the value 1 is written to a bit here, the corresponding bit in GPIO_OUT_REG
will be cleared. Recommended operation: use this register to clear GPIO_OUT_REG.
*/
#define GPIO_OUT_W1TC_REG				REG(GPIO_BASE + GPIO_OUT_W1TC_REG_OFFSET) // Sets the output LOW

// 8: Offset for GPIO_ENABLE_W1TS register
#define GPIO_ENABLE_W1TS_REG_OFFSET 	(0x0024UL)	 	// 0x00 24

/* 9: Address of GPIO_ENABLE_W1TS register
GPIO0~31 output enable set register. If the value 1 is written to a bit here, the corresponding bit in
GPIO_ENABLE_REG will be set to 1. Recommended operation: use this register to set GPIO_ENABLE_REG.
*/
#define GPIO_ENABLE_W1TS_REG			REG(GPIO_BASE + GPIO_ENABLE_W1TS_REG_OFFSET) // Enables output

// 10: Address for GPIO Function Output Selection Configuration Register
#define GPIO_FUNC_OUT_SEL_CFG_REG_(x) 	REG(GPIO_BASE + 0x0554 + 0x4UL * (x))

/* 11: Register portion for selection control
Selection control for GPIO output x. If a value y (0<y<256) is written to this field, the peripheral
output signal y will be connected to GPIO output x. if a value 256 is written to this field, but x of 
GPIO_OUT_REG/GPIO_OUT1_REG and GPIO_ENABLE_REG/GPIO_ENABLE1_REG will be selected as the output value
and output enable.
*/
#define GPIO_FUNC_OUT_SEL_(x)			(0x100UL) // 0x1 00; hex for 256

/* 12: Register portion for enable signal
Use output enable signal from peripheral; 1: Force the output enable signal to be sourced from 
GPIO_ENABLE_REG[x].
*/
#define GPIO_FUNC_OEN_SEL_(x)			(1U << 10) // sets bit 10 to 1

// 13: Alias for GPIO21 representing LED User pin
#define USER_LED    					21	// GPIO21, not sure why this isn't 27...

// 14: LED Mask
#define USER_LED_MASK					(1U << USER_LED)

void delay(volatile uint32_t number_of_seconds) {
	clock_t start_time = clock();
	while (clock() - start_time < number_of_seconds * CLOCKS_PER_SEC);
}

static void led_init(void) {
	GPIO_FUNC_OUT_SEL_CFG_REG_(USER_LED) = GPIO_FUNC_OUT_SEL_(USER_LED) | GPIO_FUNC_OEN_SEL_(USER_LED);
	GPIO_ENABLE_W1TS_REG = USER_LED_MASK;
}

void app_main(void) {
	// Enable LED
	led_init();
	uint i;
	
	while (1) {
		GPIO_OUT_W1TS_REG = USER_LED_MASK; // Set the GPIO pin HIGH, meaning LED is off
		for (i = 0; i < 5; i++) {
			delay(1);
		}
		GPIO_OUT_W1TC_REG = USER_LED_MASK; // Set the GPIO pin LOW, meaning LED is on
		for (i = 0; i < 5; i++) {
			delay(1);
		}		
	}

}
