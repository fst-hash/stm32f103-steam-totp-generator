# stm32f103-steam-totp-generator
A steam Time-based One-Time Password generator for stm32f103.
The MCU is normally in SLEEP mode, unless you wake it up using a button or connect it to a PC via USB.
Time can be changed through a UART connection.
Using Cifra library(https://github.com/ctz/cifra).
