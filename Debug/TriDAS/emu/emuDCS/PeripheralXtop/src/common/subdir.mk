################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../TriDAS/emu/emuDCS/PeripheralXtop/src/common/Chamber.cc \
../TriDAS/emu/emuDCS/PeripheralXtop/src/common/DDU.cc \
../TriDAS/emu/emuDCS/PeripheralXtop/src/common/EmuDim.cc \
../TriDAS/emu/emuDCS/PeripheralXtop/src/common/LOAD.cc \
../TriDAS/emu/emuDCS/PeripheralXtop/src/common/XtopVersion.cc 

OBJS += \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/Chamber.o \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/DDU.o \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/EmuDim.o \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/LOAD.o \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/XtopVersion.o 

CC_DEPS += \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/Chamber.d \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/DDU.d \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/EmuDim.d \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/LOAD.d \
./TriDAS/emu/emuDCS/PeripheralXtop/src/common/XtopVersion.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/emuDCS/PeripheralXtop/src/common/%.o: ../TriDAS/emu/emuDCS/PeripheralXtop/src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


