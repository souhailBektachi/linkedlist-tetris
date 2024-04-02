CC = g++
CFLAGS = -Wall -Wextra -std=c++11 -g -I src/include -I src/headers 
LDFLAGS = -L src/lib -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2main

TARGET = game
SRC_DIR = src/Cfiles
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES += main.cpp
OBJ_DIR = build
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ_FILES) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	del /s /q $(OBJ_DIR)/*.o

debug: CFLAGS += -DDEBUG
debug: all
