################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 11
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
bootloader_Z4_0.elf \

EXECUTABLES_QUOTED += \
"bootloader_Z4_0.elf" \

EXECUTABLES_OS_FORMAT += \
bootloader_Z4_0.elf \

SECONDARY_FLASH += \
bootloader_Z4_0.srec \

SECONDARY_FLASH_QUOTED += \
"bootloader_Z4_0.srec" \

SECONDARY_FLASH_OS_FORMAT += \
bootloader_Z4_0.srec \

SECONDARY_LIST += \
bootloader_Z4_0.lst \

SECONDARY_LIST_QUOTED += \
"bootloader_Z4_0.lst" \

SECONDARY_LIST_OS_FORMAT += \
bootloader_Z4_0.lst \


# All Target
all: warning-messages explicit-dependencies bootloader_Z4_0.elf secondary-outputs

# Tool invocations
bootloader_Z4_0.elf: $(OBJS) D:/boot/bootloader/bootloader_Z4_0/Project_Settings/Linker_Files/57xx_flash.ld D:/boot/bootloader/bootloader_Z4_0/Project_Settings/Linker_Files/libs.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #12 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "bootloader_Z4_0.elf" "@bootloader_Z4_0.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

bootloader_Z4_0.srec: $(EXECUTABLES)
	@echo 'Executing target #13 $@'
	@echo 'Invoking: Standard S32DS Create Flash Image'
	powerpc-eabivle-objcopy -O srec $(EXECUTABLES)  "bootloader_Z4_0.srec"
	@echo 'Finished building: $@'
	@echo ' '

bootloader_Z4_0.lst: $(EXECUTABLES)
	@echo 'Executing target #14 $@'
	@echo 'Invoking: Standard S32DS Create Listing'
	powerpc-eabivle-objdump --source --all-headers --demangle --disassemble --line-numbers --wide $(EXECUTABLES) > "bootloader_Z4_0.lst"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_LIST_QUOTED) ./*/*/*.o ./*/*.o  $(SECONDARY_FLASH_QUOTED) $(EXECUTABLES_QUOTED) ./*/*.d  D:\boot\bootloader\bootloader_Z4_0\Debug\bootloader_Z4_0.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

