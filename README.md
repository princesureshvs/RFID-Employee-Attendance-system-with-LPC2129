# RFID-Employee-Attendance-system-with-LPC2129


This project implements an RFID-based employee attendance system using LPC2129 microcontroller, RFID technology, and an 16x2 LCD display. It utilizes an RTC (Real-Time Clock) module for accurate timekeeping.

## Features

- RFID-based employee identification
- Real-time clock functionality for accurate timekeeping
- Display of time, date, and day on an 16x2 LCD
- Logging of employee entry and exit times
- Supports both entry and exit actions
- Database management for employee information

## Hardware Setup

1. **RFID Module:**
   - VCC to 5V pin of LPC2129
   - GND to GND pin of LPC2129
   - TX to P0.9 pin of LPC2129

2. **RTC Module:**
   - SCL to P0.2 pin of LPC2129
   - SDA to P0.3 pin of LPC2129

3. **16 x 2 Display:**
   - Connect the of the LCD to the corresponding pins of LPC2129 (as like previous voting machine project setup).

## Software Setup

1. **Development Environment:**
   - Use Keil IDE 5 for software development and programming of the LPC2129 microcontroller.

2. **Programming Language:**
   - Write your code in C language to interface with RTC module, and LCD display.

3. **Compilation:**
   - Compile your code using the GCC compiler integrated with Keil IDE.

4. **Serial Communication:**
   - Utilize the UART communication protocol for transmitting RFID card data from LPC2129 to your Linux system via the DB9 cable.

## Operation

1. **Power On:**
   - Power on the system and ensure all components are properly connected.

2. **Programming:**
   - Write and compile your code in Keil IDE, ensuring proper initialization and configuration of peripherals including UART, and RTC.

3. **Serial Terminal Configuration:**
   - Configure the serial terminal on your Linux machine to communicate with the LPC2129 microcontroller via the DB9 cable.

4. **RFID Scanning:**
   - Scan an employee RFID card to register entry or exit. The RFID module will transmit the card data to the LPC2129 microcontroller.

5. **LCD Display:**
   - Monitor the LCD display for real-time updates on employee attendance, time, and date.

6. **Data Logging:**
   - Ensure proper logging of entry and exit times in the database, updating the attendance log accordingly.

## Usage

1. Power on the system and ensure all components are properly connected.
2. Write and compile your code in Keil IDE.
3. Configure the serial terminal on your Linux machine to communicate with the LPC2129 microcontroller via the DB9 cable.
4. Scan an employee RFID card to register entry or exit.
5. Monitor the LCD display for real-time updates on employee attendance.
6. Review the attendance log in the database for further analysis.

## Contributing

Contributions are welcome! Feel free to fork this repository and submit pull requests with any improvements or enhancements.
