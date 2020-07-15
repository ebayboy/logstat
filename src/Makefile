CC = g++
LD = g++
SRCS = $(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

INCLUDE = -I./include -I./test
LIB = -L./libs -lhiredis -levent
CFLAGS = -std=c++11 -Wall -Wextra -Wcast-align -Wno-ctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wno-float-equal

TARGET = logstat

.PHONY:all clean

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(LD) -o $@ $^ $(INCLUDE) $(LIB) 

%.o:%.cpp 
	$(CC) -c -g $< $(INCLUDE) $(CFLAGS) -o $@ -MD -MF $*.d -MP

clean:
	rm -f $(OBJS) *.d $(TARGET)*

-include $(DEPS)
