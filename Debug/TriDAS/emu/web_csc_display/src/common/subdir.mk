################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../TriDAS/emu/web_csc_display/src/common/JSON.cc \
../TriDAS/emu/web_csc_display/src/common/SimpleWeb.cc \
../TriDAS/emu/web_csc_display/src/common/graph.cc \
../TriDAS/emu/web_csc_display/src/common/unpacker.cc \
../TriDAS/emu/web_csc_display/src/common/utils.cc \
../TriDAS/emu/web_csc_display/src/common/version.cc 

OBJS += \
./TriDAS/emu/web_csc_display/src/common/JSON.o \
./TriDAS/emu/web_csc_display/src/common/SimpleWeb.o \
./TriDAS/emu/web_csc_display/src/common/graph.o \
./TriDAS/emu/web_csc_display/src/common/unpacker.o \
./TriDAS/emu/web_csc_display/src/common/utils.o \
./TriDAS/emu/web_csc_display/src/common/version.o 

CC_DEPS += \
./TriDAS/emu/web_csc_display/src/common/JSON.d \
./TriDAS/emu/web_csc_display/src/common/SimpleWeb.d \
./TriDAS/emu/web_csc_display/src/common/graph.d \
./TriDAS/emu/web_csc_display/src/common/unpacker.d \
./TriDAS/emu/web_csc_display/src/common/utils.d \
./TriDAS/emu/web_csc_display/src/common/version.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/web_csc_display/src/common/%.o: ../TriDAS/emu/web_csc_display/src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


