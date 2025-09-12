#define FOSC    12000000
// Main oscillator frequency in Hz (12 MHz)

#define CCLK  (FOSC*5)
// CPU Clock (CCLK) frequency, typically set by PLL multiplier (here PLL multiplier = 5)
// So, CCLK = 12 MHz * 5 = 60 MHz

#define PCLK  (CCLK/4)
// Peripheral Clock (PCLK) frequency, typically a division of CCLK by 4
// So, PCLK = 60 MHz / 4 = 15 MHz

// RTC Prescaler values calculated based on PCLK and 32.768 kHz RTC clock requirement

#define PREINT_VAL (int)((PCLK/32768)-1)
// Integer part of the RTC prescaler for generating 1-second tick
// Divides PCLK down to 32.768 kHz base clock for RTC

#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768)) 
// Fractional part of the RTC prescaler to fine-tune the RTC clock frequency

// RTC Control Register (CCR) bits
#define RTC_ENABLE  (1<<0)
// Bit to enable the RTC

#define RTC_RESET   (1<<1)
// Bit to reset the RTC

#define RTC_CLKSRC  (1<<4)
// Bit to select RTC clock source (e.g., external 32 kHz oscillator)

