CC = gcc
CFLAGS = -Wall -Wextra -O2 -g
LDFLAGS = -lm -fopenmp

LIBDIR = lib
SRCS1 = solution1.c $(wildcard $(LIBDIR)/*.c)
SRCS2 = solution2.c $(wildcard $(LIBDIR)/*.c)
OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)
TARGET1 = solution1
TARGET2 = solution2

.PHONY: all clean

all: $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET2): $(OBJS2)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS1) $(OBJS2) $(TARGET1) $(TARGET2)
