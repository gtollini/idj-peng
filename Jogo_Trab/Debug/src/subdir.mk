################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Component.cpp \
../src/Face.cpp \
../src/Game.cpp \
../src/GameObject.cpp \
../src/Music.cpp \
../src/Rect.cpp \
../src/Sound.cpp \
../src/Sprite.cpp \
../src/State.cpp \
../src/Vec2.cpp \
../src/main.cpp 

OBJS += \
./src/Component.o \
./src/Face.o \
./src/Game.o \
./src/GameObject.o \
./src/Music.o \
./src/Rect.o \
./src/Sound.o \
./src/Sprite.o \
./src/State.o \
./src/Vec2.o \
./src/main.o 

CPP_DEPS += \
./src/Component.d \
./src/Face.d \
./src/Game.d \
./src/GameObject.d \
./src/Music.d \
./src/Rect.d \
./src/Sound.d \
./src/Sprite.d \
./src/State.d \
./src/Vec2.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/SDL2 -I"/media/gabriel/RAID/Trabalhos/IDJ/Jogo_Trab/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


