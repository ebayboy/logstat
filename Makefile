

#SUBDIRS := $(wildcard */.)
SUBDIRS := ./src
 
TARGET = logstat

all: $(TARGET)

$(TARGET):
	$(MAKE) -C $(SUBDIRS)

clean: $(SUBDIRS)
	$(MAKE) $@ -C $(SUBDIRS)

.PHONY: all clean $(SUBDIRS)

