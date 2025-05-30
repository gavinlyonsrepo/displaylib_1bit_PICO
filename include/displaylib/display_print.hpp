/*!
	@file  display_print.hpp
	@brief Base class that provides print() and println() for 1-bit color displays. library
	@details supports integers with base number formatting, floats with precision formatting
		character array and std::string
	@note  Port of arduino built-in print class, G Lyons 2022.
*/

#pragma once

#include <cstdint>
#include <cstdio> // for size_t
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <string>
#include <array>
#include "display_data.hpp"

/*!
	@brief class that provides polymorphic print methods for printing data
*/
class Print
{
	private:
		int write_error;
		size_t printNumber(unsigned long, uint8_t);
		size_t printFloat(double, uint8_t);
	protected:
		void setWriteError(int err = 1) { write_error = err; }
	public:
		/*! Base number type */
		enum BaseNum : uint8_t{
			DEC = 10, /**< Decimal*/
			HEX = 16, /**< Hexadecimal */
			OCT = 8,  /**< Octal */
			BIN = 2   /**<  Binary */
		};

		Print() : write_error(0) {}

		/*!
			@brief  gets the error flag status, zero no error
		*/
		int getWriteError() { return write_error; }
		/*! 
			@brief clears the errof flag by setting it to zero
		*/
		void clearWriteError() { setWriteError(0); }
		/*! 
			@brief writes a character to display , defined in the sub class
		*/
		virtual size_t write(uint8_t) = 0;
		size_t write(const char *str) {
			if (str == nullptr) 
			{
				setWriteError(DisplayRet::CharArrayNullptr); //_CharArrayNullptr
				return 0;
			}
			clearWriteError();
			return write((const uint8_t *)str, strlen(str));
		}
		virtual size_t write(const uint8_t *buffer, size_t size);
		size_t write(const char *buffer, size_t size) {
			return write((const uint8_t *)buffer, size);
		}

		// default to zero, meaning "a single write may block"
		// should be overriden by subclasses with buffering
		virtual int availableForWrite() { return 0; }

		size_t print(const char[]);
		size_t print(char);
		size_t print(int, int = DEC);
		size_t print(unsigned int, int = DEC);
		size_t print(long, int = DEC);
		size_t print(unsigned long, int = DEC);
		size_t print(double, int = 2);
		size_t print(const std::string &);

		size_t println(const char[]);
		size_t println(char);
		size_t println(int, int = DEC);
		size_t println(unsigned int, int = DEC);
		size_t println(long, int = DEC);
		size_t println(unsigned long, int = DEC);
		size_t println(double, int = 2);
		size_t println(void);
		size_t println(const std::string &s);
};
