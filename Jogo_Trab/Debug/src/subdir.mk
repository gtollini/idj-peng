################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/CameraFollower.cpp \
../src/Component.cpp \
../src/Face.cpp \
../src/Game.cpp \
../src/GameObject.cpp \
../src/InputManager.cpp \
../src/Music.cpp \
../src/Rect.cpp \
../src/Resources.cpp \
../src/Sound.cpp \
../src/Sprite.cpp \
../src/State.cpp \
../src/TileMap.cpp \
../src/TileSet.cpp \
../src/Vec2.cpp \
../src/main.cpp 

OBJS += \
./src/Camera.o \
./src/CameraFollower.o \
./src/Component.o \
./src/Face.o \
./src/Game.o \
./src/GameObject.o \
./src/InputManager.o \
./src/Music.o \
./src/Rect.o \
./src/Resources.o \
./src/Sound.o \
./src/Sprite.o \
./src/State.o \
./src/TileMap.o \
./src/TileSet.o \
./src/Vec2.o \
./src/main.o 

CPP_DEPS += \
./src/Camera.d \
./src/CameraFollower.d \
./src/Component.d \
./src/Face.d \
./src/Game.d \
./src/GameObject.d \
./src/InputManager.d \
./src/Music.d \
./src/Rect.d \
./src/Resources.d \
./src/Sound.d \
./src/Sprite.d \
./src/State.d \
./src/TileMap.d \
./src/TileSet.d \
./src/Vec2.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -I/usr/include/SDL2 -O0 -g3 -Wall -Wextra -Wconversion -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


