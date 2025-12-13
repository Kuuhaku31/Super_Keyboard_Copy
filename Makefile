
SRC_PATH = ./src
BUILD_PATH = ./build
OUT_PATH = ./out

SRC_MAIN = $(SRC_PATH)/main.cpp
SRC_COPY = $(SRC_PATH)/copy.cpp
SRC_UTIL = $(SRC_PATH)/util.cpp
SRC_HEADER = $(SRC_PATH)/header.h

OBJ_MAIN = $(BUILD_PATH)/main.o
OBJ_COPY = $(BUILD_PATH)/copy.o
OBJ_UTIL = $(BUILD_PATH)/util.o

INCLUDE_PATH = $(SRC_PATH)

CXX = g++
CXXFLAGS = -I$(INCLUDE_PATH)

IS_DEBUG ?= 0
ifeq ($(IS_DEBUG), 1)
	CXXFLAGS += -DDEBUG -g -O0
endif

.PHONY: make_dirs c

# 生成目标文件
$(OBJ_MAIN): $(SRC_MAIN)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_MAIN) $(SRC_MAIN)
$(OBJ_COPY): $(SRC_COPY) $(SRC_HEADER)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_COPY) $(SRC_COPY)
$(OBJ_UTIL): $(SRC_UTIL) $(SRC_HEADER)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_UTIL) $(SRC_UTIL)

main: $(OBJ_MAIN) $(OBJ_COPY) $(OBJ_UTIL)
	$(CXX) $(CXXFLAGS) -o $(OUT_PATH)/$@.exe $(OBJ_MAIN) $(OBJ_COPY) $(OBJ_UTIL)

rmain: main
	(cd $(OUT_PATH) && ./main.exe)

make_dirs:
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(OUT_PATH)

c:
	@rm -rf $(BUILD_PATH)/*
	@rm -rf $(OUT_PATH)/*