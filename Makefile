# Spiderq Makefile
# Copyright (C) 2012-2012 Qteqpid <glloveyp at 163 dot com>
# This file is released under the BSD license, see the LICENSE file

TARGET=main
SOURCES=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SOURCES))

CXX:=gcc
OPTIMIZATION?=-O2 -DNDEBUG
WARNINGS=-Wall
#WARNINGS=-Wall -Werror
REAL_CXXFLAGS=$(OPTIMIZATION) $(CXXFLAGS) $(WARNINGS) $(DEBUG) $(PROF) 
REAL_LDFLAGS=$(LDFLAGS) $(PROF) -rdynamic -lpthread -levent -lcrypt -ldl



all: $(TARGET)
	@if [ ! -d ../download ]; then mkdir ../download; fi

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

.c.o:
	$(CXX) -c $(REAL_CXXFLAGS) $<

clean:
	-rm -rf $(TARGET) $(OBJS)
	-rm -rf ../$(TARGET)

debug:
	$(MAKE) OPTIMIZATION="" DEBUG="-g -ggdb -g3"

gprof:
	$(MAKE) PROF="-pg" 

install:
	-cp -f $(TARGET) ../

.PHONY: all clean debug gprof install
