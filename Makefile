

#SUBDIRS := $(wildcard */.)
SUBDIRS := ./src
 
TARGET = riskstat_cpp

all: $(TARGET)

$(TARGET):
	$(MAKE) -C $(SUBDIRS)

clean: $(SUBDIRS)
	$(MAKE) $@ -C $(SUBDIRS)

.PHONY: all clean $(SUBDIRS)

