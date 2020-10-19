CC = g++
LD = g++

TARGET = test

INCLUDES = -I ./..  
INCLUDES += -I /usr/local/googletest/include/ 

LIB = -L /usr/local/googletest/lib64/

CFLAGS = -c -g -O0 -std=c++17 -Wall

LDFLAGS = -lgtest -lpthread

SRC_C := ../base64.c
SRC_CPP := test.cpp main.cpp

OBJS_C=$(SRC_C:.c=.o)
OBJS_CPP=$(SRC_CPP:.cpp=.o)

#$(warning $(OBJS_C))

.PHONY:all clean

all: $(TARGET)
$(TARGET): $(OBJS_C) $(OBJS_CPP)
	$(LD) $^ -o $@ $(LDFLAGS) $(LIB) 
	./$(TARGET)

%.o:%.c
	$(CC) $(CFLAGS) $< $(INCLUDES) -o $@

%.o:%.cpp
	$(CC) $(CFLAGS) $< $(INCLUDES) -o $@

clean:
	rm -rf $(TARGET) $(OBJS_C) $(OBJS_CPP)

