# Compiler
CC = gcc

# Directories
SRCDIR = src
BUILDDIR = build
TARGETDIR = bin
INCDIR = include

# Compiler flags
CFLAGS = -g -Wall -I $(INCDIR)

# Files and targets
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SRCS))
TARGET = $(TARGETDIR)/university_anniversary_management_system

# Default rule
all: directories $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: directories
directories:
	mkdir -p $(TARGETDIR)
	mkdir -p $(BUILDDIR)

.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(TARGETDIR)

.PHONY: run
run: all
	./$(TARGET)
