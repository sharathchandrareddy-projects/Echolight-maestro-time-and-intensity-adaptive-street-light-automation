#include <lpc21xx.h>    i    // Include LPC21xx microcontroller definitions
#include "kpmdefines.h"     // Presumably contains custom macros for GPIO
#include "delay.h"          // Presumably contains delay functions
#include "defines.h"        // Additional user-defined macros/constants

// Lookup table for keypad values (4x4 matrix)
unsigned int kpmlut[4][4] = {
    {'1', '2', '3', '/'},    // Row 0
    {'4', '5', '6', '*'},    // Row 1
    {'7', '8', '9', '+'},    // Row 2
    {'c', '0', '=', '-'}     // Row 3
};

/*
 * Initializes the keypad matrix.
 * Rows (P1.16 to P1.19) are configured as output.
 * Columns (P1.20 to P1.23) are inputs by default.
 * Rows are grounded (set to 0) to prepare for scanning.
 */
void initkpm(void)
{
    // Configure P1.16 to P1.19 as output for rows
    WRITEBYTE(IODIR1, ROW0, 15);  // Assuming ROW0 = 16, configures 4 bits (rows)

    // Default all rows to 0 (grounded)
    // This allows column inputs to go low when a key is pressed
}

/*
 * Checks if any column pin (P1.20–P1.23) is low.
 * Returns 0 if any key is pressed (i.e., column goes low), else 1.
 */
unsigned int colscan(void)
{
    unsigned int status;

    // Read 4 bits from P1.20 to P1.23 and check if any are low
    status = (READNIBBLE(IOPIN1, COL0) < 15) ? 0 : 1;  // COL0 assumed to be 20

    return status;
}

/*
 * Scans rows one by one to find which row has the pressed key.
 * Grounds one row at a time and checks columns.
 * Returns the row index (0 to 3) of the pressed key.
 */
unsigned int rowcheck(void)
{
    unsigned int r;

    for (r = 0; r <= 3; r++)
    {
        // Ground one row at a time (active low)
        WRITENIBBLE(IOPIN1, ROW0, ~(1 << r));  // Incorrect: IOPIN1 is read-only

        // Check if any column goes low (i.e., key press detected)
        if (colscan() == 0)
        {
            break;  // Key press detected in row 'r'
        }
    }

    // Reset all rows to default (grounded)
    WRITENIBBLE(IOPIN1, ROW0, 0);  // Incorrect use of IOPIN1 again

    return r;
}

/*
 * After determining the active row, checks which column is low.
 * Returns the column index (0 to 3) where key is pressed.
 */
unsigned int colcheck(void)
{
    unsigned int c;

    for (c = 0; c <= 3; c++)
    {
        if (READBIT(IOPIN1, COL0 + c) == 0)  // Check if column pin is low
        {
            break;
        }
    }

    return c;
}

/*
 * Scans and returns the pressed key value from the keypad.
 * Waits until a key is pressed, identifies row and column,
 * then maps to the character using the lookup table.
 */
unsigned int keyscan(void)
{
    unsigned int c, r, key;

    while (colscan());          // Wait until a key is pressed
    r = rowcheck();             // Identify which row
    c = colcheck();             // Identify which column
    key = kpmlut[r][c];         // Map to character using lookup table

    return key;
}

/*
 * Reads a complete number input from the keypad.
 * Continues reading digits ('0' to '9') and building the number.
 * Stops when a non-digit key (like '=', '+', etc.) is pressed.
 * Stores the final digit in '*key' and the number in '*num'.
 */
void readnum(unsigned int *num, char *key)
{
    *num = 0;  // Initialize number to 0

    while (1)
    {
        *key = keyscan();  // Read key from keypad
          delay_ms(200);
        if (*key >= '0' && *key <= '9')  // If digit
        {
            *num = (*num * 10) + (*key - '0');  // Build the number
            while (colscan() == 0);             // Wait for key release
        }
        else
        {
            while (colscan() == 0);  // Wait for non-digit key release
            break;                   // Exit loop
        }
    }
}

