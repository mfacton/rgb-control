CC = gcc

CFLAGS = -Wall -Wextra -std=c11

LIBS = -lhidapi-libusb

TARGETS = test.out sync.out

SRCS = test.c sync.c

OBJS = $(SRCS:.c=.o)

all: $(TARGETS)

test.out: test.o
	$(CC) $(CFLAGS) -o $@ test.o $(LIBS)

sync.out: sync.o
	$(CC) $(CFLAGS) -o $@ sync.o $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGETS)
