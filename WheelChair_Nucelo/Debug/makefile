################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
WheelChair_Nucelo.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
WheelChair_Nucelo.list \

OBJCOPY_BIN += \
WheelChair_Nucelo.bin \


# All Target
all: WheelChair_Nucelo.elf secondary-outputs

# Tool invocations
WheelChair_Nucelo.elf: $(OBJS) $(USER_OBJS) C:\Users\Hari\Desktop\295A\Github\295_Firmware_Freaks\WheelChair_Nucelo\STM32F446RETX_FLASH.ld
	arm-none-eabi-gcc -o "WheelChair_Nucelo.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\Hari\Desktop\295A\Github\295_Firmware_Freaks\WheelChair_Nucelo\STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="WheelChair_Nucelo.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

WheelChair_Nucelo.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "WheelChair_Nucelo.list"
	@echo 'Finished building: $@'
	@echo ' '

WheelChair_Nucelo.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "WheelChair_Nucelo.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
