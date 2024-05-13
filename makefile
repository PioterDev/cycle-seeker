CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

SRCDIR = src
INCDIR = include
BUILDDIR = build

# Define source files and output executable
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(filter-out main.c, $(SRCS)))
EXEC = main

# Default target
all: $(EXEC)

# Rule to build executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Rule to compile source files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#Rule to compile main.c
#$(BUILDDIR)/main.o: main.c
#	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(EXEC) $(OBJS)