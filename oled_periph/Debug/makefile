################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := oled_periph
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all:
	+@$(MAKE) --no-print-directory main-build && $(MAKE) --no-print-directory post-build

# Main-build Target
main-build: oled_periph.axf

# Tool invocations
oled_periph.axf: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_CMSISv1p30_LPC17xx\Debug" -L"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_EaBaseBoard\Debug" -L"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_MCU\Debug" -Xlinker --gc-sections -Xlinker -Map=oled_periph.map -mcpu=cortex-m3 -mthumb -T oled_periph_Debug.ld -o "oled_periph.axf" $(OBJS) $(USER_OBJS) $(LIBS) -lCMSISv1p30_LPC17xx -lLib_EaBaseBoard -lLib_MCU
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) oled_periph.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size oled_periph.axf; # arm-none-eabi-objdump -h -S oled_periph.axf >oled_periph.lss
	-@echo ' '

.PHONY: all clean dependents main-build post-build

-include ../makefile.targets
