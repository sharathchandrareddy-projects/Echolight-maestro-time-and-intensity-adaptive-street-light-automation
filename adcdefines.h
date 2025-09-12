// ===== Clock Configuration =====

#define FOSC        12000000        // Main oscillator frequency = 12 MHz
#define CCLK        (FOSC * 5)      // CPU Clock = FOSC * PLL multiplier (e.g., M=5) => 60 MHz
#define PCLK        (CCLK / 4)      // Peripheral Clock (PCLK) = CCLK / 4 => 15 MHz
#define ADCCLK      3000000         // Desired ADC clock = 3 MHz (Max allowed for accurate ADC)

// CLKDIV: Determines how much to divide PCLK to get ADCCLK
// Formula from datasheet: ADCCLK = PCLK / (CLKDIV + 1)
// So, CLKDIV = (PCLK / ADCCLK) - 1
#define CLKDIV      ((PCLK / ADCCLK) - 1)  // => (15000000 / 3000000) - 1 = 4

// ===== ADC Control Register (AD0CR) Bit Fields =====

// Bits 15:8 — CLKDIV field — Controls ADC clock division
#define CLKDIV_BITS 8               // CLKDIV is placed starting at bit 8 in AD0CR

// Bit 21 — PDN: Power-down bit — must be set to 1 to enable ADC
#define PDN_BIT     21              // Set this bit to power on the ADC

// Bit 24 — START: Start conversion bit — writing 1 starts conversion
#define ADC_START_BIT 24            // Writing 1 starts conversion on selected channel

// ===== ADC Global Data Register (AD0GDR) Bit Fields =====

// Bits 15:6 — RESULT: 10-bit ADC result stored in bits 15 down to 6
#define DIG_DATA_BITS 6             // The 10-bit ADC result starts at bit 6

// Bit 31 — DONE: Set to 1 when conversion is complete
#define DONE_BIT    31              // Check this bit to see if ADC conversion is done

