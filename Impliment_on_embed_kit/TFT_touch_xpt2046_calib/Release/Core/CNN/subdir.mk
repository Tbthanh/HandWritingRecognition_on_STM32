################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/CNN/cnn.c 

OBJS += \
./Core/CNN/cnn.o 

C_DEPS += \
./Core/CNN/cnn.d 


# Each subdirectory must supply rules for building sources it contributes
Core/CNN/%.o Core/CNN/%.su Core/CNN/%.cyclo: ../Core/CNN/%.c Core/CNN/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I"D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/CNN" -I"D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/ST7789" -I"D:/TAI_LIEU/20241/AI_and_App/HandWritingRecognition_on_STM32/Impliment_on_embed_kit/TFT_touch_xpt2046_calib/Core/XPT2046" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-CNN

clean-Core-2f-CNN:
	-$(RM) ./Core/CNN/cnn.cyclo ./Core/CNN/cnn.d ./Core/CNN/cnn.o ./Core/CNN/cnn.su

.PHONY: clean-Core-2f-CNN

