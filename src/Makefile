
CC = g++
LD = g++
SRCS = $(wildcard *.cpp)
OBJS = $(patsubst %cpp, %o, $(SRCS))

INCLUDE = -I./include

# -L指定库文件目录，-l指定静态库名字(去掉文件名中的lib前缀和.a后缀)
LIB = -L./libs -lpthread

CFLAGS = -g -Wall -O3

TARGET = riskstat

.PHONY:all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(LIB)

%o:%cpp
	$(CC) -c $^ $(INCLUDE) $(CFLAGS) 

clean:
	rm -f $(OBJS) $(TARGET)
