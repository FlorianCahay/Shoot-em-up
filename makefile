EXEC = project
CC = gcc
# Fichiers sources
SRCDIR = src
# Fichiers en-têtes
INCDIR = include
# Fichiers générés
BINDIR = bin
# Options
CFLAGS = -ansi -Wall -Wfatal-errors `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`
# Chemins des fichiers .c et .o
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS) $(LDLIBS)

$(BINDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/%.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

mrproper: clean
	rm -f $(BINDIR)/$(EXEC)


