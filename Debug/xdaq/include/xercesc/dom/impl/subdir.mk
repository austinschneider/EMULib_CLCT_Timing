################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xdaq/include/xercesc/dom/impl/DOMDeepNodeListPool.c 

OBJS += \
./xdaq/include/xercesc/dom/impl/DOMDeepNodeListPool.o 

C_DEPS += \
./xdaq/include/xercesc/dom/impl/DOMDeepNodeListPool.d 


# Each subdirectory must supply rules for building sources it contributes
xdaq/include/xercesc/dom/impl/%.o: ../xdaq/include/xercesc/dom/impl/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


