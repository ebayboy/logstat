CC = g++
LD = g++

INCLUDES = -I./include -I./test
LIB = -L./libs -lhiredis -levent
CFLAGS = -std=c++11 -Wall -Wextra -Wcast-align -Wno-ctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Woverloaded-virtual -Wredundant-decls -Wsign-promo -Wstrict-overflow=5 -Wswitch -Wundef -Wno-unused -Wnon-virtual-dtor -Wreorder -Wdeprecated -Wno-float-equal

#root src
ROOT_SRCS := $(wildcard *.cpp) 
ROOT_OBJS=$(ROOT_SRCS:.cpp=.o)

#add modules
MODULES   := func util redisHelper redisSubscriptHelper testRedisHelper
SUB_DIRS  := $(addprefix ./,$(MODULES))
SUB_SRCS  := $(foreach sdir,$(SUB_DIRS),$(wildcard $(sdir)/*.cpp))
SUB_OBJS=$(SUB_SRCS:.cpp=.o)
SUB_INCLUDES  := $(addprefix -I,$(SUB_DIRS))

DEPS=$(ROOT_SRCS:.cpp=.d)
DEPS+=$(SUB_SRCS:.cpp=.d)

#打印变量
#$(warning  DEPS: $(DEPS))

INCLUDES+=$(SUB_INCLUDES)

TARGET = logstat

.PHONY:all clean

all: $(TARGET)

$(TARGET): $(ROOT_OBJS) $(SUB_OBJS)
	$(LD) -o $@ $^ $(INCLUDES) $(LIB) 

%.o:%.cpp 
	$(CC) -c -g $< $(INCLUDES) $(CFLAGS) -o $@ -MD -MF $*.d -MP

clean:
	rm $(TARGET) $(ROOT_OBJS) $(SUB_OBJS)  $(DEPS)

-include $(DEPS)
