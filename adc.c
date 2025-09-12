#include <lpc214x.h>
#include "delay.h"              // Custom delay function, assumed to provide delay_us()
#include "pinconnectblock.h"    // Assumed to provide cfgportpinfunc()
#include "adcdefines.h"         // Contains macros like CLKDIV, PDN_BIT, etc.

// Initializes the ADC peripheral
void initadc() {
    // Configure P0.28 as AIN1 (ADC input), which is AD0.1
    cfgportpinfunc(0, 28, 1); // This sets PINSEL1 for P0.28

    // Configure AD0CR register:
    // Set CLKDIV and Power ON (PDN = 1)
    AD0CR = (CLKDIV << CLKDIV_BITS) | (1 << PDN_BIT);
}

// Reads ADC value from specified channel
void readadc(unsigned int chno, unsigned int *adcdval, float *EAR) {
    // Clear previously selected channel (bits 0-7)
    AD0CR &= 0xFFFFFF00;

    // Select channel, start conversion
    AD0CR |= (1 << chno) | (1 << ADC_START_BIT);

    // Small delay for the conversion to take effect
    delay_us(3);

    // Wait until conversion is complete (DONE bit becomes 1)
    while (((AD0GDR >> DONE_BIT) & 1) == 0);

    // Stop ADC conversion
    AD0CR &= ~(1 << ADC_START_BIT);

    // Extract 10-bit result from bits [15:6] (masking to get 10-bit)
    *adcdval = ((AD0GDR >> DIG_DATA_BITS) &1023);

    // Convert to voltage (Assuming Vref = 3.3V)
    *EAR = (*adcdval * (3.3 / 1024));
}

