/*!
* @file   ssd1315.hpp
* @brief  OLED driven by SSD1315 controller driver
* @author Gavin Lyons.
* @TODO -# Test on 64x32 display size
*/

#pragma once

// Library includes
#include <cstdbool>
#include <span> // C++ 20
#include "display_graphics.hpp"
#include "hardware/i2c.h"

/*!
	@brief class to control OLED and define buffer
*/
class SSD1315 : public displaylib_graphics  {
  public:
	SSD1315(int16_t , int16_t );
	~SSD1315(){};

	static constexpr uint8_t SSD1315_ADDR  = 0x3C;  /**< I2C address, alt 0x3D */

	DisplayRet::Ret_Codes_e OLEDSetBufferPtr(uint8_t width, uint8_t height , std::span<uint8_t> buffer);
	virtual void drawPixel(int16_t x, int16_t y, uint8_t color) override;
	DisplayRet::Ret_Codes_e OLEDupdate(void);
	DisplayRet::Ret_Codes_e OLEDclearBuffer(void);
	void OLEDBuffer(int16_t x, int16_t y, uint8_t w, uint8_t h, std::span<uint8_t> data);
	void OLEDFillScreen(uint8_t pixel, uint8_t mircodelay);
	void OLEDFillPage(uint8_t page_num, uint8_t pixels,uint8_t delay);
	DisplayRet::Ret_Codes_e OLEDBitmap(int16_t x, int16_t y, int16_t w, int16_t h, std::span<const uint8_t> bitmap, bool invert);
	DisplayRet::Ret_Codes_e OLEDbegin(uint8_t I2c_address= SSD1315_ADDR , i2c_inst_t* i2c_type = i2c1 , uint16_t CLKspeed = 100, uint8_t SDApin = 18, uint8_t SCLKpin = 19);
	void OLEDinit();
	void OLEDdeI2CInit(void);
	void OLEDPowerDown(void);

	void OLEDEnable(uint8_t on);
	void OLEDContrast(uint8_t OLEDcontrast);
	void OLEDInvert(bool on);

	void OLEDStartScrollRight(uint8_t start, uint8_t stop);
	void OLEDStartScrollLeft(uint8_t start, uint8_t stop) ;
	void OLEDStartScrollDiagRight(uint8_t start, uint8_t stop) ;
	void OLEDStartScrollDiagLeft(uint8_t start, uint8_t stop) ;
	void OLEDStopScroll(void) ;

	int16_t CheckConnection(void);
	bool GetIsConnected(void);
	void SetIsConnected(bool);
	bool GetDebugMode(void);
	void SetDebugMode(bool);
	uint8_t GetI2CRetryAttemptsNo(void);
	void SetI2CRetryAttemptsNo(uint8_t);
	uint16_t GetI2CRetryDelay(void);
	void SetI2CRetryDelay(uint16_t);
	uint32_t GetI2CTimeout(void);
	void SetI2CTimeout(uint32_t);

  private:

	void I2CWriteByte(uint8_t value = 0x00, uint8_t DataOrCmd =  SSD1315_COMMAND);
	//  === SSD1315 Command Set  ===
	// Fundamental Commands
	static constexpr uint8_t SSD1315_SET_CONTRAST_CONTROL = 0x81;
	static constexpr uint8_t SSD1315_DISPLAY_ALL_ON_RESUME = 0xA4;
	static constexpr uint8_t SSD1315_DISPLAY_ALL_ON = 0xA5;
	static constexpr uint8_t SSD1315_NORMAL_DISPLAY = 0xA6;
	static constexpr uint8_t SSD1315_INVERT_DISPLAY = 0xA7;
	static constexpr uint8_t SSD1315_DISPLAY_OFF = 0xAE;
	static constexpr uint8_t SSD1315_DISPLAY_ON = 0xAF;
	static constexpr uint8_t SSD1315_NOP = 0xE3;

