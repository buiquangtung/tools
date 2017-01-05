################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 8
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
LED_Blinky_Z4_0.elf \

EXECUTABLES_QUOTED += \
"LED_Blinky_Z4_0.elf" \

EXECUTABLES_OS_FORMAT += \
LED_Blinky_Z4_0.elf \

SECONDARY_FLASH += \
LED_Blinky_Z4_0.srec \

SECONDARY_FLASH_QUOTED += \
"LED_Blinky_Z4_0.srec" \

SECONDARY_FLASH_OS_FORMAT += \
LED_Blinky_Z4_0.srec \


# All Target
all: warning-messages explicit-dependencies LED_Blinky_Z4_0.elf secondary-outputs

dependents:
	-cd "D:\1boot\App\LED_Blinky_Z2\Debug" && $(MAKE) all
	-cd "D:\1boot\App\LED_Blinky_Z4_1\Debug" && $(MAKE) all

# Tool invocations
LED_Blinky_Z4_0.elf: $(OBJS) D:/1boot/App/LED_Blinky_Z4_0/Project_Settings/Linker_Files/57xx_flash.ld D:/1boot/App/LED_Blinky_Z4_0/Project_Settings/Linker_Files/libs.ld $(USER_OBJS) D:/1boot/App/LED_Blinky_Z2/Debug/LED_Blinky_Z2.elf D:/1boot/App/LED_Blinky_Z4_1/Debug/LED_Blinky_Z4_1.elf
	@echo 'Building target: $@'
	@echo 'Executing target #9 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "LED_Blinky_Z4_0.elf" "@LED_Blinky_Z4_0.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

LED_Blinky_Z4_0.srec: $(EXECUTABLES)
	@echo 'Executing target #10 $@'
	@echo 'Invoking: Standard S32DS Create Flash Image'
	powerpc-eabivle-objcopy -O srec $(EXECUTABLES)  "LED_Blinky_Z4_0.srec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*/*.o ./*/*.o  $(SECONDARY_FLASH_QUOTED) $(EXECUTABLES_QUOTED) ./*/*.d  D:\1boot\App\LED_Blinky_Z4_0\Debug\LED_Blinky_Z4_0.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:
D:/1boot/App/LED_Blinky_Z2/Debug/LED_Blinky_Z2.elf:
D:/1boot/App/LED_Blinky_Z4_1/Debug/LED_Blinky_Z4_1.elf:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

