all: flash

clean:
	rm blink.elf blink.hex

blink.elf:
	avr-gcc -mmcu=atmega328p -Wall -Os -o blink.elf hello.c

blink.hex: blink.elf
	avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex

flash: blink.hex
	avrdude -p m328p -c stk500v2 -B 50 -P /dev/cu.usbmodem1411 -e -U flash:w:blink.hex  -v

