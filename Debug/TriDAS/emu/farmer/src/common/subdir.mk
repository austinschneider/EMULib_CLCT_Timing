################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../TriDAS/emu/farmer/src/common/Application.cc \
../TriDAS/emu/farmer/src/common/Cgi.cc \
../TriDAS/emu/farmer/src/common/FileSystem.cc \
../TriDAS/emu/farmer/src/common/ProcessDescriptor.cc \
../TriDAS/emu/farmer/src/common/SOAP.cc \
../TriDAS/emu/farmer/src/common/Xalan.cc \
../TriDAS/emu/farmer/src/common/version.cc 

OBJS += \
./TriDAS/emu/farmer/src/common/Application.o \
./TriDAS/emu/farmer/src/common/Cgi.o \
./TriDAS/emu/farmer/src/common/FileSystem.o \
./TriDAS/emu/farmer/src/common/ProcessDescriptor.o \
./TriDAS/emu/farmer/src/common/SOAP.o \
./TriDAS/emu/farmer/src/common/Xalan.o \
./TriDAS/emu/farmer/src/common/version.o 

CC_DEPS += \
./TriDAS/emu/farmer/src/common/Application.d \
./TriDAS/emu/farmer/src/common/Cgi.d \
./TriDAS/emu/farmer/src/common/FileSystem.d \
./TriDAS/emu/farmer/src/common/ProcessDescriptor.d \
./TriDAS/emu/farmer/src/common/SOAP.d \
./TriDAS/emu/farmer/src/common/Xalan.d \
./TriDAS/emu/farmer/src/common/version.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/farmer/src/common/%.o: ../TriDAS/emu/farmer/src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


