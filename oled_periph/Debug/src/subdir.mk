################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc17.c \
../src/ledStrips.c \
../src/main.c \
../src/myRtc.c \
../src/screenManagment.c 

C_DEPS += \
./src/cr_startup_lpc17.d \
./src/ledStrips.d \
./src/main.d \
./src/myRtc.d \
./src/screenManagment.d 

OBJS += \
./src/cr_startup_lpc17.o \
./src/ledStrips.o \
./src/main.o \
./src/myRtc.o \
./src/screenManagment.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_CMSISv1p30_LPC17xx\inc" -I"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_EaBaseBoard\inc" -I"C:\Users\student\Desktop\basic\lpc17xx_xpr_bb_140609(1)\Lib_MCU\inc" -O0 -g3 -gdwarf-4 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/cr_startup_lpc17.d ./src/cr_startup_lpc17.o ./src/ledStrips.d ./src/ledStrips.o ./src/main.d ./src/main.o ./src/myRtc.d ./src/myRtc.o ./src/screenManagment.d ./src/screenManagment.o

.PHONY: clean-src

