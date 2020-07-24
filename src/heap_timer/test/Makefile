CC = g++
LD = g++
TARGET = test
INCLUDES = -I./ -I../
LIB = -L./ -I../
CFLAGS = -std=c++11 -Wall
SRC := CTimerTest.cpp ../CTimer.hpp
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