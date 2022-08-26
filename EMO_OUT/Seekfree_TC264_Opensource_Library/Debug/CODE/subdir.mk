################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CODE/All_Config.c \
../CODE/Beep.c \
../CODE/Camera.c \
../CODE/Charge.c \
../CODE/Display.c \
../CODE/Encoder.c \
../CODE/FuzzyPID.c \
../CODE/Grayscale.c \
../CODE/Gyroscope.c \
../CODE/Keystroke.c \
../CODE/LED.c \
../CODE/Motor.c \
../CODE/PID.c \
../CODE/Wireless.c 

OBJS += \
./CODE/All_Config.o \
./CODE/Beep.o \
./CODE/Camera.o \
./CODE/Charge.o \
./CODE/Display.o \
./CODE/Encoder.o \
./CODE/FuzzyPID.o \
./CODE/Grayscale.o \
./CODE/Gyroscope.o \
./CODE/Keystroke.o \
./CODE/LED.o \
./CODE/Motor.o \
./CODE/PID.o \
./CODE/Wireless.o 

COMPILED_SRCS += \
./CODE/All_Config.src \
./CODE/Beep.src \
./CODE/Camera.src \
./CODE/Charge.src \
./CODE/Display.src \
./CODE/Encoder.src \
./CODE/FuzzyPID.src \
./CODE/Grayscale.src \
./CODE/Gyroscope.src \
./CODE/Keystroke.src \
./CODE/LED.src \
./CODE/Motor.src \
./CODE/PID.src \
./CODE/Wireless.src 

C_DEPS += \
./CODE/All_Config.d \
./CODE/Beep.d \
./CODE/Camera.d \
./CODE/Charge.d \
./CODE/Display.d \
./CODE/Encoder.d \
./CODE/FuzzyPID.d \
./CODE/Grayscale.d \
./CODE/Gyroscope.d \
./CODE/Keystroke.d \
./CODE/LED.d \
./CODE/Motor.d \
./CODE/PID.d \
./CODE/Wireless.d 


# Each subdirectory must supply rules for building sources it contributes
CODE/%.src: ../CODE/%.c CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fD:/EMO_OUT/Seekfree_TC264_Opensource_Library/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O2 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

CODE/%.o: ./CODE/%.src CODE/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


