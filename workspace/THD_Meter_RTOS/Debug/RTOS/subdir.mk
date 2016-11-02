################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../RTOS/rtos_globales.c \
../RTOS/rtos_init.c \
../RTOS/rtos_tareas.c 

OBJS += \
./RTOS/rtos_globales.o \
./RTOS/rtos_init.o \
./RTOS/rtos_tareas.o 

C_DEPS += \
./RTOS/rtos_globales.d \
./RTOS/rtos_init.d \
./RTOS/rtos_tareas.d 


# Each subdirectory must supply rules for building sources it contributes
RTOS/%.o: ../RTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__REDLIB__ -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_myboard_1769\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\CMSIS_DSPLIB_CM3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\UART" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\FFT" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\ADC_DAC" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\RTOS" -O0 -g3 -Wall -c --save-temps -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


