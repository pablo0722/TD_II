################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FreeRTOSCommonHooks.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/heap_3.c \
../src/list.c \
../src/port.c \
../src/queue.c \
../src/sysinit.c \
../src/tasks.c \
../src/test_PCM1802_PCM1781.c 

OBJS += \
./src/FreeRTOSCommonHooks.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/heap_3.o \
./src/list.o \
./src/port.o \
./src/queue.o \
./src/sysinit.o \
./src/tasks.o \
./src/test_PCM1802_PCM1781.o 

C_DEPS += \
./src/FreeRTOSCommonHooks.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/heap_3.d \
./src/list.d \
./src/port.d \
./src/queue.d \
./src/sysinit.d \
./src/tasks.d \
./src/test_PCM1802_PCM1781.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__REDLIB__ -I"/home/aortiz/UTN/TD II/TEST_DMA_I2S/test_PCM1802_PCM1781/inc" -I"/home/aortiz/UTN/TD II/TEST_DMA_I2S/test_PCM1802_PCM1781/src" -I"/home/aortiz/UTN/TD II/TEST_DMA_I2S/lpc_board_nxp_lpcxpresso_1769/inc" -I"/home/aortiz/UTN/TD II/TEST_DMA_I2S/lpc_chip_175x_6x/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


