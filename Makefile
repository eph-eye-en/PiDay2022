DEVICE     = at90usb162
CLOCK      = 8000000
OBJECTS    = main.o

COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
MAKE_USB = $(MAKE) MCU=$(DEVICE) F_CPU=$(CLOCK) -C USB

# symbolic targets:

all: main test usb

main: main.hex;

test: test.out;

usb: usb.hex;

load: main.hex
	sudo dfu-programmer $(DEVICE) erase
	sudo dfu-programmer $(DEVICE) flash main.hex

.c.o:
	$(COMPILE) -c $< -o $@

load-usb: usb.hex
	sudo dfu-programmer $(DEVICE) erase
	sudo dfu-programmer $(DEVICE) flash usb.hex

clean:
	rm -f main.hex main.elf $(OBJECTS)
	rm -f test.out
	rm -f usb.hex usb.elf
	$(MAKE_USB) clean

# file targets:

main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avr-size --format=avr --mcu=$(DEVICE) main.elf

disasm:	main.elf
	avr-objdump -d main.elf

test.out: test.c pi.c
	gcc test.c -o test.out

usb.elf: USB/usb.c
	$(MAKE_USB) elf
	cp ./USB/usb.elf .

usb.hex: USB/usb.c
	$(MAKE_USB) hex
	cp ./USB/usb.hex .

diasm-usb: usb.elf
	avr-objdump -d usb.elf