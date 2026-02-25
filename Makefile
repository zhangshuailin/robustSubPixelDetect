# 编译器和工具
CXX = g++
RM = del

# 目录配置
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# OpenCV 路径（根据你的安装路径修改）
OPENCV_DIR = D:/opencvmingw/build/install
OPENCV_INCLUDE = $(OPENCV_DIR)/include
OPENCV_LIB = $(OPENCV_DIR)/x64/mingw/lib

# 编译选项
CXXFLAGS = -I$(INCLUDE_DIR) -I$(OPENCV_INCLUDE) -Wall -O2 -std=c++17 -D_USE_MATH_DEFINES
LDFLAGS = -L$(OPENCV_LIB)
LIBS = -lopencv_world4140

# 目标程序
TARGET = $(BIN_DIR)/robustSubPixelDetect.exe

# 源文件和对象文件
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# 主目标
all: $(BIN_DIR) $(OBJ_DIR) $(TARGET)

# 创建必要的目录
$(BIN_DIR):
	mkdir $(BIN_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# 链接目标程序
$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	@echo Build successful: $@

# 编译源文件为对象文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译产物
clean:
	@echo Cleaning...
	-$(RM) /S /Q $(OBJ_DIR)
	-$(RM) /S /Q $(BIN_DIR)

# 其他命令
run: $(TARGET)
	$(TARGET)

.PHONY: all clean run