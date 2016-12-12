################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../display/display_func.c \
../display/display_globales.c \
../display/display_int.c \
../display/fonts.c 

OBJS += \
./display/display_func.o \
./display/display_globales.o \
./display/display_int.o \
./display/fonts.o 

C_DEPS += \
./display/display_func.d \
./display/display_globales.d \
./display/display_int.d \
./display/fonts.d 


# Each subdirectory must supply rules for building sources it contributes
display/%.o: ../display/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_LPCOPEN -D__LPC17XX__ -D__NEWLIB__ -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\FFT" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\CMSIS_DSPLIB_CM3\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\CMSIS_DSPLIB_CM3\inc\arm" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\efectos" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\display" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\my_freertos" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\gpio" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\adc_dac" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\freertos\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\eqh\freertos\src" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\lpc_board_nxp_lpcxpresso_1769\inc" -I"D:\UTN\Git\TD_II\TD_II (ADA antiguo)\eqh\fw\lpc_chip_175x_6x\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


