CC = clang
BUILD_DIR = _build

COMPILER_FLAGS = -O3 -Wall -Wextra -pedantic -std=c11 -g -I$(BUILD_DIR)
LINKER_FLAGS = -lSDL2 -lSDL2_ttf

$(BUILD_DIR)/screen.o: src/screen.h src/screen.c
	$(CC) -c -o $@ src/screen.c $(COMPILER_FLAGS)

$(BUILD_DIR)/canvas.o: src/canvas.h src/canvas.h
	$(CC) -c -o $@ src/canvas.c $(COMPILER_FLAGS)

$(BUILD_DIR)/ticks.o: src/ticks.h src/ticks.c
	$(CC) -c -o $@ src/ticks.c $(COMPILER_FLAGS)

gbr: $(BUILD_DIR)/screen.o $(BUILD_DIR)/canvas.o $(BUILD_DIR)/ticks.o src/main.c
	$(CC) -o $@ $^ $(COMPILER_FLAGS) $(LINKER_FLAGS)

clean:
	rm -rf $(BUILD_DIR)/*
	rm gbr
