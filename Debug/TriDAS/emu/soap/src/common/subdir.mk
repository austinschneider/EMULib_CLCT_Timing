################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../TriDAS/emu/soap/src/common/Attachment.cc \
../TriDAS/emu/soap/src/common/Attributes.cc \
../TriDAS/emu/soap/src/common/Messenger.cc \
../TriDAS/emu/soap/src/common/Parameters.cc \
../TriDAS/emu/soap/src/common/QualifiedName.cc \
../TriDAS/emu/soap/src/common/ToolBox.cc \
../TriDAS/emu/soap/src/common/version.cc 

OBJS += \
./TriDAS/emu/soap/src/common/Attachment.o \
./TriDAS/emu/soap/src/common/Attributes.o \
./TriDAS/emu/soap/src/common/Messenger.o \
./TriDAS/emu/soap/src/common/Parameters.o \
./TriDAS/emu/soap/src/common/QualifiedName.o \
./TriDAS/emu/soap/src/common/ToolBox.o \
./TriDAS/emu/soap/src/common/version.o 

CC_DEPS += \
./TriDAS/emu/soap/src/common/Attachment.d \
./TriDAS/emu/soap/src/common/Attributes.d \
./TriDAS/emu/soap/src/common/Messenger.d \
./TriDAS/emu/soap/src/common/Parameters.d \
./TriDAS/emu/soap/src/common/QualifiedName.d \
./TriDAS/emu/soap/src/common/ToolBox.d \
./TriDAS/emu/soap/src/common/version.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/soap/src/common/%.o: ../TriDAS/emu/soap/src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


