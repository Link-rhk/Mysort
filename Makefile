# 定义变量
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = bin
OBJ_DIR = $(BUILD_DIR)
OUT_DIR = out

# 查找源文件
SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS_SRCS = $(notdir $(SRCS))
OBJS = $(SRCS_SRCS:.c=.o)

# 添加 main.c（假设在根目录）
MAIN_SRC = main.c
MAIN_OBJ = main.o

# 所有目标文件
ALL_OBJS = $(OBJS) $(MAIN_OBJ)

# 最终目标
TARGET = main_app

# 编译器设置
CC = gcc
CFLAGS += -I./$(INC_DIR)

# 目标文件路径（带构建目录）
OBJS_WITH_PATH = $(addprefix $(OBJ_DIR)/, $(ALL_OBJS))

#SRCS = $(wildcard src/*.c)
#SRCS_SRCS = $(notdir $(SRCS))
#OBJS = $(patsubst %.c,%.o,$(SRCS_SRCS))
#OBJ=main_app

#OBJ_DIR = bin
#SRC_DIR = src

#MAIN_OBJ = main.c
#MAIN_SRC = main.o
#CC = gcc
#CFLAGS += -I./inc

ifeq ($(OS),Windows_NT)
	make_dir =powershell -Command "New-Item -ItemType "Directory" -Force -Path"
	remove = powershell -Command "del -r"
	EXE_EXT= .exe
	move = powershell -Command "mv"
else
	make_dir = mkdir -p
	remove = rm -rf
	EXE_EXT = 
	move = mv 
endif

ifeq ("$(BUILDDIR)", "")
	BUILDDIR="./bin"
endif

#THIS_BUILD_DIR=$(BUILDDIR)

# 默认目标
all: clean init $(BUILD_DIR)/$(TARGET)$(EXE_EXT)

# 初始化：创建目录
init:
	@echo "creat dir: $(BUILD_DIR)"
	-$(make_dir) $(BUILD_DIR)
	-$(make_dir) $(OBJ_DIR)
	-$(make_dir) $(OUT_DIR)

# 链接：生成可执行文件
$(BUILD_DIR)/$(TARGET)$(EXE_EXT): $(OBJS_WITH_PATH)
	@echo "link: $@"
	$(CC) $(CFLAGS) -o $@ $^ -O2 -Werror
	-$(move) $(BUILD_DIR)/$(TARGET)$(EXE_EXT) $(OUT_DIR)


# 编译规则1：编译 src 目录下的 .c 文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "compile: $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@ -O2

# 编译规则2：编译根目录的 main.c
$(OBJ_DIR)/$(MAIN_OBJ): $(MAIN_SRC)
	@echo "compile: $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@ -O2

# 清理
clean:
	@echo "clean: $(BUILD_DIR)"
	-$(remove) $(BUILD_DIR)
	-$(remove) $(OUT_DIR)

# 显示信息
show:
	@echo "src: $(SRCS_SRCS)"
	@echo "bin: $(OBJS)"
	@echo "poix: $(OS)"
	@echo "build_dir: $(BUILD_DIR)"
	@echo "bin_dir: $(OBJ_DIR)"
	@echo "bin_dir: $(OBJS_WITH_PATH)"

.PHONY: all init clean show
