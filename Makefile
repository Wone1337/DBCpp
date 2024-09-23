COMPILER = nasm

LINKER = ld

TARGET = *

TARGET_NAME = main

TARGET_TO_DIR = ASM_MAKE/

all:	$(TARGET).asm
		$(COMPILER) -f elf64  $(TARGET).asm 
		$(LINKER) -o $(TARGET_NAME) $(TARGET_NAME).o
		mv $(TARGET_NAME).o $(TARGET_NAME) $(TARGET_TO_DIR)



clean:
		$(RM) -i  $(TARGET_TO_DIR)$(TARGET)
