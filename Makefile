# Compiler
CC = gcc

# Executable
EXE = main

SRCDIR = src
OBJDIR = .obj
MKDIRS = $(OBJDIR)

CFILE  = $(foreach dir, $(SRCDIR), $(notdir $(wildcard $(dir)/*.c)))
OBJS   = $(CFILE:%.c=$(OBJDIR)/%.o)

# Link
$(EXE): $(OBJS)
	$(CC) -o $(SRCDIR)/$(EXE) $(OBJS)

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $^

clean:
	rm -rf $(SRCDIR)/$(EXE) $(OBJDIR)

$(info $(shell mkdir -p $(MKDIRS)))
