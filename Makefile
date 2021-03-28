OBJS = main.cpp src/Game.cpp src/Ground.cpp src/Player.cpp

CC = g++

COMPILER_FLAGS = -w

LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ_NAME = apple_catch

INSTALL_DIR = ./
DIR_NAME = applecatch/

HEADER_DIR = headers/

all : $(OBJS)
	make createdir
	make copybin
	make compile
createdir:
	mkdir $(INSTALL_DIR)applecatch || echo "Install directory already exists" 
copybin:
	cp -rf ./bin $(INSTALL_DIR)$(DIR_NAME)
compile:
	$(CC) $(OBJS) -I $(HEADER_DIR) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(INSTALL_DIR)applecatch/$(OBJ_NAME)
