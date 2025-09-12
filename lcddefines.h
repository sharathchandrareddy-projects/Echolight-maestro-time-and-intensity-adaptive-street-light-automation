// HD44780 LCD Command Codes

#define CLEAR_LCD            0x01  // Clear display and return cursor to home position
#define RET_CUR_HOME         0x02  // Return cursor to home (address 0)
#define SHIFT_CUR_RIGHT      0x06  // Entry mode: cursor moves right after write
#define SHIFT_CUR_LEFT       0x07  // Entry mode: cursor moves left after write
#define DISP_OFF             0x08  // Display OFF, cursor OFF, blink OFF
#define DISP_ON_CUR_OFF      0x0c  // Display ON, cursor OFF, blink OFF
#define DISP_ON_CUR_ON       0x0e  // Display ON, cursor ON, blink OFF
#define DISP_ON_CUR_BLINK    0x0f  // Display ON, cursor ON, blink ON
#define SHIFT_DISP_LEFT      0x10  // Shift entire display left (cursor position unchanged)
#define SHIFT_DISP_RIGHT     0x14  // Shift entire display right (cursor position unchanged)
#define MODE_8BIT_1LINE      0x30  // 8-bit interface, 1 line, 5x8 dots font
#define MODE_4BIT_1LINE      0x20  // 4-bit interface, 1 line, 5x8 dots font
#define MODE_8BIT_2LINE      0x38  // 8-bit interface, 2 lines, 5x8 dots font
#define MODE_4BIT_2LINE      0x28  // 4-bit interface, 2 lines, 5x8 dots font

// DDRAM Addresses for start of each line (for 4-line displays)
#define GOTO_LINE1_POS0      0x80  // Start of Line 1
#define GOTO_LINE2_POS0      0xc0  // Start of Line 2
#define GOTO_LINE3_POS0      0x94  // Start of Line 3 (for 20x4 LCD)
#define GOTO_LINE4_POS0      0xd4  // Start of Line 4 (for 20x4 LCD)

#define GOTO_CGRAM_START     0x40  // Address of CGRAM (Custom Character Generator RAM)



// LCD Pin Connections (mapped to MCU Port 0 pins)

// LCD data pins D0-D7 connected to P0.8 to P0.15
#define LCD_DATA 8    // Base pin for data lines; D0 is on P0.8, D7 on P0.15

// Control pins connected to Port 0 pins
#define LCD_RS   16   // Register Select pin connected to P0.16
#define LCD_RW   18 // Read/Write pin connected to P0.18
#define LCD_EN   17   // Enable pin connected to P0.17

