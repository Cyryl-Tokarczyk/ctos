CC := i686-elf-gcc
CFLAGS := -I include -m32 -ffreestanding -Wall -Wextra -Werror -mno-red-zone -c

LD := i686-elf-ld
LDFLAGS := -T src/linker.ld -m elf_i386

AS := nasm
ASFLAGS := -f elf32

i386_ASM_SOURCE_FILES := $(shell find src/i386 -name '*.asm')
i386_ASM_OBJECT_FILES := $(patsubst src/i386/%.asm, build/i386/%.o, $(i386_ASM_SOURCE_FILES))

i386_C_SOURCE_FILES := $(shell find src/i386 -name '*.c')
i386_C_OBJECT_FILES := $(patsubst src/i386/%.c, build/i386/%.o, $(i386_C_SOURCE_FILES))

i386_OBJECT_FILES := $(i386_ASM_OBJECT_FILES) $(i386_C_OBJECT_FILES)

COMMON_C_SOURCE_FILES := $(shell find src/common -name '*.c')
COMMON_C_OBJECT_FILES := $(patsubst src/common/%.c, build/common/%.o, $(COMMON_C_SOURCE_FILES))

KERNEL_SOURCE_FILES := $(shell find src/kernel/ -name '*.c')
KERNEL_OBJECT_FILES := $(patsubst src/kernel/%.c, build/kernel/%.o, $(KERNEL_SOURCE_FILES))

all: os.iso

os.iso: iso/boot/kernel.elf
	@xorriso -as mkisofs \
		-R \
		-b boot/grub/stage2_eltorito \
		-no-emul-boot \
		-boot-load-size 4 \
		-A os \
		-boot-info-table \
		-o os.iso \
		-quiet \
		iso

iso/boot/kernel.elf: $(i386_OBJECT_FILES) $(COMMON_C_OBJECT_FILES) $(KERNEL_OBJECT_FILES) src/linker.ld
	$(LD) $(LDFLAGS) $(i386_OBJECT_FILES) $(COMMON_C_OBJECT_FILES) $(KERNEL_OBJECT_FILES) -o $@

build/i386/%.o: src/i386/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

build/i386/%.o: src/i386/%.asm
	mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

build/common/%.o: src/common/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

build/kernel/%.o: src/kernel/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< -o $@

debug: debug.cpp src/common/conversion.c
	g++ -I include debug.cpp src/common/conversion.c -o debug

test:
	echo $(COMMON_C_OBJECT_FILES)

run: os.iso
	qemu-system-i386 -cdrom os.iso -d int,cpu_reset -D qemu.log