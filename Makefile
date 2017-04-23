CC = clang
BUILD_DIR = _build

COMPILER_FLAGS = -O3 -Wall -Wextra -pedantic -std=c11 -g
LINKER_FLAGS = -lSDL2 -lSDL2_ttf

$(BUILD)/screen.o: src/screen.h src/screen.c
	$(CC) -c -o $(BUILD_DIR)/screen.o src/screen.c $(COMPILER_FLAGS)

$(BUILD)/canvas.o: src/canvas.h src/canvas.c
	$(CC) -c -o $(BUILD_DIR)/canvas.o src/canvas.c $(COMPILER_FLAGS)

gbr: $(BUILD)/screen.o $(BUILD)/canvas.o src/event.h src/main.c
	$(CC) -o gbr $(BUILD_DIR)/screen.o $(BUILD_DIR)/canvas.o src/main.c $(COMPILER_FLAGS) $(LINKER_FLAGS)
