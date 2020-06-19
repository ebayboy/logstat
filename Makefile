

#SUBDIRS := $(wildcard */.)
SUBDIRS := ./src
 
TARGET = riskstat

all: $(TARGET)

$(TARGET):
	$(MAKE) -C $(SUBDIRS)

clean: $(SUBDIRS)
	$(MAKE) $@ -C $(SUBDIRS)

.PHONY: all clean $(SUBDIRS)

