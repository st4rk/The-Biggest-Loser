include $(DEVKITARM)/ds_rules

OBJDUMP	:=	$(PREFIX)objdump

all: flawUS.sav flawEU.sav

flawUS.sav flawEU.sav: payloadUS.bin payloadEU.bin
	python inject_payload.py
	CRCFix/CRCFix flawUS.sav
	CRCFix/CRCFix flawEU.sav
	@rm -f payloadUS.bin
	@rm -f payloadEU.bin

payloadUS.bin: *.c
	$(CC) -nostartfiles -nostdlib -DARM9 -I$(LIBNDS)/include *.c -o payload.elf -O2 -Wall -Ttext=0x0211E364
	$(OBJCOPY) -O binary payload.elf payloadUS.bin
	@rm -f payload.elf

payloadEU.bin: *.c
	$(CC) -nostartfiles -nostdlib -DARM9 -I$(LIBNDS)/include *.c -o payload.elf -O2 -Wall -Ttext=0x0211E604
	$(OBJCOPY) -O binary payload.elf payloadEU.bin
	@rm -f payload.elf
