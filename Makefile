
SRC_PATH = ./src
BUILD_PATH = ./build
OUT_PATH = ./out


make_dirs:
	@mkdir -p $(BUILD_PATH)
	@mkdir -p $(OUT_PATH)

test01: make_dirs $(SRC_PATH)/test/test01.cpp
	g++ -o $(OUT_PATH)/$@.exe $(SRC_PATH)/test/test01.cpp
	$(OUT_PATH)/$@.exe

test02: make_dirs $(SRC_PATH)/test/test02.cpp $(SRC_PATH)/utf_reader.h
	g++ -o $(OUT_PATH)/$@.exe $(SRC_PATH)/test/test02.cpp -I$(SRC_PATH)
	$(OUT_PATH)/$@.exe


main: make_dirs $(SRC_PATH)/main.cpp $(SRC_PATH)/copy.cpp $(SRC_PATH)/header.h $(SRC_PATH)/utf_reader.h
	g++ -o $(OUT_PATH)/$@.exe $(SRC_PATH)/main.cpp $(SRC_PATH)/copy.cpp -I$(SRC_PATH)

rm: main
	(cd $(OUT_PATH) && ./main.exe)


c:
	@rm -rf $(BUILD_PATH)
	@rm -rf $(OUT_PATH)


test03: make_dirs $(SRC_PATH)/test/test03.cpp $(SRC_PATH)/copy.cpp
	g++ -o $(OUT_PATH)/$@.exe $(SRC_PATH)/test/test03.cpp $(SRC_PATH)/copy.cpp -I$(SRC_PATH)
	(cd $(OUT_PATH) && ./test03.exe)

test03_debug: make_dirs $(SRC_PATH)/test/test03.cpp $(SRC_PATH)/copy.cpp
	g++ -g -O0 -DDEBUG -o $(OUT_PATH)/test03_debug.exe $(SRC_PATH)/test/test03.cpp $(SRC_PATH)/copy.cpp -I$(SRC_PATH)

main_debug: make_dirs $(SRC_PATH)/main.cpp $(SRC_PATH)/copy.cpp $(SRC_PATH)/header.h $(SRC_PATH)/utf_reader.h
	g++ -g -O0 -DDEBUG -o $(OUT_PATH)/main_debug.exe $(SRC_PATH)/main.cpp $(SRC_PATH)/copy.cpp -I$(SRC_PATH)
