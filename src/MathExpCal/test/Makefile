CC = g++
LD = g++
TARGET = test
INCLUDES = -I./
LIB = -L./
CFLAGS = -std=c++11 -Wall
SRC := $(wildcard *.cpp)
OBJS=$(SRC:.cpp=.o)
#$(warning  DEPS: $(DEPS))
.PHONY:all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(INCLUDES) $(LIB)
%.o:%.cpp
	$(CC) -c -g $< $(INCLUDES) $(CFLAGS) -o $@
clean:
	rm $(TARGET) $(OBJS) *.exe