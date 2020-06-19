
CC = g++
LD = g++
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

INCLUDE = -I./include

# -L指定库文件目录，-l指定静态库名字(去掉文件名中的lib前缀和.a后缀)
LIB = -L./libs 

CFLAGS = -std=c++11 -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wno-ctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wno-float-equal

TARGET = riskstat_cpp

.PHONY:all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LIB)

%.o:%.cpp
	$(CC) -c $^ $(INCLUDE) $(CFLAGS) 

clean:
	rm -f $(OBJS) $(TARGET)*
