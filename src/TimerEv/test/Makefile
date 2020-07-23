CC = g++
LD = g++
TARGET = test
INCLUDES = -I./ -I../ -I../../include
LIB = -L./ -L../../libs
CFLAGS = -std=c++11 -Wall -levent
SRC := $(wildcard *.cpp) $(wildcard ../*.cpp) 
OBJS=$(SRC:.cpp=.o)
#$(warning  DEPS: $(DEPS))
.PHONY:all clean
all: $(TARGET)
$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(INCLUDES) $(LIB) $(CFLAGS)
%.o:%.cpp
	$(CC) -c -g $< $(INCLUDES) $(CFLAGS) -o $@
clean:
	rm $(TARGET) $(OBJS) *.exe