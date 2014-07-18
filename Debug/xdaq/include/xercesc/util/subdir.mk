################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xdaq/include/xercesc/util/BaseRefVectorOf.c \
../xdaq/include/xercesc/util/CountedPointer.c \
../xdaq/include/xercesc/util/FlagJanitor.c \
../xdaq/include/xercesc/util/Janitor.c \
../xdaq/include/xercesc/util/KeyRefPair.c \
../xdaq/include/xercesc/util/KeyValuePair.c \
../xdaq/include/xercesc/util/LogicalPath.c \
../xdaq/include/xercesc/util/NameIdPool.c \
../xdaq/include/xercesc/util/RefArrayOf.c \
../xdaq/include/xercesc/util/RefArrayVectorOf.c \
../xdaq/include/xercesc/util/RefHash2KeysTableOf.c \
../xdaq/include/xercesc/util/RefHash3KeysIdPool.c \
../xdaq/include/xercesc/util/RefHashTableOf.c \
../xdaq/include/xercesc/util/RefStackOf.c \
../xdaq/include/xercesc/util/RefVectorOf.c \
../xdaq/include/xercesc/util/TransENameMap.c \
../xdaq/include/xercesc/util/ValueArrayOf.c \
../xdaq/include/xercesc/util/ValueHashTableOf.c \
../xdaq/include/xercesc/util/ValueStackOf.c \
../xdaq/include/xercesc/util/ValueVectorOf.c \
../xdaq/include/xercesc/util/XMLDeleterFor.c \
../xdaq/include/xercesc/util/XMLHolder.c 

OBJS += \
./xdaq/include/xercesc/util/BaseRefVectorOf.o \
./xdaq/include/xercesc/util/CountedPointer.o \
./xdaq/include/xercesc/util/FlagJanitor.o \
./xdaq/include/xercesc/util/Janitor.o \
./xdaq/include/xercesc/util/KeyRefPair.o \
./xdaq/include/xercesc/util/KeyValuePair.o \
./xdaq/include/xercesc/util/LogicalPath.o \
./xdaq/include/xercesc/util/NameIdPool.o \
./xdaq/include/xercesc/util/RefArrayOf.o \
./xdaq/include/xercesc/util/RefArrayVectorOf.o \
./xdaq/include/xercesc/util/RefHash2KeysTableOf.o \
./xdaq/include/xercesc/util/RefHash3KeysIdPool.o \
./xdaq/include/xercesc/util/RefHashTableOf.o \
./xdaq/include/xercesc/util/RefStackOf.o \
./xdaq/include/xercesc/util/RefVectorOf.o \
./xdaq/include/xercesc/util/TransENameMap.o \
./xdaq/include/xercesc/util/ValueArrayOf.o \
./xdaq/include/xercesc/util/ValueHashTableOf.o \
./xdaq/include/xercesc/util/ValueStackOf.o \
./xdaq/include/xercesc/util/ValueVectorOf.o \
./xdaq/include/xercesc/util/XMLDeleterFor.o \
./xdaq/include/xercesc/util/XMLHolder.o 

C_DEPS += \
./xdaq/include/xercesc/util/BaseRefVectorOf.d \
./xdaq/include/xercesc/util/CountedPointer.d \
./xdaq/include/xercesc/util/FlagJanitor.d \
./xdaq/include/xercesc/util/Janitor.d \
./xdaq/include/xercesc/util/KeyRefPair.d \
./xdaq/include/xercesc/util/KeyValuePair.d \
./xdaq/include/xercesc/util/LogicalPath.d \
./xdaq/include/xercesc/util/NameIdPool.d \
./xdaq/include/xercesc/util/RefArrayOf.d \
./xdaq/include/xercesc/util/RefArrayVectorOf.d \
./xdaq/include/xercesc/util/RefHash2KeysTableOf.d \
./xdaq/include/xercesc/util/RefHash3KeysIdPool.d \
./xdaq/include/xercesc/util/RefHashTableOf.d \
./xdaq/include/xercesc/util/RefStackOf.d \
./xdaq/include/xercesc/util/RefVectorOf.d \
./xdaq/include/xercesc/util/TransENameMap.d \
./xdaq/include/xercesc/util/ValueArrayOf.d \
./xdaq/include/xercesc/util/ValueHashTableOf.d \
./xdaq/include/xercesc/util/ValueStackOf.d \
./xdaq/include/xercesc/util/ValueVectorOf.d \
./xdaq/include/xercesc/util/XMLDeleterFor.d \
./xdaq/include/xercesc/util/XMLHolder.d 


# Each subdirectory must supply rules for building sources it contributes
xdaq/include/xercesc/util/%.o: ../xdaq/include/xercesc/util/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


