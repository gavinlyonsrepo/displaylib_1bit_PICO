/*!
	@file main.cpp
	@author Gavin Lyons
	@brief Test file for SSD1306_OLED library, showing I2C test
	Project Name: SSD1306_OLED_PICO

	@test
		1. Test 1008 I2C interface testing
*/

// === Libraries ===
#include <cstdio>

#include "pico/stdlib.h"
#include "displaylib/ssd1306.hpp"

/// @cond

// Screen settings
#define myOLEDwidth  128
#define myOLEDheight 64
#define myScreenSize (myOLEDwidth * (myOLEDheight/8)) // eg 1024 bytes = 128 * 64/8
uint8_t screenBuffer[myScreenSize]; // Define a buffer to cover whole screen  128 * 64/8

// I2C settings
const uint16_t I2C_Speed = 100;
const uint8_t I2C_Address = 0x3C;

// instantiate  an OLED object
SSD1306 myOLED(myOLEDwidth ,myOLEDheight);

// =============== Function prototype ================
void SetupTest(void);
void Test(void);
void EndTest(void);

// ======================= Main ===================
int main() 
{
	SetupTest();
	Test();
	EndTest();
}
// ======================= End of main  ===================

// ===================== Function Space =====================
void SetupTest() 
{
	stdio_init_all(); // Initialize chosen serial port, default 38400 baud
	busy_wait_ms(500);
	printf("OLED SSD1306 :: Start!\r\n");
	while(myOLED.OLEDbegin(I2C_Address,i2c1,  I2C_Speed, 18, 19) != DisplayRet::Success)
	{
		printf("SetupTest ERROR : Failed to initialize OLED!\r\n");
		busy_wait_ms(1500);
	} // initialize the OLED
	if (myOLED.OLEDSetBufferPtr(myOLEDwidth, myOLEDheight, screenBuffer) != DisplayRet::Success)
	{
		printf("SetupTest : ERROR : OLEDSetBufferPtr Failed!\r\n");
		while(1){busy_wait_ms(1000);}
	} // Initialize the buffer
	myOLED.OLEDFillScreen(0xF0, 0); // splash screen bars
	busy_wait_ms(1000);
}

void Test() 
{
	uint8_t testCount = 0;
	myOLED.SetDebugMode(true);
	while(testCount++ < 25)
	{
		myOLED.OLEDclearBuffer(); 
		myOLED.setFont(pFontDefault);
		myOLED.setCursor(5,5);
		myOLED.print("I2C test!");
		myOLED.setCursor(5,25);
		myOLED.print(testCount);
		myOLED.OLEDupdate();  
		busy_wait_ms(5000);
		printf("Library number %u \n",__LibVerNum__); 
		printf("Debug Mode %s \n",(myOLED.GetDebugMode() ? "true" : "false")); 
		printf("I2C retry attempts %u \n",myOLED.GetI2CRetryAttemptsNo());
		printf("I2C retry Delay %u mS\n",myOLED.GetI2CRetryDelay());
		printf("I2C Timeout %lu uS\n",myOLED.GetI2CTimeout());
		printf("I2C Is connected %s\n", (myOLED.GetIsConnected()  ? "true" : "false"));
		myOLED.CheckConnection();
	}
}

void EndTest()
{
	myOLED.OLEDPowerDown(); // Switch off display
	myOLED.OLEDdeI2CInit(); 
	printf("OLED SSD1306 :: End\r\n");
}

/// @endcond
