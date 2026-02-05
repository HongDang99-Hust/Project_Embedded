################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver_Layer/DHT22/DHT.c 

OBJS += \
./Driver_Layer/DHT22/DHT.o 

C_DEPS += \
./Driver_Layer/DHT22/DHT.d 


# Each subdirectory must supply rules for building sources it contributes
Driver_Layer/DHT22/%.o Driver_Layer/DHT22/%.su Driver_Layer/DHT22/%.cyclo: ../Driver_Layer/DHT22/%.c Driver_Layer/DHT22/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/DELL/STM32CubeIDE/workspace_1.16.1/single_task1/01_Simple_Period_Done/Driver_Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver_Layer-2f-DHT22

clean-Driver_Layer-2f-DHT22:
	-$(RM) ./Driver_Layer/DHT22/DHT.cyclo ./Driver_Layer/DHT22/DHT.d ./Driver_Layer/DHT22/DHT.o ./Driver_Layer/DHT22/DHT.su

.PHONY: clean-Driver_Layer-2f-DHT22

