################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/subdir.mk
-include HAL/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
test_machine_state.lss \

FLASH_IMAGE += \
test_machine_state.hex \

EEPROM_IMAGE += \
test_machine_state.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: test_machine_state.elf secondary-outputs

# Tool invocations
test_machine_state.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,test_machine_state.map -mmcu=atmega32 -o "test_machine_state.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

test_machine_state.lss: test_machine_state.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S test_machine_state.elf  >"test_machine_state.lss"
	@echo 'Finished building: $@'
	@echo ' '

test_machine_state.hex: test_machine_state.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex test_machine_state.elf  "test_machine_state.hex"
	@echo 'Finished building: $@'
	@echo ' '

test_machine_state.eep: test_machine_state.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex test_machine_state.elf  "test_machine_state.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: test_machine_state.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 test_machine_state.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) test_machine_state.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
