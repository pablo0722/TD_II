################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include UART/subdir.mk
-include TIMER/subdir.mk
-include TFT/subdir.mk
-include RTOS/subdir.mk
-include FFT/subdir.mk
-include BASICS/subdir.mk
-include ADC_DAC/private/subdir.mk
-include ADC_DAC/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: THD_Meter_RTOS.axf

dependents:
	-cd D:/UTN/Git/TD_II/TD_II/workspace/LibFreeRTOS_8.2.3/Debug && $(MAKE) all
	-cd D:/UTN/Git/TD_II/TD_II/workspace/lpc_chip_175x_6x/Debug && $(MAKE) all
	-cd D:/UTN/Git/TD_II/TD_II/workspace/lpc_myboard_1769/Debug && $(MAKE) all

# Tool invocations
THD_Meter_RTOS.axf: $(OBJS) $(USER_OBJS) D:/UTN/Git/TD_II/TD_II/workspace/LibFreeRTOS_8.2.3/Debug/libLibFreeRTOS_8.2.3.a D:/UTN/Git/TD_II/TD_II/workspace/lpc_chip_175x_6x/Debug/liblpc_chip_175x_6x.a D:/UTN/Git/TD_II/TD_II/workspace/lpc_myboard_1769/Debug/liblpc_myboard_1769.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"D:\UTN\Git\TD_II\TD_II\workspace\lpc_myboard_1769\Debug" -L"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x\Debug" -L"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\Debug" -L"D:\UTN\Git\TD_II\TD_II\workspace\CMSIS_DSPLIB_CM3\lib" -Xlinker -Map="THD_Meter_RTOS.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "THD_Meter_RTOS_Debug.ld" -o "THD_Meter_RTOS.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) THD_Meter_RTOS.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "THD_Meter_RTOS.axf" ; arm-none-eabi-nm -S --size-sort -s "THD_Meter_RTOS.axf" ; # arm-none-eabi-objcopy -v -O binary "THD_Meter_RTOS.axf" "THD_Meter_RTOS.bin" ; # checksum -p LPC1769 -d "THD_Meter_RTOS.bin"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
D:/UTN/Git/TD_II/TD_II/workspace/LibFreeRTOS_8.2.3/Debug/libLibFreeRTOS_8.2.3.a:
D:/UTN/Git/TD_II/TD_II/workspace/lpc_chip_175x_6x/Debug/liblpc_chip_175x_6x.a:
D:/UTN/Git/TD_II/TD_II/workspace/lpc_myboard_1769/Debug/liblpc_myboard_1769.a:

-include ../makefile.targets
