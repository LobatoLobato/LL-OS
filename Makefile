ASM = nasm
ASM_FLAGS =  -f elf64

GCC = x86_64-elf-gcc
LD = x86_64-elf-ld
GCC_FLAGS = -c -I src/interfaces -ffreestanding

OBJ_DIR = build/obj
OUT_DIR = build/out

x86_64_asm_source_files := $(shell find src/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/x86_64/%.asm, $(OBJ_DIR)/x86_64/%.asm.o, $(x86_64_asm_source_files))

x86_64_c_source_files := $(shell find src/x86_64 -name *.c)
x86_64_c_object_files := $(patsubst src/x86_64/%.c, $(OBJ_DIR)/x86_64/%.c.o, $(x86_64_c_source_files))

x86_64_cpp_source_files := $(shell find src/x86_64 -name *.cpp)
x86_64_cpp_object_files := $(patsubst src/x86_64/%.cpp, $(OBJ_DIR)/x86_64/%.cpp.o, $(x86_64_cpp_source_files))

kernel_c_source_files := $(shell find src/kernel -name *.c)
kernel_c_object_files := $(patsubst src/kernel/%.c, $(OBJ_DIR)/kernel/%.c.o, $(kernel_c_source_files))

kernel_cpp_source_files := $(shell find src/kernel -name *.cpp)
kernel_cpp_object_files := $(patsubst src/kernel/%.cpp, $(OBJ_DIR)/kernel/%.cpp.o, $(kernel_cpp_source_files))

x86_64_object_files := $(x86_64_cpp_object_files) $(x86_64_c_object_files) $(x86_64_asm_object_files)
kernel_object_files := $(kernel_cpp_object_files) $(kernel_c_object_files)

$(x86_64_c_object_files): $(OBJ_DIR)/x86_64/%.c.o : src/x86_64/%.c
	mkdir -p $(dir $@) && \
	$(GCC) $(GCC_FLAGS) $(patsubst $(OBJ_DIR)/x86_64/%.c.o, src/x86_64/%.c, $@) -o $@

$(x86_64_cpp_object_files): $(OBJ_DIR)/x86_64/%.cpp.o : src/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	$(GCC) $(GCC_FLAGS) $(patsubst $(OBJ_DIR)/x86_64/%.cpp.o, src/x86_64/%.cpp, $@) -o $@ 

$(kernel_c_object_files): $(OBJ_DIR)/kernel/%.c.o : src/kernel/%.c
	mkdir -p $(dir $@) && \
	$(GCC) $(GCC_FLAGS) $(patsubst $(OBJ_DIR)/kernel/%.c.o, src/kernel/%.c, $@) -o $@

$(kernel_cpp_object_files): $(OBJ_DIR)/kernel/%.cpp.o : src/kernel/%.cpp
	mkdir -p $(dir $@) && \
	$(GCC) $(GCC_FLAGS) $(patsubst $(OBJ_DIR)/kernel/%.cpp.o, src/kernel/%.cpp, $@) -o $@ 

$(x86_64_asm_object_files): $(OBJ_DIR)/x86_64/%.asm.o : src/x86_64/%.asm
	mkdir -p $(dir $@) && \
	$(ASM) $(ASM_FLAGS) $(patsubst $(OBJ_DIR)/x86_64/%.asm.o, src/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64 clean
build-x86_64: $(kernel_cpp_object_files) $(x86_64_object_files)
	mkdir -p $(OUT_DIR)/x86_64 && \
	$(LD) -Map=$(OBJ_DIR)/obj.map -n -o $(OUT_DIR)/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	cp $(OUT_DIR)/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	sudo grub-mkrescue /usr/lib/grub/i386-pc -o $(OUT_DIR)/x86_64/kernel.iso targets/x86_64/iso && \
	rm -rf targets/x86_64/iso/boot/kernel.bin

clean:
	rm -rf build