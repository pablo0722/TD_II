################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TFT/tft_Init.c \
../TFT/tft_fonts.c \
../TFT/tft_globales.c \
../TFT/tft_lcd_primitivas.c \
../TFT/tft_private_func.c \
../TFT/tft_signalTFT.c \
../TFT/tft_tareas.c 

OBJS += \
./TFT/tft_Init.o \
./TFT/tft_fonts.o \
./TFT/tft_globales.o \
./TFT/tft_lcd_primitivas.o \
./TFT/tft_private_func.o \
./TFT/tft_signalTFT.o \
./TFT/tft_tareas.o 

C_DEPS += \
./TFT/tft_Init.d \
./TFT/tft_fonts.d \
./TFT/tft_globales.d \
./TFT/tft_lcd_primitivas.d \
./TFT/tft_private_func.d \
./TFT/tft_signalTFT.d \
./TFT/tft_tareas.d 


# Each subdirectory must supply rules for building sources it contributes
TFT/%.o: ../TFT/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__REDLIB__ -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_myboard_1769\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\CMSIS_DSPLIB_CM3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\UART" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\FFT" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\ADC_DAC" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\TIMER" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\TFT" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\RTOS" -O0 -g3 -Wall -c --save-temps -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

