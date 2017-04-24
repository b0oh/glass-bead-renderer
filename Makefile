CC = clang
BUILD_DIR = _build

CFLAGS = -O3 -Wall -Wextra -pedantic -std=c11 -g -I$(BUILD_DIR) -fsanitize=address
LDFLAGS = -lSDL2 -lSDL2_ttf


gbr: $(BUILD_DIR)/screen.o $(BUILD_DIR)/canvas.o $(BUILD_DIR)/ticks.o src/main.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

$(BUILD_DIR)/%.o: src/%.h src/%.c | $(BUILD_DIR)
	$(CC) -c -o $@ src/$*.c $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*
	rm gbr
