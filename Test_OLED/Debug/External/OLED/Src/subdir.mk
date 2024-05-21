################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../External/OLED/Src/ssd1306.c \
../External/OLED/Src/ssd1306_fonts.c 

OBJS += \
./External/OLED/Src/ssd1306.o \
./External/OLED/Src/ssd1306_fonts.o 

C_DEPS += \
./External/OLED/Src/ssd1306.d \
./External/OLED/Src/ssd1306_fonts.d 


# Each subdirectory must supply rules for building sources it contributes
External/OLED/Src/%.o External/OLED/Src/%.su External/OLED/Src/%.cyclo: ../External/OLED/Src/%.c External/OLED/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I"/home/yocozuna/STM32CubeIDE/workspace_1.15.0/Test_OLED/External/OLED/Inc" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-External-2f-OLED-2f-Src

clean-External-2f-OLED-2f-Src:
	-$(RM) ./External/OLED/Src/ssd1306.cyclo ./External/OLED/Src/ssd1306.d ./External/OLED/Src/ssd1306.o ./External/OLED/Src/ssd1306.su ./External/OLED/Src/ssd1306_fonts.cyclo ./External/OLED/Src/ssd1306_fonts.d ./External/OLED/Src/ssd1306_fonts.o ./External/OLED/Src/ssd1306_fonts.su

.PHONY: clean-External-2f-OLED-2f-Src

