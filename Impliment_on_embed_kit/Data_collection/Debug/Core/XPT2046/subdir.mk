################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/XPT2046/xpt2046.c 

OBJS += \
./Core/XPT2046/xpt2046.o 

C_DEPS += \
./Core/XPT2046/xpt2046.d 


# Each subdirectory must supply rules for building sources it contributes
Core/XPT2046/xpt2046.o: D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/XPT2046/xpt2046.c Core/XPT2046/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/ST7789" -I"D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/XPT2046" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/CNN" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-XPT2046

clean-Core-2f-XPT2046:
	-$(RM) ./Core/XPT2046/xpt2046.cyclo ./Core/XPT2046/xpt2046.d ./Core/XPT2046/xpt2046.o ./Core/XPT2046/xpt2046.su

.PHONY: clean-Core-2f-XPT2046

