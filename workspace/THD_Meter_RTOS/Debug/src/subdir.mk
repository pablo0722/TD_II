################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Inicializaciones.c \
../src/THD_Meter.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/funciones.c \
../src/sysinit.c 

OBJS += \
./src/Inicializaciones.o \
./src/THD_Meter.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/funciones.o \
./src/sysinit.o 

C_DEPS += \
./src/Inicializaciones.d \
./src/THD_Meter.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/funciones.d \
./src/sysinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__REDLIB__ -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_myboard_1769\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\CMSIS_DSPLIB_CM3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\UART" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\FFT" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\ADC_DAC" -Os -g3 -Wall -c --save-temps -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


