# gcc compliler
CC = gcc
# enable verbose warnings and optimize for speed
CFLAGS = -Wall -Wextra -O2
# xcb and xcb keykodes
LIBS = -lxcb -xcb-keysyms
# target onyxwm
all: onyxwm
# define target
onyxwm: main.c
	# build
	$(CC) $(CFLAGS) main.c -o onyxwm $(LIBS)
clean:
	rm -f onyxwm