	// Scrolling Commands
	static constexpr uint8_t SSD1315_RIGHT_HORIZONTAL_SCROLL = 0x26;
	static constexpr uint8_t SSD1315_LEFT_HORIZONTAL_SCROLL = 0x27;
	static constexpr uint8_t SSD1315_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL = 0x29;
	static constexpr uint8_t SSD1315_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL = 0x2A;
	static constexpr uint8_t SSD1315_DEACTIVATE_SCROLL = 0x2E;
	static constexpr uint8_t SSD1315_ACTIVATE_SCROLL = 0x2F;
	static constexpr uint8_t SSD1315_SET_VERTICAL_SCROLL_AREA = 0xA3;

	// Addressing Setting Commands
	static constexpr uint8_t SSD1315_SET_LOWER_COLUMN = 0x00;
	static constexpr uint8_t SSD1315_SET_HIGHER_COLUMN = 0x10;
	static constexpr uint8_t SSD1315_MEMORY_ADDR_MODE = 0x20;
	static constexpr uint8_t SSD1315_SET_COLUMN_ADDR = 0x21;
	static constexpr uint8_t SSD1315_SET_PAGE_ADDR = 0x22;

	// Hardware Configuration Commands
	static constexpr uint8_t SSD1315_SET_START_LINE = 0x40;
	static constexpr uint8_t SSD1315_SET_SEGMENT_REMAP = 0xA0;
	static constexpr uint8_t SSD1315_SET_MULTIPLEX_RATIO = 0xA8;
	static constexpr uint8_t SSD1315_COM_SCAN_DIR_INC = 0xC0;
	static constexpr uint8_t SSD1315_COM_SCAN_DIR_DEC = 0xC8;
	static constexpr uint8_t SSD1315_SET_DISPLAY_OFFSET = 0xD3;
	static constexpr uint8_t SSD1315_SET_COM_PINS = 0xDA;
	static constexpr uint8_t SSD1315_CHARGE_PUMP = 0x8D;

	// Timing & Driving Scheme Setting Commands
	static constexpr uint8_t SSD1315_SET_DISPLAY_CLOCK_DIV_RATIO = 0xD5;
	static constexpr uint8_t SSD1315_SET_PRECHARGE_PERIOD = 0xD9;
	static constexpr uint8_t SSD1315_SET_VCOM_DESELECT = 0xDB;

	// Data & command related
	static constexpr uint8_t SSD1315_COMMAND        = 0x00;
	static constexpr uint8_t SSD1315_DATA           = 0xC0;
	static constexpr uint8_t SSD1315_DATA_CONTINUE  = 0x40;

	// Page address Set
	static constexpr uint8_t SSD1315_PAGE_ADDR_0 = 0xB0;
	//  === SSD1315 Command Set END ===

	// I2C
	uint8_t _I2CRetryAttempts = 3; /**< Maximum number of Retry attempts in event of I2C write error*/
	uint16_t _I2CRetryDelay = 100; /**< mS Delay, in between Retry attempts in event of I2C error*/
	uint32_t _TimeoutDelayI2C = 50000; /**< uS delay , I2C timeout*/
	uint8_t _OLEDAddressI2C =  SSD1315_ADDR ; /**< I2C address */
	uint8_t _SDataPin = 18; /**< I2C data GPIO pin  */
	uint8_t _SClkPin = 19;  /**< I2C clock GPIO pin  */
	uint16_t _CLKSpeed = 100; /**< I2C bus speed in khz datasheet */
	i2c_inst_t * _i2c; /**< i2C port number */

	// flags for debugging & status
	bool _bIsConnected = false; /**< is device connected/correct flag */
	bool _bSerialDebugFlag = false; /**< for serial debug I2C errors to console flag */

	// Screen related
	uint8_t _OLED_WIDTH=128;      /**< Width of OLED Screen in pixels */
	uint8_t _OLED_HEIGHT=64;    /**< Height of OLED Screen in pixels */
	uint8_t _OLED_PAGE_NUM=(_OLED_HEIGHT/8); /**< Number of byte size pages OLED screen is divided into */
	std::span<uint8_t> _OLEDbuffer; /**< Buffer to hold screen data */

};
