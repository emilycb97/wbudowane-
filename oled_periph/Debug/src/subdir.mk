################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/JoystickHandler.c \
../src/cr_startup_lpc17.c \
../src/main.c \
../src/myRtc.c 

C_DEPS += \
./src/JoystickHandler.d \
./src/cr_startup_lpc17.d \
./src/main.d \
./src/myRtc.d 

OBJS += \
./src/JoystickHandler.o \
./src/cr_startup_lpc17.o \
./src/main.o \
./src/myRtc.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_EaBaseBoard\inc" -I"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_MCU\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/JoystickHandler.d ./src/JoystickHandler.o ./src/cr_startup_lpc17.d ./src/cr_startup_lpc17.o ./src/main.d ./src/main.o ./src/myRtc.d ./src/myRtc.o

.PHONY: clean-src

