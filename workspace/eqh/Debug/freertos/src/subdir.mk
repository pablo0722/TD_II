################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freertos/src/FreeRTOSCommonHooks.c \
../freertos/src/heap_3.c \
../freertos/src/list.c \
../freertos/src/port.c \
../freertos/src/queue.c \
../freertos/src/tasks.c 

OBJS += \
./freertos/src/FreeRTOSCommonHooks.o \
./freertos/src/heap_3.o \
./freertos/src/list.o \
./freertos/src/port.o \
./freertos/src/queue.o \
./freertos/src/tasks.o 

C_DEPS += \
./freertos/src/FreeRTOSCommonHooks.d \
./freertos/src/heap_3.d \
./freertos/src/list.d \
./freertos/src/port.d \
./freertos/src/queue.d \
./freertos/src/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
freertos/src/%.o: ../freertos/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__NEWLIB__ -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\FFT" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\CMSIS_DSPLIB_CM3\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\CMSIS_DSPLIB_CM3\inc\arm" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\efectos" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\display" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\my_freertos" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\gpio" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\adc_dac" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\freertos\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\freertos\src" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\lpc_board_nxp_lpcxpresso_1769\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


