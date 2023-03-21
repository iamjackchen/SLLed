default:
	avr-gcc code.c -o code.elf -mmcu=atmega16u2 -DF_CPU=16000000UL -Os
	avr-objcopy code.elf -O ihex code.hex
	sudo avrdude -c flip1 -p m16u2 -U flash:w:"code.hex":a
