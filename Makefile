# Compiler
CC = gcc

# Executable
EXE = main

# Utility
PKG_CON = pkg-config
GTK = gtk4

SRCDIR = src
OBJDIR = .obj
MKDIRS = $(OBJDIR)

CFILE  = $(foreach dir, $(SRCDIR), $(notdir $(wildcard $(dir)/*.c)))
OBJS   = $(CFILE:%.c=$(OBJDIR)/%.o)

# Link
$(EXE): $(OBJS)
	$(CC) -o $(SRCDIR)/$(EXE) $(OBJS) `$(PKG_CON) --libs $(GTK)`

# Compile
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ `$(PKG_CON) --cflags $(GTK)` $^

clean:
	rm -rf $(SRCDIR)/$(EXE) $(OBJDIR)

$(info $(shell mkdir -p $(MKDIRS)))
