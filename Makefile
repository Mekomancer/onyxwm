# Compiler, default is gcc
CC = gcc
# Compiler flags, enable verbose warnings and optimize for speed
CFLAGS = -Wall -Wextra -O2
# Libraries, xcb and xcb keysyms helper
LIBS = -lxcb -xcb-keysyms
# Files to be compiled
SRCS = $(shell find src -name "*.c")
# What files will be compiled into
OBJS := $(SRCS:.c=.o)
# Final executable name
TARGET := onyxwm

all: $(TARGET)
# target onyxwm
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
