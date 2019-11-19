EXEC = main
CC = gcc
# Options
CFLAGS = -ansi -Wall -Wfatal-errors `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`
# Chemins des fichiers .c et .o
SRC = $(wildcard *.c)
OBJ = $(SRC:%.c=%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(BINDIR)/%.o: %.c %.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)

mrproper: clean
	rm -f $(EXEC)