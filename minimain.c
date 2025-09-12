#include <lpc21xx.h>
#include "lcd.h"
#include "lcddefines.h"
#include "rtc.h"
#include "rtcdefines.h"
#include "pinconnectblock.h"
#include "delay.h"
#include "kpm.h"
#include "adc.h"

// Pin function and interrupt definitions
#define pinfunc4 3             // Pin function mode 4 (GPIO or peripheral function)
#define eint0_pin_func pinfunc4 // External interrupt 0 pin function
#define eint0_pin 1            // External interrupt 0 on pin P0.1
#define eint0_vic_chno 14      // VIC channel number for external interrupt 0
#define light 4                // Light connected to P0.4

unsigned int interrupt(void);
void Eint0_isr(void)__irq ;     // ISR for external interrupt 0

// Global variables to hold RTC time/date and ADC value
unsigned int hour, minute, sec, date, month, year, day, adcdval;
float EAR;

int main()
{
    initlcd();                 // Initialize LCD
    initrtc();                // Initialize RTC
    initadc();                 // Initialize ADC

    IODIR0 |= 1 << light;      // Configure P0.4 as output (light control)

    // Configure pin function for external interrupt 0 (P0.1)
    cfgportpinfunc(0, 1, eint0_pin_func);

    // Enable VIC interrupt for EINT0
    VICIntEnable = 1 << eint0_vic_chno;

    // Configure VIC vector control for EINT0 interrupt
    VICVectCntl0 = (1 << 5) | eint0_vic_chno;

    // Assign ISR to VIC vector address 0
    VICVectAddr0 = (unsigned int)Eint0_isr;

    // Configure EINT0 for edge-triggered interrupt (falling edge default)
    EXTMODE = 1 << 0;

    // Display initial message on LCD
    strlcd("rtc info");
    cmdlcd(CLEAR_LCD);

    // Set initial RTC time (05:59:55)
   // SetRTCTimeInfo(05, 59, 55);

    while (1)
    {
        // Display current time on LCD Line 1
        cmdlcd(GOTO_LINE1_POS0);
        GetRTCTimeInfo(&hour, &minute, &sec);
        DisplayRTCTime(hour, minute, sec);

        // Display current date on LCD Line 2
        GetRTCDateInfo(&date, &month, &year);
        cmdlcd(GOTO_LINE2_POS0);
        DisplayRTCDate(date, month, year);

        // Display current day of week on LCD Line 1, position 8
        GetRTCDay(&day);
        cmdlcd(GOTO_LINE1_POS0 + 8);
        DisplayRTCDay(day);

        // Control light based on time and ambient light
        if ((hour >= 18) || (hour < 6))
        {
            readadc(1, &adcdval, &EAR); // Read ADC channel 1 for light sensor
            EAR = EAR * 100;

            if (EAR > 300)
            {
                IOSET0 = 1 << light;   // Turn ON light if ambient light is low
            }
            else
                IOCLR0 = 1 << light;   // Turn OFF light otherwise
        }
        else
            IOCLR0 = 1 << light;       // Daytime, light OFF
    }
}

// External interrupt 0 ISR
void Eint0_isr(void) __irq
{
    interrupt();              // Call interrupt handler function
}

// Interrupt handler for user to set time, date, day or exit
unsigned int interrupt(void)
{
    unsigned int hr, min, sec, date, mon, yr, day;
    char key, ch;

    initkpm();                // Initialize keypad
    cmdlcd(CLEAR_LCD);
    strlcd("set time");
    delay_ms(1000);

    while (1)
    {
        cmdlcd(GOTO_LINE1_POS0);
        strlcd("1.time,2.date");
        cmdlcd(GOTO_LINE2_POS0);
        strlcd("3.day,4.exit");

        ch = keyscan();       // Scan keypad for choice
        delay_ms(200);
        while (colscan() == 0); // Wait for key release

        switch (ch)
        {
        case '1': // Set Time
            cmdlcd(CLEAR_LCD);
            cmdlcd(GOTO_LINE2_POS0);
            strlcd("enter hour");
            readnum(&hr, &key);
            cmdlcd(GOTO_LINE1_POS0);
            u32lcd(hr);
            delay_ms(500);

            cmdlcd(GOTO_LINE2_POS0);
            strlcd("                "); // Clear line
            cmdlcd(GOTO_LINE2_POS0);
            strlcd("enter min");
            readnum(&min, &key);
            cmdlcd(GOTO_LINE1_POS0 + 2);
            charlcd(':');
            cmdlcd(GOTO_LINE1_POS0 + 3);
            u32lcd(min);
            delay_ms(500);

            cmdlcd(GOTO_LINE2_POS0);
            strlcd("                ");
            cmdlcd(GOTO_LINE2_POS0);
            strlcd("enter sec");
            readnum(&sec, &key);
            cmdlcd(GOTO_LINE1_POS0 + 6);
            charlcd(':');
            u32lcd(sec);

            SetRTCTimeInfo(hr, min, sec); // Update RTC time
            break;

        case '2': // Set Date
            cmdlcd(CLEAR_LCD);
            cmdlcd(GOTO_LINE2_POS0);
            strlcd("enter date");
            readnum(&date, &key);

            cmdlcd(CLEAR_LCD);
            cmdlcd(GOTO_LINE2_POS0);
            strlcd("enter month");
            readnum(&mon, &key);

            cmdlcd(CLEAR_LCD);
            cmdlcd(GOTO_LINE2_POS0);
            strlcd("enter year");
            readnum(&yr, &key);

            SetRTCDateInfo(date, mon, yr); // Update RTC date
            break;

        case '3': // Set Day
            cmdlcd(CLEAR_LCD);
            cmdlcd(GOTO_LINE2_POS0);
            strlcd("enter day");
            readnum(&day, &key);

            SetRTCDay(day); // Update RTC day of week
            break;

        case '4': // Exit
            cmdlcd(CLEAR_LCD);
            EXTINT = 1 << 0;     // Clear external interrupt flag
            VICVectAddr = 0;     // Signal end of interrupt
            return 0;
        }

        cmdlcd(CLEAR_LCD);
        EXTINT = 1 << 0;         // Clear external interrupt flag after operation
        VICVectAddr = 0;         // Signal end of interrupt
    }
}

