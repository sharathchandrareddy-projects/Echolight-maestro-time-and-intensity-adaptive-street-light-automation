/**
 * @brief Configure the function of a specific pin on a given port.
 *
 * This function sets the pin function (GPIO, peripheral functions, etc.) for
 * a specified pin number on the specified port by configuring the PINSEL registers.
 *
 * @param portnum The port number (e.g., 0 for Port 0).
 * @param pinnum The pin number within the port (usually 0 to 31).
 * @param pinfunc The function code to assign to the pin (0 to 3),
 *                which defines the pin’s mode or peripheral function.
 */
void cfgportpinfunc(unsigned int portnum, unsigned int pinnum, unsigned int pinfunc);

