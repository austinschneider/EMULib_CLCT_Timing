################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../TriDAS/emu/emuDCS/drivers/gbit-vme/eth_hook_jtag_simple/eth_hook.c 

OBJS += \
./TriDAS/emu/emuDCS/drivers/gbit-vme/eth_hook_jtag_simple/eth_hook.o 

C_DEPS += \
./TriDAS/emu/emuDCS/drivers/gbit-vme/eth_hook_jtag_simple/eth_hook.d 


# Each subdirectory must supply rules for building sources it contributes
TriDAS/emu/emuDCS/drivers/gbit-vme/eth_hook_jtag_simple/%.o: ../TriDAS/emu/emuDCS/drivers/gbit-vme/eth_hook_jtag_simple/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


