CC = g++
LD = g++
TARGET = test
INCLUDES = 
LIB = 
CFLAGS = -g -O0 -std=c++17 -Wall

SRC := *.c

OBJS=$(SRC:.cpp=.o)

.PHONY:all clean

all: $(TARGET)
$(TARGET): $(OBJS)
	$(LD) -o $@ $^ $(INCLUDES) $(LIB) $(CFLAGS)

%.o:%.c
	$(CC) -c -g $< $(INCLUDES) $(CFLAGS) -o $@

clean:
	rm *.o $(TARGET)
