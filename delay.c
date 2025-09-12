/**
 * @brief Generates a delay in microseconds.
 * 
 * This function uses a simple loop to generate a time delay.
 * The loop count is scaled based on an assumed CPU clock of 12 MHz,
 * where 1 microsecond = ~12 clock cycles.
 *
 * @param dlyus Number of microseconds to delay.
 */
void delay_us(unsigned int dlyus)
{ 
    dlyus *= 12;         // Assuming 1 iteration ≈ 1 clock cycle at 12 MHz
    while (dlyus--);     // Busy-wait loop for the delay
}


/**
 * @brief Generates a delay in milliseconds.
 * 
 * Based on the assumption that 1 ms ≈ 12,000 clock cycles at 12 MHz.
 * This function creates a blocking delay using a loop.
 *
 * @param dlyms Number of milliseconds to delay.
 */
void delay_ms(unsigned int dlyms)
{
    dlyms *= 12000;      // 1 ms = 12,000 cycles at 12 MHz
    while (dlyms--);     // Busy-wait loop
}


/**
 * @brief Generates a delay in seconds.
 * 
 * For a 12 MHz CPU clock, 1 second ≈ 12,000,000 cycles.
 * This delay is not accurate and will vary with compiler optimizations.
 *
 * @param dlys Number of seconds to delay.
 */
void delay_s(unsigned int dlys)
{
    dlys *= 12000000;    // 1 sec = 12,000,000 cycles at 12 MHz
    while (dlys--);      // Busy-wait loop
}

