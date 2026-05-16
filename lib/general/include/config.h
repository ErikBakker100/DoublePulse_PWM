#pragma once
#include <stdint.h>

#define OUTPUT_PIN 18                       // GPIO pin used for output
#define TRIGGER_PIN 19                      // GPIO pin used for triggering scope on second channel
#define STATUS_PIN 21                       // GPIO pin used for status LED, used for heart beat indication

#define BAUDRATE 115200

// Default values for the pulse widths and intervals. These can be updated by sending a JSON string with the new values over UART.
#define DEFAULT_PULSE_WIDTH1 70
#define DEFAULT_INTER_PULSE_DELAY 30
#define DEFAULT_PULSE_WIDTH2 50
#define DEFAULT_PULSE_INTERVAL 200
extern volatile uint16_t Intervals[];       // Array to hold the intervals (16-bit values)
#define MAX_INTERVAL 65535                  // Maximum allowed value for pulse widths and intervals (uint16_t)

// Maximum number of 32-bit words in the bitstream for the PWM signal.
// Increased to support 16-bit intervals (worst-case total bits up to ~262k).
#define BITSTREAM_WORDS 9000                // ~9000 * 4 = 36 KB buffer
                                            // Ensure BITSTREAM_WORDS * 32 bits can hold the expanded pattern.
extern volatile uint32_t bitstream[BITSTREAM_WORDS]; // We will use this to store the bitstream for the PWM signal

#define CPUID_REG (*(volatile uint32_t *)0xE000ED00)

#define BLINK_TIMER 100000

#define JSON_TIMEOUT_US 50000              // Timeout for receiving a full JSON string, in microseconds (at 115200 baud, one byte is ~87 microseconds)

