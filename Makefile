CC = g++
INCLUDE_DIR = -I/usr/include/ -I./src -I./src/sdl -I./src/sfml -I./src/base -I./src/core -I./src/txt 
CPP_FLAGS = -Wall -MMD -ggdb -std=c++14 -O2
SFML_LIB = -lsfml-window -lsfml-system -lsfml-graphics -lsfml-network -lsfml-audio
SFML_LIB_DIR =

# le ficher où il y a le main()
MAIN_CPP = src/main.cpp
MAIN_OBJ = obj/main.o
# nom de l'executable
BIN = bin/Iryal.io


# ne marche pas
FILE_NAME:
	UNAME_S = $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		CCFLAGS += -D LINUX -I./SFML_LINUX/include \
		SFML_LIB_DIR += -L./SFML_LINUX/lib
	endif
	ifeq ($(UNAME_S), Darwin)
		CCFLAGS += -D OSX \
		@echo Darwin
	endif
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P), x86_64)
		CCFLAGS += -D AMD64
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		CCFLAGS += -D IA32
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		CCFLAGS += -D ARM
	endif


# les chemin vers les ficher .cpp
CORE_CPP = $(wildcard src/core/*.cpp)
BASE_CPP = $(wildcard src/base/*.cpp)
SFML_CPP = $(wildcard src/sfml/*.cpp)
# et leurs .h correspondat
CORE_H = $(wildcard src/core/*.h)
BASE_H = $(wildcard src/base/*.h)
SFML_H = $(wildcard src/sfml/*.h)
# les ficher obj
CORE_O_TMP = $(notdir $(patsubst %.cpp,%.o,$(CORE_CPP)))
CORE_O = $(patsubst %.o,obj/%.o,$(CORE_O_TMP))
BASE_O_TMP = $(notdir $(patsubst %.cpp,%.o,$(BASE_CPP)))
BASE_O = $(patsubst %.o,obj/%.o,$(BASE_O_TMP))
SFML_O_TMP = $(notdir $(patsubst %.cpp,%.o,$(SFML_CPP)))
SFML_O = $(patsubst %.o,obj/%.o,$(SFML_O_TMP))

# liste des tous les fichiers .cpp
SRCS = $(CORE_CPP) $(BASE_CPP) $(SFML_CPP)
# all obj files
OBJ = $(CORE_O) $(BASE_O) $(SFML_O) $(MAIN_OBJ)
# la liste des dépandance crée pour les .cpp et .h
DEP = $(OBJ:%.o=%.d)


main: $(OBJ)
	@mkdir -p bin
	@echo $(CC) -o $(BIN) 
	@echo $(OBJ)
	@$(CC) -o $(BIN) $(OBJ) $(SFML_LIB_DIR) $(SFML_LIB)

.PHONY: clean

clean:
	rm obj/*
	rm bin/*


doc:
	@mkdir -p doc
	doxygen -g doc/Iryal.io.doxy
	

# Include all .d files
-include $(DEP)

# generation des fichiers obj
obj/%.o : src/%.cpp
	@mkdir -p obj
	@echo $@ $<
	@$(CC) $(CPP_FLAGS) -c $(INCLUDE_DIR) -o $@  $<

obj/%.o : src/mainTests/%.cpp
	@mkdir -p obj
	@echo $@ $<
	@$(CC) $(CPP_FLAGS) -c $(INCLUDE_DIR) -o $@  $<

obj/%.o : src/sfml/%.cpp
	@mkdir -p obj
	@echo $@ $<
	@$(CC) $(CPP_FLAGS) -c $(INCLUDE_DIR) -o $@  $<

obj/%.o : src/base/%.cpp
	@mkdir -p obj
	@echo $@ $<
	@$(CC) $(CPP_FLAGS) -c $(INCLUDE_DIR) -o $@  $<

obj/%.o : src/core/%.cpp
	@mkdir -p obj
	@echo $@ $<
	@$(CC) $(CPP_FLAGS) -c $(INCLUDE_DIR) -o $@  $<

obj/%.o : src/sdl/%.cpp
	@mkdir -p obj
	@echo $@ $<
	@$(CC) $(CPP_FLAGS) -c $(INCLUDE_DIR) -o $@  $<

obj/%.o : src/txt/%.cpp
	@mkdir -p obj
	@echo $@ $<
	@$(CC) $(CPP_FLAGS) -c $(INCLUDE_DIR) -o $@  $<
