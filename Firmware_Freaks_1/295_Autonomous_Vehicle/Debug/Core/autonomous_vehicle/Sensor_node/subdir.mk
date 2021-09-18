################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/autonomous_vehicle/Sensor_node/sensor__config.c \
../Core/autonomous_vehicle/Sensor_node/sensor__val_conv.c 

OBJS += \
./Core/autonomous_vehicle/Sensor_node/sensor__config.o \
./Core/autonomous_vehicle/Sensor_node/sensor__val_conv.o 

C_DEPS += \
./Core/autonomous_vehicle/Sensor_node/sensor__config.d \
./Core/autonomous_vehicle/Sensor_node/sensor__val_conv.d 


# Each subdirectory must supply rules for building sources it contributes
Core/autonomous_vehicle/Sensor_node/%.o: ../Core/autonomous_vehicle/Sensor_node/%.c Core/autonomous_vehicle/Sensor_node/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../USB_HOST/App -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Include -I../Core/Inc -I../USB_HOST/Target -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

