/**
 * @brief Initialize the RTC module.
 * 
 * Configures and enables the RTC peripheral with appropriate clock and prescaler settings.
 */
void initrtc(void);

/**
 * @brief Retrieve the current RTC date information.
 * 
 * @param date Pointer to store the current day of the month (1-31).
 * @param month Pointer to store the current month (1-12).
 * @param year Pointer to store the current year (four-digit format).
 */
void GetRTCDateInfo(int *date, int *month, int *year);

/**
 * @brief Display the provided date on the LCD.
 * 
 * @param date Day of the month (1-31).
 * @param month Month (1-12).
 * @param year Year (four-digit).
 */
void DisplayRTCDate(unsigned int date, unsigned int month, unsigned int year);

/**
 * @brief Set the RTC time registers.
 * 
 * @param hour Hour to set (0-23).
 * @param minute Minute to set (0-59).
 * @param second Second to set (0-59).
 */
void SetRTCTimeInfo(unsigned int hour, unsigned int minute, unsigned int second);

/**
 * @brief Set the RTC date registers.
 * 
 * @param date Day of the month to set (1-31).
 * @param month Month to set (1-12).
 * @param year Year to set (four-digit).
 */
void SetRTCDateInfo(unsigned int date, unsigned int month, unsigned int year);

/**
 * @brief Retrieve the current day of the week from the RTC.
 * 
 * @param day Pointer to store the day of the week (0=Sunday, ..., 6=Saturday).
 */
void GetRTCDay(int *day);

/**
 * @brief Display the day of the week on the LCD.
 * 
 * @param day Day of the week (0=Sunday, ..., 6=Saturday).
 */
void DisplayRTCDay(unsigned int day);

/**
 * @brief Set the day of the week in the RTC.
 * 
 * @param day Day of the week to set (0=Sunday, ..., 6=Saturday).
 */
void SetRTCDay(unsigned int day);

