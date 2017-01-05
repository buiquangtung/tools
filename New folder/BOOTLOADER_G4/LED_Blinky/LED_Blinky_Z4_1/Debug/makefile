################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 6
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
LED_Blinky_Z4_1.elf \

EXECUTABLES_QUOTED += \
"LED_Blinky_Z4_1.elf" \

EXECUTABLES_OS_FORMAT += \
LED_Blinky_Z4_1.elf \


# All Target
all: warning-messages explicit-dependencies LED_Blinky_Z4_1.elf secondary-outputs

# Tool invocations
LED_Blinky_Z4_1.elf: $(OBJS) D:/1boot/App/LED_Blinky_Z4_1/Project_Settings/Linker_Files/57xx_flash.ld D:/1boot/App/LED_Blinky_Z4_1/Project_Settings/Linker_Files/libs.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #7 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	powerpc-eabivle-gcc -o "LED_Blinky_Z4_1.elf" "@LED_Blinky_Z4_1.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*/*.o ./*/*.o  $(EXECUTABLES_QUOTED) ./*/*.d  D:\1boot\App\LED_Blinky_Z4_1\Debug\LED_Blinky_Z4_1.elf
	-@echo ' '

secondary-outputs:

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

