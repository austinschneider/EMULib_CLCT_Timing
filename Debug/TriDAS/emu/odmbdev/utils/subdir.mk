################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TriDAS/emu/odmbdev/utils/add_ddu_hdr.cpp \
../TriDAS/emu/odmbdev/utils/data_packet.cpp \
../TriDAS/emu/odmbdev/utils/parseddu.cpp 

OBJS += \
./TriDAS/emu/odmbdev/utils/add_ddu_hdr.o \
./TriDAS/emu/odmbdev/utils/data_packet.o \
./TriDAS/emu/odmbdev/utils/parseddu.o 

CPP_DEPS += \
./TriDAS/emu/odmbdev/utils/add_ddu_hdr.d \
./TriDAS/emu/odmbdev/utils/data_packet.d \
./TriDAS/emu/odmbdev/utils/parseddu.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/odmbdev/utils/%.o: ../TriDAS/emu/odmbdev/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


