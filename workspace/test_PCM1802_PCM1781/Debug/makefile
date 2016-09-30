################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: test_PCM1802_PCM1781.axf

# Tool invocations
test_PCM1802_PCM1781.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/aortiz/UTN/TD II/TEST_DMA_I2S/lpc_board_nxp_lpcxpresso_1769/Debug" -L"/home/aortiz/UTN/TD II/TEST_DMA_I2S/lpc_chip_175x_6x/Debug" -Xlinker -Map="test_PCM1802_PCM1781.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "test_PCM1802_PCM1781_Debug.ld" -o "test_PCM1802_PCM1781.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) test_PCM1802_PCM1781.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "test_PCM1802_PCM1781.axf"; # arm-none-eabi-objcopy -v -O binary "test_PCM1802_PCM1781.axf" "test_PCM1802_PCM1781.bin" ; # checksum -p LPC1769 -d "test_PCM1802_PCM1781.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
