CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm -fopenmp

LIBDIR = lib
BUILDDIR = build

SRCS1 = solution1.c $(wildcard $(LIBDIR)/*.c)
SRCS2 = solution2.c $(wildcard $(LIBDIR)/*.c)
OBJS1 = $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SRCS1)))
OBJS2 = $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SRCS2)))
TARGET1 = solution1
TARGET2 = solution2

.PHONY: all clean

all: $(BUILDDIR) $(TARGET1) $(TARGET2)
	@echo "Compilation successful."

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(TARGET1): $(OBJS1)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET2): $(OBJS2)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: $(LIBDIR)/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(TARGET1) $(TARGET2)
