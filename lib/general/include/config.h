#pragma once
#include <stdint.h>

#define OUTPUT_PIN ((uint8_t)OUTPUT)        // GPIO pin used for output, set in CMakeLists.txt
#define STATUS_PIN 21                       // GPIO pin used for status LED, used for heart beat indication

#define BAUDRATE 115200

// Default values for the pulse widths and intervals. These can be updated by sending a JSON string with the new values over UART. But may not be bigger than 255.
#define DEFAULT_PULSE_WIDTH1 70
#define DEFAULT_INTER_PULSE_DELAY 30
#define DEFAULT_PULSE_WIDTH2 50
#define DEFAULT_PULSE_INTERVAL 200
extern volatile uint8_t Intervals[];        // Array to hold the intervals
#define MAX_INTERVAL 255                    // Maximum allowed value for pulse widths and intervals, based on the fact that we are using uint8_t to store these values in the bitstream for the PWM signal.

#define BITSTREAM_WORDS 256                 // Maximum number of 32-bit words in the bitstream for the PWM signal, this limits the maximum pulse interval and pulse widths we can generate. 
                                            // We need to make sure that the total number of bits in the bitstream does not exceed BITSTREAM_WORDS * 32 bits.
extern volatile uint32_t bitstream[BITSTREAM_WORDS]; // We will use this to store the bitstream for the PWM signal

#define TRIGGER_PULSE_BITS 8                // Width of the scope trigger pulse in PWM bit ticks.

#define CPUID_REG (*(volatile uint32_t *)0xE000ED00)

#define BLINK_TIMER 100000

#define JSON_TIMEOUT_US 50000              // Timeout for receiving a full JSON string, in microseconds (at 115200 baud, one byte is ~87 microseconds)

