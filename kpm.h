// Initializes the keypad matrix hardware
// Configures row pins as output and column pins as input
void initkpm(void);

// Checks if any column pin is active (i.e., a key is pressed)
// Returns 0 if a key press is detected (any column goes low), else returns 1
unsigned int colscan(void);

// Scans rows one at a time by grounding them to detect which row has the key press
// Returns the index (0–3) of the active row
unsigned int rowcheck(void);

// After row is found, checks which column line is low (pressed)
// Returns the index (0–3) of the active column
unsigned int colcheck(void);

// Performs a full key scan: waits for key press, detects row and column,
// maps to the corresponding character using the lookup table
unsigned int keyscan(void);

// Reads a multi-digit number from the keypad
// Stops when a non-digit key is pressed
// Stores the result in the integer pointer (*num), and the terminating key in (*key)
void readnum(int *num, char *key);

