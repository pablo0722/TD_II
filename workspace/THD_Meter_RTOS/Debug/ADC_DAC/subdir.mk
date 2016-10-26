################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_DAC/adc_dac_globales.c \
../ADC_DAC/adc_dac_irq.c \
../ADC_DAC/adc_dac_main.c \
../ADC_DAC/adc_dac_main_aux.c 

OBJS += \
./ADC_DAC/adc_dac_globales.o \
./ADC_DAC/adc_dac_irq.o \
./ADC_DAC/adc_dac_main.o \
./ADC_DAC/adc_dac_main_aux.o 

C_DEPS += \
./ADC_DAC/adc_dac_globales.d \
./ADC_DAC/adc_dac_irq.d \
./ADC_DAC/adc_dac_main.d \
./ADC_DAC/adc_dac_main_aux.d 


# Each subdirectory must supply rules for building sources it contributes
ADC_DAC/%.o: ../ADC_DAC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__REDLIB__ -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_board_nxp_lpcxpresso_1769" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_myboard_1769\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\CMSIS_DSPLIB_CM3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\UART" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\FFT" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\ADC_DAC" -O0 -g3 -Wall -c --save-temps -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


