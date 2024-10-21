CC = gcc

CFLAGS = -Wall -Wextra -std=c11

LIBS = -lhidapi-libusb

TARGETS = test.out sync.out single.out zone.out

SRCS = test.c sync.c single.c zone.c

OBJS = $(SRCS:.c=.o)

all: $(TARGETS)

test.out: test.o
	$(CC) $(CFLAGS) -o $@ test.o $(LIBS)

sync.out: sync.o
	$(CC) $(CFLAGS) -o $@ sync.o $(LIBS)

single.out: single.o
	$(CC) $(CFLAGS) -o $@ single.o $(LIBS)

zone.out: zone.o
	$(CC) $(CFLAGS) -o $@ zone.o $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
