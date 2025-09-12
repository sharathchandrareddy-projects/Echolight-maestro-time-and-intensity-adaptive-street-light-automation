#include <lpc21xx.h>

/**
 * @brief Configure the pin function of a specific pin on a given port.
 *
 * LPC21xx microcontrollers use PINSEL registers to select the function of each pin.
 * Each pin uses 2 bits in the PINSEL register to select its function (00, 01, 10, or 11).
 *
 * @param portnum Port number (only port 0 supported in this function).
 * @param pinnum Pin number (0 to 31) within the port.
 * @param pinfunc Function selection value (0 to 3) to set the pin's mode.
 */
void cfgportpinfunc(unsigned int portnum, unsigned int pinnum, unsigned int pinfunc)
{
    if (portnum == 0)  // Only Port 0 handled here
    {
        if ((pinnum >= 0) && (pinnum <= 15))
        {
            // Clear the 2 bits corresponding to the pin in PINSEL0
            // Then set those bits to pinfunc value
            PINSEL0 = (PINSEL0 & ~(3 << (pinnum * 2))) | (pinfunc << (pinnum * 2));
        }
        else if ((pinnum >= 16) && (pinnum <= 31))
        {
            // For pins 16-31, use PINSEL1 register
            // Clear the 2 bits corresponding to (pinnum - 16) in PINSEL1
            // Then set those bits to pinfunc value
            PINSEL1 = (PINSEL1 & ~(3 << ((pinnum - 16) * 2))) | (pinfunc << ((pinnum - 16) * 2));
        }
    }
    // If other ports need to be handled, add code here
}

