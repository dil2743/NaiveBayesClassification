################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/DSP/Source/arm_max_f32.c 

OBJS += \
./Drivers/DSP/Source/arm_max_f32.o 

C_DEPS += \
./Drivers/DSP/Source/arm_max_f32.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/DSP/Source/arm_max_f32.o: ../Drivers/DSP/Source/arm_max_f32.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32G0B1xx -DUSE_HAL_DRIVER -DDEBUG -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core_A/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/DSP/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/DSP/Source/arm_max_f32.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

