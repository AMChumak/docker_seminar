CC ?= gcc
CPPFLAGS ?= -Iinclude
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2

BUILD_DIR := build
BIN_DIR := bin

APP := $(BIN_DIR)/text-report
CPU_HOG := $(BIN_DIR)/cpu-hog
MEMORY_HOG := $(BIN_DIR)/memory-hog

APP_OBJECTS := \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/text_stats.o

.PHONY: all clean app workloads

all: app workloads
app: $(APP)
workloads: $(CPU_HOG) $(MEMORY_HOG)

$(APP): $(APP_OBJECTS) | $(BIN_DIR)
	$(CC) $(APP_OBJECTS) -o $@

$(BUILD_DIR)/main.o: src/main.c include/text_stats.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/text_stats.o: src/text_stats.c include/text_stats.h | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(CPU_HOG): resource-lab/cpu_hog.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(MEMORY_HOG): resource-lab/memory_hog.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
