
SRC_PATH = ./src
BUILD_PATH = ./build
OUT_PATH = ./out

SRC += $(SRC_PATH)/main.cpp
SRC += $(SRC_PATH)/color_io.h
SRC += $(SRC_PATH)/header.h
SRC += $(SRC_PATH)/copy.cpp
SRC += $(SRC_PATH)/util.cpp

OBJ = $(patsubst $(SRC_PATH)/%.cpp,$(BUILD_PATH)/%.o,$(filter %.cpp,$(SRC)))

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -I$(SRC_PATH)

TARGET = $(OUT_PATH)/super_keyboard_copy.exe

all: $(TARGET)

$(TARGET): $(OBJ) $(SRC_PATH)/header.h $(SRC_PATH)/color_io.h
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_PATH)/*.o
	rm -rf $(OUT_PATH)/*.exe

rm: $(TARGET)
	./out/super_keyboard_copy.exe ./out/test.txt