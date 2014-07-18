################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xdaq/include/xercesc/framework/psvi/XSNamedMap.c 

OBJS += \
./xdaq/include/xercesc/framework/psvi/XSNamedMap.o 

C_DEPS += \
./xdaq/include/xercesc/framework/psvi/XSNamedMap.d 


# Each subdirectory must supply rules for building sources it contributes
xdaq/include/xercesc/framework/psvi/%.o: ../xdaq/include/xercesc/framework/psvi/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


