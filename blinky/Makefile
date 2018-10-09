XTENSA_TOOLS_ROOT ?= /Volumes/case-sensitive/esp-open-sdk/xtensa-lx106-elf/bin
SDK_BASE	?= /Volumes/case-sensitive/esp-open-sdk

BUILD_BASE	= build
TARGET		= app
FW_BASE		= firmware

CC := $(XTENSA_TOOLS_ROOT)/xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld

V ?= $(VERBOSE)
ifeq ("$(V)","1")
Q :=
vecho := @true
else
Q := @
vecho := @echo
endif

#MODULES		= driver user
#BUILD_DIR	:= $(BUILD_BASE)

#FW_FILE_1_ADDR	= 0x00000
#FW_FILE_2_ADDR	= 0x40000

.PHONY: all flash clean

all: checkdirs main-0x00000.bin

checkdirs: $(BUILD_BASE) $(FW_BASE)

$(BUILD_BASE):
	$(Q) mkdir -p $@

$(FW_BASE):
	$(Q) mkdir -p $@
	
main-0x00000.bin: main
	esptool.py elf2image -o $(FW_BASE)/ $^

main: main.o

main.o: main.c

flash: main-0x00000.bin
	esptool.py write_flash 0 main-0x00000.bin 0x10000 main-0x10000.bin

clean:
	$(Q) rm -rf $(FW_BASE) $(BUILD_BASE) main
