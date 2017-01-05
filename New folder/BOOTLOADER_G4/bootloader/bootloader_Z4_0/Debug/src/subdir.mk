################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../src/intc_sw_handlers.S" \

S_UPPER_SRCS += \
../src/intc_sw_handlers.S \

C_SRCS_QUOTED += \
"../src/MPC57xx__Interrupt_Init.c" \
"../src/Vector.c" \
"../src/flashrchw.c" \
"../src/intc_SW_mode_isr_vectors_MPC5748G.c" \
"../src/linflexd_uart.c" \
"../src/main.c" \
"../src/mode.c" \
"../src/srec.c" \
"../src/tung.c" \

C_SRCS += \
../src/MPC57xx__Interrupt_Init.c \
../src/Vector.c \
../src/flashrchw.c \
../src/intc_SW_mode_isr_vectors_MPC5748G.c \
../src/linflexd_uart.c \
../src/main.c \
../src/mode.c \
../src/srec.c \
../src/tung.c \

OBJS += \
./src/MPC57xx__Interrupt_Init.o \
./src/Vector.o \
./src/flashrchw.o \
./src/intc_SW_mode_isr_vectors_MPC5748G.o \
./src/intc_sw_handlers.o \
./src/linflexd_uart.o \
./src/main.o \
./src/mode.o \
./src/srec.o \
./src/tung.o \

C_DEPS += \
./src/MPC57xx__Interrupt_Init.d \
./src/Vector.d \
./src/flashrchw.d \
./src/intc_SW_mode_isr_vectors_MPC5748G.d \
./src/linflexd_uart.d \
./src/main.d \
./src/mode.d \
./src/srec.d \
./src/tung.d \

OBJS_QUOTED += \
"./src/MPC57xx__Interrupt_Init.o" \
"./src/Vector.o" \
"./src/flashrchw.o" \
"./src/intc_SW_mode_isr_vectors_MPC5748G.o" \
"./src/intc_sw_handlers.o" \
"./src/linflexd_uart.o" \
"./src/main.o" \
"./src/mode.o" \
"./src/srec.o" \
"./src/tung.o" \

C_DEPS_QUOTED += \
"./src/MPC57xx__Interrupt_Init.d" \
"./src/Vector.d" \
"./src/flashrchw.d" \
"./src/intc_SW_mode_isr_vectors_MPC5748G.d" \
"./src/linflexd_uart.d" \
"./src/main.d" \
"./src/mode.d" \
"./src/srec.d" \
"./src/tung.d" \

OBJS_OS_FORMAT += \
./src/MPC57xx__Interrupt_Init.o \
./src/Vector.o \
./src/flashrchw.o \
./src/intc_SW_mode_isr_vectors_MPC5748G.o \
./src/intc_sw_handlers.o \
./src/linflexd_uart.o \
./src/main.o \
./src/mode.o \
./src/srec.o \
./src/tung.o \


# Each subdirectory must supply rules for building sources it contributes
src/MPC57xx__Interrupt_Init.o: ../src/MPC57xx__Interrupt_Init.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/MPC57xx__Interrupt_Init.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/MPC57xx__Interrupt_Init.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/Vector.o: ../src/Vector.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/Vector.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/Vector.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/flashrchw.o: ../src/flashrchw.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/flashrchw.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/flashrchw.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_SW_mode_isr_vectors_MPC5748G.o: ../src/intc_SW_mode_isr_vectors_MPC5748G.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/intc_SW_mode_isr_vectors_MPC5748G.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/intc_SW_mode_isr_vectors_MPC5748G.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/intc_sw_handlers.o: ../src/intc_sw_handlers.S
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	powerpc-eabivle-gcc "@src/intc_sw_handlers.args" -c -o "src/intc_sw_handlers.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/linflexd_uart.o: ../src/linflexd_uart.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/linflexd_uart.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/linflexd_uart.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.o: ../src/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/main.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/mode.o: ../src/mode.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/mode.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/mode.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/srec.o: ../src/srec.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/srec.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/srec.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/tung.o: ../src/tung.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	powerpc-eabivle-gcc "@src/tung.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "src/tung.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


