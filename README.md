# RTC-Based Smart Light Controller (LPC21xx)

This project implements a **real-time clock (RTC)-based smart lighting system** on the **LPC21xx ARM7 microcontroller**.  
It integrates an LCD display, a keypad, an ADC-based light sensor, and an external interrupt for setting date and time.  

The system automatically turns a light ON/OFF based on the **time of day** and **ambient light levels**.

---

## ✨ Features
- **RTC Display**  
  - Continuously displays the current time, date, and day of the week on a 16x2 LCD.  

- **Smart Light Control**  
  - Turns ON the light (connected to P0.4) between **6 PM – 6 AM** if ambient light (from ADC sensor) is below a threshold.  
  - Keeps the light OFF during daytime.  

- **User Interaction via Interrupt & Keypad**  
  - External interrupt (on **P0.1**) allows the user to set time, date, and day.  
  - Keypad-driven menu system for user inputs.  

- **LCD Menu System**  
  - Menu-driven interface for setting time, date, and day.  

---

## 🛠️ Hardware Requirements
- **LPC21xx ARM7 Microcontroller**
- **16x2 LCD** (connected via `lcd.h` driver)  
- **RTC Module** (integrated in LPC21xx, controlled via `rtc.h`)  
- **Keypad Matrix** (for user input, controlled via `kpm.h`)  
- **ADC-based Light Sensor** (connected to ADC channel 1)  
- **External Interrupt (EINT0)** on pin **P0.1**  
- **Light (LED or Relay)** connected to **P0.4**

---

## 📂 File Structure
├── minimain.c # Main source file
├── lcd.h / lcddefines.h # LCD driver and macros
├── rtc.h / rtcdefines.h # RTC driver and macros
├── pinconnectblock.h # Pin configuration definitions
├── delay.h # Delay functions
├── kpm.h # Keypad driver
├── adc.h # ADC driver

---

## 🚀 How It Works
1. **System Initialization**  
   - LCD, RTC, ADC, and GPIO are initialized.  
   - External interrupt (EINT0) configured on pin P0.1.  

2. **Normal Operation**  
   - LCD shows current **time, date, and day**.  
   - Light automatically toggles depending on **RTC time** and **ambient light (ADC value)**.  

3. **Interrupt Mode (Set Parameters)**  
   - Triggered by pressing the external interrupt key (EINT0).  
   - Menu allows setting:  
     - `1` → Time  
     - `2` → Date  
     - `3` → Day  
     - `4` → Exit  

---

## ⚡ Usage Instructions
1. Flash the code into the LPC21xx microcontroller.  
2. Connect the hardware as per pin mappings:  
   - Light → P0.4  
   - EINT0 → P0.1  
   - ADC input → ADC Channel 1  
   - LCD & keypad as per drivers.  
3. On startup, the LCD displays RTC info.  
4. To update time/date/day, press the **interrupt button** (connected to P0.1).  
5. The smart light system runs automatically based on settings.  

---
