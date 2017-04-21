CC = clang
BUILD_DIR = _build

COMPILER_FLAGS = -O3 -Wall -Wextra -pedantic -std=c11 -g
LINKER_FLAGS = -lSDL2 -lSDL2_ttf

$(BUILD)/canvas.o: src/canvas.h src/canvas.c
	$(CC) -c -o $(BUILD_DIR)/canvas.o src/canvas.c $(COMPILER_FLAGS)

gbr: $(BUILD)/canvas.o src/event.h src/main.c
	$(CC) -o gbr $(BUILD_DIR)/canvas.o src/main.c $(COMPILER_FLAGS) $(LINKER_FLAGS)
