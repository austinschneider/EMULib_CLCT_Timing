################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TriDAS/emu/fast_daq/daq_common/src/crcdivide.c \
../TriDAS/emu/fast_daq/daq_common/src/daq_ipc.c \
../TriDAS/emu/fast_daq/daq_common/src/get_next_event.c 

OBJS += \
./TriDAS/emu/fast_daq/daq_common/src/crcdivide.o \
./TriDAS/emu/fast_daq/daq_common/src/daq_ipc.o \
./TriDAS/emu/fast_daq/daq_common/src/get_next_event.o 

C_DEPS += \
./TriDAS/emu/fast_daq/daq_common/src/crcdivide.d \
./TriDAS/emu/fast_daq/daq_common/src/daq_ipc.d \
./TriDAS/emu/fast_daq/daq_common/src/get_next_event.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/fast_daq/daq_common/src/%.o: ../TriDAS/emu/fast_daq/daq_common/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


