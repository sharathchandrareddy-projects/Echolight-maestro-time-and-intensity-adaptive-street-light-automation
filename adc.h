/**
 * @brief Initializes the ADC (Analog-to-Digital Converter) module.
 * 
 * Configures the ADC control registers, enables power to the ADC peripheral,
 * and sets the corresponding pins (e.g., P0.28–P0.31) to ADC mode.
 * 
 * Should be called once during system initialization before using the ADC.
 */
void initadc(void);

/**
 * @brief Reads an analog value from a specified ADC channel.
 *
 * This function performs a single ADC conversion on the selected channel,
 * stores the raw 10-bit digital ADC result in *adcdval, and also calculates
 * the corresponding analog voltage (or sensor reading) and stores it in *EAR.
 *
 * @param chno     ADC channel number to read from (0 to 7 depending on MCU).
 * @param adcdval  Pointer to an unsigned int where the 10-bit ADC result is stored.
 * @param EAR      Pointer to a float where the converted analog value (e.g., voltage) is stored.
 */
void readadc(unsigned int chno, unsigned int *adcdval, float *EAR);

