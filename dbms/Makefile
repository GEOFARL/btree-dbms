# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

# Directories
SRC_DIR = src
OBJ_DIR = obj
BUILD_DIR = build

# Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
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
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/my_program