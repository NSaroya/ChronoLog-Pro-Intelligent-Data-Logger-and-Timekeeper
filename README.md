# ChronoLog: Intelligent Data Logger and Timekeeper

## Overview

ChronoLog is an embedded data logger and precision timekeeping system developed by Nikhil Saroya using the ATmega328p microcontroller. This project provides real-time clock data on a serial terminal and supports channel-specific data logging upon user interaction with corresponding buttons. The project features interrupt-driven timekeeping and utilizes the USART (Universal Synchronous and Asynchronous Receiver Transmitter) module for communication.

## File Information

- **File Name:** main.c
- **Author:** Nikhil Saroya
- **Student ID:** 1629920
- **Project ID:** ECE 312 Project 3: Data Logger
- **Created on:** November 12, 2021, 3:11 AM

## Hardware Requirements

- ATmega328p microcontroller
- Serial terminal (for data display)
- Four buttons (for channel selection)
- Crystal oscillator (for clock accuracy)

## Timekeeping

The project employs an interrupt-driven mechanism for timekeeping. The Timer1 interrupt (TIMER1_COMPA_vect) is triggered every tenth of a second, updating the time variables (T, S, M, H, D) accordingly. The time is displayed in the format "D:HH:MM:SS.T" on the serial terminal.

## Channel Selection

The system supports four channels, and the user can select a specific channel by pressing the corresponding button. Upon selection, the current clock time and the channel's identification message are transmitted to the serial terminal.

## Communication

The USART module is initialized for serial communication. The project sends a unique identifier ("Nikhil 1629920") followed by a newline and carriage return as an acknowledgment when the system is powered on.

## Functions

- `Transmit_Format`: Formats and transmits the current clock time to the serial terminal.
- `button_init`: Initializes the buttons used for channel selection.
- `USART_init`: Initializes the USART module for serial communication.
- `wavegenT1_init`: Initializes Timer1 for interrupt-driven timekeeping.
- `USART_Transmit`: Transmits a character through the USART module.
- `USART_Receive`: Receives data through the USART module.
- `button_1`, `button_2`, `button_3`, `button_4`: Checks the status of each button.

## How to Use

1. Connect the ATmega328p microcontroller to the required components.
2. Upload the provided code to the microcontroller.
3. Power on the system.
4. Observe the real-time clock data on the serial terminal.
5. Press buttons 1 to 4 to select different channels and view corresponding information.

## License

This project is open-source and available under the [MIT License](LICENSE). Feel free to modify and adapt the code for your own projects.

For contributions, bug reports, or feedback, please feel free to participate. Happy logging!
