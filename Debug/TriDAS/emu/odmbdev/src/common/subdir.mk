################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TriDAS/emu/odmbdev/src/common/eth_hook_2.c \
../TriDAS/emu/odmbdev/src/common/eth_hook_2.mod.c \
../TriDAS/emu/odmbdev/src/common/eth_libmm.c \
../TriDAS/emu/odmbdev/src/common/read_ethbuf.c \
../TriDAS/emu/odmbdev/src/common/reset.c 

CC_SRCS += \
../TriDAS/emu/odmbdev/src/common/Action.cc \
../TriDAS/emu/odmbdev/src/common/ButtonAction.cc \
../TriDAS/emu/odmbdev/src/common/Buttons.cc \
../TriDAS/emu/odmbdev/src/common/FourTextBoxAction.cc \
../TriDAS/emu/odmbdev/src/common/JTAGWrapper.cc \
../TriDAS/emu/odmbdev/src/common/LogAction.cc \
../TriDAS/emu/odmbdev/src/common/MCSTextBoxAction.cc \
../TriDAS/emu/odmbdev/src/common/Manager.cc \
../TriDAS/emu/odmbdev/src/common/OneTextBoxAction.cc \
../TriDAS/emu/odmbdev/src/common/RadioButtonAction.cc \
../TriDAS/emu/odmbdev/src/common/RepeatTextBoxAction.cc \
../TriDAS/emu/odmbdev/src/common/SignatureTextBoxAction.cc \
../TriDAS/emu/odmbdev/src/common/Spy.cc \
../TriDAS/emu/odmbdev/src/common/TextBoxAction.cc \
../TriDAS/emu/odmbdev/src/common/ThreeTextBoxAction.cc \
../TriDAS/emu/odmbdev/src/common/VMEWrapper.cc \
../TriDAS/emu/odmbdev/src/common/eth_lib.cc \
../TriDAS/emu/odmbdev/src/common/tempHWW.cc \
../TriDAS/emu/odmbdev/src/common/utils.cc \
../TriDAS/emu/odmbdev/src/common/version.cc 

OBJS += \
./TriDAS/emu/odmbdev/src/common/Action.o \
./TriDAS/emu/odmbdev/src/common/ButtonAction.o \
./TriDAS/emu/odmbdev/src/common/Buttons.o \
./TriDAS/emu/odmbdev/src/common/FourTextBoxAction.o \
./TriDAS/emu/odmbdev/src/common/JTAGWrapper.o \
./TriDAS/emu/odmbdev/src/common/LogAction.o \
./TriDAS/emu/odmbdev/src/common/MCSTextBoxAction.o \
./TriDAS/emu/odmbdev/src/common/Manager.o \
./TriDAS/emu/odmbdev/src/common/OneTextBoxAction.o \
./TriDAS/emu/odmbdev/src/common/RadioButtonAction.o \
./TriDAS/emu/odmbdev/src/common/RepeatTextBoxAction.o \
./TriDAS/emu/odmbdev/src/common/SignatureTextBoxAction.o \
./TriDAS/emu/odmbdev/src/common/Spy.o \
./TriDAS/emu/odmbdev/src/common/TextBoxAction.o \
./TriDAS/emu/odmbdev/src/common/ThreeTextBoxAction.o \
./TriDAS/emu/odmbdev/src/common/VMEWrapper.o \
./TriDAS/emu/odmbdev/src/common/eth_hook_2.o \
./TriDAS/emu/odmbdev/src/common/eth_hook_2.mod.o \
./TriDAS/emu/odmbdev/src/common/eth_lib.o \
./TriDAS/emu/odmbdev/src/common/eth_libmm.o \
./TriDAS/emu/odmbdev/src/common/read_ethbuf.o \
./TriDAS/emu/odmbdev/src/common/reset.o \
./TriDAS/emu/odmbdev/src/common/tempHWW.o \
./TriDAS/emu/odmbdev/src/common/utils.o \
./TriDAS/emu/odmbdev/src/common/version.o 

C_DEPS += \
./TriDAS/emu/odmbdev/src/common/eth_hook_2.d \
./TriDAS/emu/odmbdev/src/common/eth_hook_2.mod.d \
./TriDAS/emu/odmbdev/src/common/eth_libmm.d \
./TriDAS/emu/odmbdev/src/common/read_ethbuf.d \
./TriDAS/emu/odmbdev/src/common/reset.d 

CC_DEPS += \
./TriDAS/emu/odmbdev/src/common/Action.d \
./TriDAS/emu/odmbdev/src/common/ButtonAction.d \
./TriDAS/emu/odmbdev/src/common/Buttons.d \
./TriDAS/emu/odmbdev/src/common/FourTextBoxAction.d \
./TriDAS/emu/odmbdev/src/common/JTAGWrapper.d \
./TriDAS/emu/odmbdev/src/common/LogAction.d \
./TriDAS/emu/odmbdev/src/common/MCSTextBoxAction.d \
./TriDAS/emu/odmbdev/src/common/Manager.d \
./TriDAS/emu/odmbdev/src/common/OneTextBoxAction.d \
./TriDAS/emu/odmbdev/src/common/RadioButtonAction.d \
./TriDAS/emu/odmbdev/src/common/RepeatTextBoxAction.d \
./TriDAS/emu/odmbdev/src/common/SignatureTextBoxAction.d \
./TriDAS/emu/odmbdev/src/common/Spy.d \
./TriDAS/emu/odmbdev/src/common/TextBoxAction.d \
./TriDAS/emu/odmbdev/src/common/ThreeTextBoxAction.d \
./TriDAS/emu/odmbdev/src/common/VMEWrapper.d \
./TriDAS/emu/odmbdev/src/common/eth_lib.d \
./TriDAS/emu/odmbdev/src/common/tempHWW.d \
./TriDAS/emu/odmbdev/src/common/utils.d \
./TriDAS/emu/odmbdev/src/common/version.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/odmbdev/src/common/%.o: ../TriDAS/emu/odmbdev/src/common/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PeripheralXtop\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\xdaq\include" -I"C:\cygwin\lib\gcc\i686-pc-cygwin\4.8.2\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\PCSwitches\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\OnlineDB\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDUtils\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCrate\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDCore\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\emuDCS\FEDApps\include" -I"C:\Users\Austin\eclipse\workspace\CFEBTiming\TriDAS\emu\base\include" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

TriDAS/emu/odmbdev/src/common/%.o: ../TriDAS/emu/odmbdev/src/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


