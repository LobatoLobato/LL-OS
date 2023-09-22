ASM = i686-elf-as
ASM_FLAGS =
GPP = i686-elf-g++
LD = i686-elf-ld
GPP_FLAGS = -c -I src/interfaces -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

OBJ_DIR = build/obj
OUT_DIR = build/out

i686_asm_source_files := $(shell find src/i686 -name *.asm)
i686_asm_object_files := $(patsubst src/i686/%.asm, $(OBJ_DIR)/i686/%.asm.o, $(i686_asm_source_files))

i686_cpp_source_files := $(shell find src/i686 -name *.cpp)
i686_cpp_object_files := $(patsubst src/i686/%.cpp, $(OBJ_DIR)/i686/%.cpp.o, $(i686_cpp_source_files))

kernel_cpp_source_files := $(shell find src/kernel -name *.cpp)
kernel_cpp_object_files := $(patsubst src/kernel/%.cpp, $(OBJ_DIR)/kernel/%.cpp.o, $(kernel_cpp_source_files))

i686_object_files := $(i686_cpp_object_files) $(i686_asm_object_files)
kernel_object_files := $(kernel_cpp_object_files) 

$(i686_asm_object_files): $(OBJ_DIR)/i686/%.asm.o : src/i686/%.asm
	mkdir -p $(dir $@) && \
	$(ASM) $(ASM_FLAGS) $(patsubst $(OBJ_DIR)/i686/%.asm.o, src/i686/%.asm, $@) -o $@

$(i686_cpp_object_files): $(OBJ_DIR)/i686/%.cpp.o : src/i686/%.cpp
	mkdir -p $(dir $@) && \
	$(GPP) $(GPP_FLAGS) $(patsubst $(OBJ_DIR)/i686/%.cpp.o, src/i686/%.cpp, $@) -o $@ 

$(kernel_cpp_object_files): $(OBJ_DIR)/kernel/%.cpp.o : src/kernel/%.cpp
	mkdir -p $(dir $@) && \
	$(GPP) $(GPP_FLAGS) $(patsubst $(OBJ_DIR)/kernel/%.cpp.o, src/kernel/%.cpp, $@) -o $@ 


.PHONY: build-i686 clean

build-i686: $(kernel_cpp_object_files) $(i686_object_files)
	mkdir -p $(OUT_DIR)/i686 && \
	$(GPP) -T src/i686/linker.ld -o $(OUT_DIR)/i686/kernel.bin -ffreestanding -O2 -nostdlib $(kernel_object_files) $(i686_object_files) -lgcc && \
	mkdir -p $(OUT_DIR)/i686/iso/boot/grub && \
	cp src/i686/boot/grub.cfg $(OUT_DIR)/i686/iso/boot/grub/grub.cfg && \
	cp $(OUT_DIR)/i686/kernel.bin $(OUT_DIR)/i686/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o $(OUT_DIR)/i686/kernel.iso $(OUT_DIR)/i686/iso && \
	rm -rf $(OUT_DIR)/i686/iso

teste:

clean:
	rm -rf build