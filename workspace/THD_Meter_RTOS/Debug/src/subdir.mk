################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Inicializaciones.c \
../src/Interrupciones.c \
../src/THD_Meter.c \
../src/Variables_globales.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/funciones.c \
../src/sysinit.c \
../src/tareas.c 

OBJS += \
./src/Inicializaciones.o \
./src/Interrupciones.o \
./src/THD_Meter.o \
./src/Variables_globales.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/funciones.o \
./src/sysinit.o \
./src/tareas.o 

C_DEPS += \
./src/Inicializaciones.d \
./src/Interrupciones.d \
./src/THD_Meter.d \
./src/Variables_globales.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/funciones.d \
./src/sysinit.d \
./src/tareas.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__USE_CMSIS_DSPLIB=CMSIS_DSPLIB_CM3 -D__LPC17XX__ -D__REDLIB__ -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\src\portable\GCC\ARM_CM3" -I"D:\UTN\Git\TD_II\TD_II\workspace\cr_dsplib_cm3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\THD_Meter_RTOS\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_myboard_1769\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\lpc_chip_175x_6x\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\CMSIS_DSPLIB_CM3\inc" -I"D:\UTN\Git\TD_II\TD_II\workspace\LibFreeRTOS_8.2.3\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


