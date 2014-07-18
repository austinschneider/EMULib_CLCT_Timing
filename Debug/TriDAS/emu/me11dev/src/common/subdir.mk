################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../TriDAS/emu/me11dev/src/common/Action.cc \
../TriDAS/emu/me11dev/src/common/Buttons.cc \
../TriDAS/emu/me11dev/src/common/LogAction.cc \
../TriDAS/emu/me11dev/src/common/Manager.cc \
../TriDAS/emu/me11dev/src/common/utils.cc \
../TriDAS/emu/me11dev/src/common/version.cc 

OBJS += \
./TriDAS/emu/me11dev/src/common/Action.o \
./TriDAS/emu/me11dev/src/common/Buttons.o \
./TriDAS/emu/me11dev/src/common/LogAction.o \
./TriDAS/emu/me11dev/src/common/Manager.o \
./TriDAS/emu/me11dev/src/common/utils.o \
./TriDAS/emu/me11dev/src/common/version.o 

CC_DEPS += \
./TriDAS/emu/me11dev/src/common/Action.d \
./TriDAS/emu/me11dev/src/common/Buttons.d \
./TriDAS/emu/me11dev/src/common/LogAction.d \
./TriDAS/emu/me11dev/src/common/Manager.d \
./TriDAS/emu/me11dev/src/common/utils.d \
./TriDAS/emu/me11dev/src/common/version.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/me11dev/src/common/%.o: ../TriDAS/emu/me11dev/src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


