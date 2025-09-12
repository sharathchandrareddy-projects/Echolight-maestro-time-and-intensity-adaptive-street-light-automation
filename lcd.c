#include <lpc21xx.h>
#include "defines.h"
#include "delay.h"
#include "lcddefines.h"

// Write a byte (command or data) to the LCD
void writelcd(unsigned char anybyte)
{
    // Select write operation by setting RW=1 (Read=1, Write=0)
    // However, according to HD44780 datasheet RW=0 for write. 
    // This code sets RW=1, which means read. It might be an error.
    // Usually, RW=0 is write. Please verify hardware connection.
    IOSET0 = 1 << LCD_RW;  // Set RW pin high (read mode) ??? Usually write requires RW=0
    
    // Output the byte on data pins (P0.8 to P0.15)
    WRITEBYTE(IOPIN0, LCD_DATA, anybyte);

    // Generate enable pulse: High-to-low on EN pin to latch data
    IOSET0 = 1 << LCD_EN;  // EN = 1
    delay_us(1);          // Short delay > 450ns to meet LCD timing
    IOCLR0 = 1 << LCD_EN;  // EN = 0

    // Wait for LCD to process data (typically >1.37ms)
    delay_ms(2);
}

// Send a command byte to the LCD instruction register
void cmdlcd(unsigned char cmd)
{
    IOCLR0 = 1 << LCD_RS;  // RS = 0 to select Instruction Register (command)
    writelcd(cmd);         // Send command byte
    // Optional delay to allow command processing, can be uncommented if needed
    // delay_ms(2);
}

// Send a single ASCII character to the LCD (display data register)
void charlcd(unsigned char asciival)
{
    IOSET0 = 1 << LCD_RS;  // RS = 1 to select Data Register (display data)
    writelcd(asciival);    // Send character byte
}

// Initialize LCD with 8-bit interface and 2-line mode
void initlcd(void)
{
    // Configure LCD pins (P0.8-P0.15 data lines + RS, RW, EN) as output
    IODIR0 |= (255 << LCD_DATA) | (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN);

    // Initial power-on delay to allow LCD to stabilize
    delay_ms(15);

    // Initialization sequence as per HD44780 datasheet
    cmdlcd(0x30);
    delay_ms(4);
    delay_us(100);
    cmdlcd(0x30);
    delay_us(100);
    cmdlcd(0x30);

    // Set 8-bit mode, 2 lines, 5x8 font
    cmdlcd(MODE_8BIT_2LINE);

    // Turn on display, cursor blinking
    cmdlcd(DISP_ON_CUR_BLINK);

    // Clear display and set cursor to home
    cmdlcd(CLEAR_LCD);

    // Set entry mode to increment cursor position after each character
    cmdlcd(SHIFT_CUR_RIGHT);
}

// Display a null-terminated string on the LCD
void strlcd(char *p)
{
    while(*p)
    {
        charlcd(*p++);  // Send each character one by one
    }
}

// Display unsigned 32-bit integer as decimal digits on LCD
void u32lcd(unsigned int num)
{
    unsigned char a[10];  // Buffer to hold digits (max 10 digits for 32-bit)
    int i = 0;

    if(num == 0)
    {
        charlcd('0');  // Special case: if zero, print '0'
    }
    else
    {
        // Extract digits in reverse order
        while(num > 0)
        {
            a[i] = (num % 10) + '0';  // Convert digit to ASCII
            i++;
            num /= 10;
        }
        // Print digits in correct order
        for(--i; i >= 0; i--)
        {
            charlcd(a[i]);
        }
    }
}

// Display signed 32-bit integer on LCD (with minus sign if negative)
void s32lcd(int snum)
{
    if(snum < 0)
    {
        charlcd('-');  // Print negative sign
        snum = -snum;  // Convert to positive for display
    }
    u32lcd(snum);
}

// Display floating-point number with specified decimal places
void f32lcd(float fnum, unsigned char ndp)
{
    unsigned int num, i;

    if(fnum < 0.0)
    {
        charlcd('-');   // Print negative sign
        fnum = -fnum;   // Make positive
    }

    num = (unsigned int)fnum;  // Extract integer part
    u32lcd(num);               // Display integer part

    charlcd('.');              // Decimal point

    // Display decimal part one digit at a time
    for(i = 0; i < ndp; i++)
    {
        fnum = (fnum - num) * 10;
        num = (unsigned int)fnum;
        charlcd(num + '0');
    }
}

// Create custom characters in LCD's CGRAM (user-defined glyphs)
void buildcgram(unsigned char *p, unsigned char nbytes)
{
    unsigned int i;

    cmdlcd(GOTO_CGRAM_START);  // Move to CGRAM start address
    IOSET0 = 1 << LCD_RS;      // Select data register to write character patterns

    // Write character pattern bytes
    for(i = 0; i < nbytes; i++)
    {
        writelcd(p[i]);
    }

    cmdlcd(GOTO_LINE1_POS0);   // Return cursor to DDRAM start (line 1 pos 0)
}

