# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -Wpedantic

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Source files (list them explicitly)
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)

# Generate corresponding object file names
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
EXE := $(BUILD_DIR)/program

# Targets
all: $(EXE)

$(EXE): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/program

EXE := $(BUILD_DIR)/program
