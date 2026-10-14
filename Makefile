# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf)
LDLIBS   := $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf)
BUILD_DIR:= build
TARGET   := $(BUILD_DIR)/BattleTank

# Automatically find all .cpp files in src/ and its subdirectories
SRCS     := $(shell find src -type f -name "*.cpp")
# Map .cpp files to corresponding .o object files inside build/
OBJS     := $(SRCS:src/%.cpp=$(BUILD_DIR)/%.o)
# Generate .d dependency files to auto-detect header changes
DEPS     := $(OBJS:.o=.d)

.PHONY: all clean run

# Default target
all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDLIBS)

# Compile source files into object files (-MMD -MP creates header dependency rules)
$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Include dependency files if they exist
-include $(DEPS)

# Run the compiled application
run: all
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)