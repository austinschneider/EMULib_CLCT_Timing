################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../TriDAS/emu/fast_daq/csc_display/src/J_Display.cc \
../TriDAS/emu/fast_daq/csc_display/src/application.cc \
../TriDAS/emu/fast_daq/csc_display/src/unpack_data.cc 

OBJS += \
./TriDAS/emu/fast_daq/csc_display/src/J_Display.o \
./TriDAS/emu/fast_daq/csc_display/src/application.o \
./TriDAS/emu/fast_daq/csc_display/src/unpack_data.o 

CC_DEPS += \
./TriDAS/emu/fast_daq/csc_display/src/J_Display.d \
./TriDAS/emu/fast_daq/csc_display/src/application.d \
./TriDAS/emu/fast_daq/csc_display/src/unpack_data.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/fast_daq/csc_display/src/%.o: ../TriDAS/emu/fast_daq/csc_display/src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


