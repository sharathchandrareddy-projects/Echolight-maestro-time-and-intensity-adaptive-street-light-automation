#include "lpc21xx.h"
#include "lcddefines.h"
#include "lcd.h"
#include "rtcdefines.h"

// Array of strings representing weekdays for display
char week[][4] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};

/**
 * @brief Initialize the RTC peripheral
 * 
 * Disables and resets the RTC, configures prescaler values, and enables RTC with the proper clock source.
 */
void initrtc(void) 
{
    // Disable and reset the RTC (clear CCR register with reset bit)
    CCR = RTC_RESET;
    
    // Set prescaler integer and fractional values to generate 1-second tick
    PREINT = PREINT_VAL;
    PREFRAC = PREFRAC_VAL;

    // Enable RTC and select clock source depending on MCU variant
    #ifndef _LPC2148_
        CCR = RTC_ENABLE; // Enable RTC with default clock source
    #else
        CCR = RTC_ENABLE | RTC_CLKSRC; // Enable RTC with external clock source for LPC2148
    #endif
}

/**
 * @brief Get the current RTC time values (hour, minute, second)
 * 
 * @param hour Pointer to store current hour (0-23)
 * @param minute Pointer to store current minute (0-59)
 * @param second Pointer to store current second (0-59)
 */
void GetRTCTimeInfo(int *hour, int *minute, int *second)
{
    *hour = HOUR;
    *minute = MIN;
    *second = SEC;
}

/**
 * @brief Display the RTC time on the LCD in HH:MM:SS format
 * 
 * @param hour Hour value (0-23)
 * @param minute Minute value (0-59)
 * @param second Second value (0-59)
 */
void DisplayRTCTime(unsigned int hour, unsigned int minute, unsigned int second)
{
    cmdlcd(GOTO_LINE1_POS0); // Move cursor to beginning of first LCD line
    
    // Display two digit hour
    charlcd((hour / 10) + '0');
    charlcd((hour % 10) + '0');
    charlcd(':');
    
    // Display two digit minute
    charlcd((minute / 10) + '0');
    charlcd((minute % 10) + '0');
    charlcd(':');
    
    // Display two digit second
    charlcd((second / 10) + '0');
    charlcd((second % 10) + '0');
}

/**
 * @brief Get the current RTC date values (date, month, year)
 * 
 * @param date Pointer to store day of month (1-31)
 * @param month Pointer to store month (1-12)
 * @param year Pointer to store year (four digit format)
 */
void GetRTCDateInfo(int *date, int *month, int *year)
{
    *date = DOM;
    *month = MONTH;
    *year = YEAR;
}

/**
 * @brief Display the RTC date on the LCD in DD/MM/YYYY format
 * 
 * @param date Day of month (1-31)
 * @param month Month (1-12)
 * @param year Year (4 digits)
 */
void DisplayRTCDate(unsigned int date, unsigned int month, unsigned int year)
{
    cmdlcd(GOTO_LINE2_POS0); // Move cursor to beginning of second LCD line

    // Display day of month (two digits)
    charlcd((date / 10) + '0');
    charlcd((date % 10) + '0');
    charlcd('/');

    // Display month (two digits)
    charlcd((month / 10) + '0');
    charlcd((month % 10) + '0');
    charlcd('/');

    // Display full year as decimal number
    u32lcd(year);
}

/**
 * @brief Set the RTC time registers with provided hour, minute, second
 * 
 * @param hour Hour to set (0-23)
 * @param minute Minute to set (0-59)
 * @param second Second to set (0-59)
 */
void SetRTCTimeInfo(unsigned int hour, unsigned int minute, unsigned int second)
{
    HOUR = hour;
    MIN = minute;
    SEC = second;
}

/**
 * @brief Set the RTC date registers with provided day, month, and year
 * 
 * @param date Day of month to set (1-31)
 * @param month Month to set (1-12)
 * @param year Year to set (four digits)
 */
void SetRTCDateInfo(unsigned int date, unsigned int month, unsigned int year)
{
    DOM = date;
    MONTH = month;
    YEAR = year;
}

/**
 * @brief Get the current day of the week from RTC (0=Sunday, ..., 6=Saturday)
 * 
 * @param day Pointer to store Day of Week
 */
void GetRTCDay(int *day)
{
    *day = DOW;
}

/**
 * @brief Display the current day of the week on the LCD
 * 
 * @param day Day of week (0=Sunday, ..., 6=Saturday)
 */
void DisplayRTCDay(unsigned int day)
{
    cmdlcd(GOTO_LINE1_POS0 + 10); // Position cursor suitably on first line
    strlcd(week[day]);            // Display the 3-letter day abbreviation
}

/**
 * @brief Set the RTC day of the week register
 * 
 * @param day Day of week to set (0=Sunday, ..., 6=Saturday)
 */
void SetRTCDay(unsigned int day)
{
    DOW = day;
}

