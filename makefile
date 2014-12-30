include $(DEVKITARM)/ds_rules

OBJDUMP	:=	$(PREFIX)objdump


all: exploit


exploit:
	$(CC) -nostartfiles -nostdlib *.c -o exploit.elf -Ttext=0x0211E3E0
	$(OBJCOPY) -O binary exploit.elf exploit.bin
	@rm -f exploit.elf
	