
CC = g++
LD = g++
SRCS = $(wildcard *.cpp)
SRCS_TEST = $(wildcard test/*.cpp)

OBJS = $(patsubst %.cpp, %.o, $(SRCS))
OBJS_TEST = $(patsubst %.cpp, %.o, $(SRCS_TEST))

INCLUDE = -I./include -I./test

# -L指定库文件目录，-l指定静态库名字(去掉文件名中的lib前缀和.a后缀)
LIB = -L./libs -lhiredis -levent

CFLAGS = -std=c++11 -Wall -Wextra -Wcast-align -Wno-ctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wno-float-equal

TARGET = logstat

.PHONY:all clean

all: $(TARGET)

$(TARGET): $(OBJS_TEST) $(OBJS)
	$(LD) -o $@ $^ $(LIB)

%.o:%.cpp
	$(CC) -c $^ $(INCLUDE) $(CFLAGS) -o $@

clean:
	rm -f $(OBJS) $(OBJS_TEST) $(TARGET)*
