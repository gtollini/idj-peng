COMPILER = g++

DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP =MF $@

LIBS = -lSDL2 -SDL2_image -lSDL2_mixer -lSDL2_ttf -lm

INC_PATHS = -I$ (INC_PATH) $(addprefix -I, $(SDL_INC_PATH));

FLAGS= -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self

DFLAGS= -ggdb -O0 -DDEBUG

RFLAGS = -03 -mtune=native

INC_PATH= include
SRC_PATH= src 
BIN_PATH= bin 
DEP_PATH= dep 

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(SRC_PATH)/*.h)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d, $(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

EXEC = JOGO


ifeq($(OS),Windows_NT)

RMDIR = rd /s /q

RM = del /q

SDL_PATHS = D:

SDL_INC_PATH += $(addsuffix /include,$(SDL_PATHS))
LINK_PATH = $(addprefix -L, $(addsuffix) /lib,$(SDL_PATHS))
FLAGS += -mwindows
DFLAGS += -mconsole
LIBS := -lmingw32 -lSDL2main $(LIBS)

EXEC := $(EXEC).exe 

else

UNAME_S := $(shell uname -s)

ifeq($(UNAME_S), Darwin)

LIBS = -lm -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf

endif
endif

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(LINK_PATH) $(LIBS) $FLAGS

$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATH) $(addprefix $(SRC_PATH)/.$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATH) $< $(DEP_FLAGS) $FLAGS

.SECONDEXPANSION:
-include $$(DEP_FILES)	