################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/ADC.c \
../MCAL/UART.c \
../MCAL/i2c.c \
../MCAL/spechial_timer.c \
../MCAL/timer.c 

OBJS += \
./MCAL/ADC.o \
./MCAL/UART.o \
./MCAL/i2c.o \
./MCAL/spechial_timer.o \
./MCAL/timer.o 

C_DEPS += \
./MCAL/ADC.d \
./MCAL/UART.d \
./MCAL/i2c.d \
./MCAL/spechial_timer.d \
./MCAL/timer.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/%.o: ../MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


