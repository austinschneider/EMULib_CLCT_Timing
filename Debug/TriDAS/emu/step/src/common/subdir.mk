################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../TriDAS/emu/step/src/common/Application.cc \
../TriDAS/emu/step/src/common/ChamberMap.cc \
../TriDAS/emu/step/src/common/Configuration.cc \
../TriDAS/emu/step/src/common/Manager.cc \
../TriDAS/emu/step/src/common/Test.cc \
../TriDAS/emu/step/src/common/TestParameters.cc \
../TriDAS/emu/step/src/common/Tester.cc \
../TriDAS/emu/step/src/common/version.cc 

OBJS += \
./TriDAS/emu/step/src/common/Application.o \
./TriDAS/emu/step/src/common/ChamberMap.o \
./TriDAS/emu/step/src/common/Configuration.o \
./TriDAS/emu/step/src/common/Manager.o \
./TriDAS/emu/step/src/common/Test.o \
./TriDAS/emu/step/src/common/TestParameters.o \
./TriDAS/emu/step/src/common/Tester.o \
./TriDAS/emu/step/src/common/version.o 

CC_DEPS += \
./TriDAS/emu/step/src/common/Application.d \
./TriDAS/emu/step/src/common/ChamberMap.d \
./TriDAS/emu/step/src/common/Configuration.d \
./TriDAS/emu/step/src/common/Manager.d \
./TriDAS/emu/step/src/common/Test.d \
./TriDAS/emu/step/src/common/TestParameters.d \
./TriDAS/emu/step/src/common/Tester.d \
./TriDAS/emu/step/src/common/version.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/step/src/common/%.o: ../TriDAS/emu/step/src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


