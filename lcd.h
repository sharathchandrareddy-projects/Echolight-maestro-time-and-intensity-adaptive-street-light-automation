/**
 * @brief Sends a byte (command or data) to the LCD data pins.
 * 
 * This is a low-level function that writes any byte to the LCD,
 * handling the timing, pin control, and data transfer.
 * Typically used internally by other LCD functions.
 *
 * @param anybyte The byte to send to the LCD (command or character data).
 */
void writelcd(unsigned char anybyte);

/**
 * @brief Sends a command byte to the LCD.
 * 
 * Commands control LCD behavior like clearing display,
 * moving cursor, setting display modes, etc.
 *
 * @param cmd The command byte to send (e.g., CLEAR_LCD).
 */
void cmdlcd(unsigned char cmd);

/**
 * @brief Sends a single ASCII character to the LCD for display.
 * 
 * Writes a character to the current cursor position on the LCD.
 *
 * @param asciival The ASCII code of the character to display.
 */
void charlcd(unsigned char asciival);

/**
 * @brief Initializes the LCD module.
 * 
 * Sends the required sequence of commands to set up the LCD
 * (e.g., interface mode, display on/off, cursor mode).
 * Must be called once before using other LCD functions.
 */
void initlcd(void);

/**
 * @brief Displays a null-terminated string on the LCD.
 * 
 * Writes each character of the string sequentially starting
 * at the current cursor position.
 *
 * @param str Pointer to the string to display.
 */
void strlcd(char *str);

/**
 * @brief Displays an unsigned 32-bit integer on the LCD.
 * 
 * Converts the number to decimal ASCII characters and displays it.
 *
 * @param num The unsigned integer to display.
 */
void u32lcd(unsigned int num);

/**
 * @brief Displays a signed 32-bit integer on the LCD.
 * 
 * Converts the signed integer to decimal ASCII characters,
 * including a minus sign if negative, and displays it.
 *
 * @param snum The signed integer to display.
 */
void s32lcd(int snum);

/**
 * @brief Displays a floating-point number on the LCD.
 * 
 * Converts the float to ASCII characters with a specified number
 * of decimal places and displays it.
 *
 * @param fnum The floating-point number to display.
 * @param ndp Number of decimal places to show after the decimal point.
 */
void f32lcd(float fnum, unsigned char ndp);

/**
 * @brief Builds custom characters in the LCD's CGRAM.
 * 
 * Loads custom character data into CGRAM memory of the LCD,
 * allowing creation of user-defined glyphs.
 *
 * @param p Pointer to an array of bytes defining the custom character bitmap.
 * @param nbytes Number of bytes to write (usually 8 bytes per custom char).
 */
void buildcgram(unsigned char *p, unsigned char nbytes);

