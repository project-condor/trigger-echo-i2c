##
## Makefile to create firmware image based on mux
##
##

# CPU model
#
MCU=attiny45


# CPU Frequency
#
F_CPU=10000000L


# Serial port used for uploading
#
SERIAL=/dev/ttyACM1
BAUD=115200


# Name of image to produce (can be arbitrary)
#
TARGET=firmware


# Toolchain and flags
#
CC=avr-gcc
CFLAGS= -g -std=gnu99 -Os -Wall -finline-functions -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -mmcu=$(MCU) -DF_CPU=$(F_CPU)

LD=avr-gcc
LDFLAGS= -Wl,--gc-sections,--relax -mmcu=$(MCU)
AR=avr-ar
AS=avr-as
ASFLAGS=-mmcu=$(MCU)
OC=avr-objcopy
OCFLAGS=
OD=avr-objdump
AVRDUDE=avrdude
AVRDUDEFLAGS= -p $(MCU) -P S(SERIAL) -b 19200 -c avrisp
AVRSIZE=avr-size

# Derived variables
SOURCEDIRS=. sys

INCLUDES=. sys

SOURCES=\
	$(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.c)) \
	$(foreach dir,$(SOURCEDIRS),$(wildcard $(dir)/*.S))

OBJECTS=$(addsuffix .o, $(basename $(SOURCES)))

# Rules
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	$(OC) $(OCFLAGS) -O ihex -R .eeprom $< $@

$(TARGET).elf: $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $^

# Sources
%.o: %.S
	$(CC) $(CFLAGS) -I$(dir $<) $(addprefix -I, $(INCLUDES)) -o $@ -c $<

%.o: %.c
	$(CC) $(CFLAGS) -I$(dir $<) $(addprefix -I, $(INCLUDES)) -o $@ -c $<

# Utility rules
size: $(TARGET).hex
	$(AVRSIZE) --format=avr --mcu=$(MCU) $(TARGET).elf

upload: $(TARGET).hex
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$(TARGET).hex:i

clean:
	@rm -f *.o
	@for dir in $(SOURCEDIRS); do \
		rm -f $$dir/*.o; \
		rm -f $$dir/*.s-gen; \
	done
	@rm -f $(TARGET).hex
	@rm -f $(TARGET).elf

.PHONY: clean
