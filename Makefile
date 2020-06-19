

#SUBDIRS := $(wildcard */.)
SUBDIRS := ./src
 
TARGET = riskstat_cpp

all: $(TARGET)

$(TARGET):
	$(MAKE) -C $(SUBDIRS)
	cp src/$(TARGET) . 

clean: $(SUBDIRS)
	$(MAKE) $@ -C $(SUBDIRS)

.PHONY: all clean $(SUBDIRS)

