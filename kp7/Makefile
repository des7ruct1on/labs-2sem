CC = gcc
CFLAGS = -std=c99 -Wall -Werror
LDFLAGS = -lm
DEBUG = gdb
FILEOUT = vector.out
SOURCES = vector.c execute.c

all: $(FILEOUT)

$(FILEOUT): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(LDFLAGS) -o $(FILEOUT)

clean:
	rm -f *.out

debug:
	$(CC) $(CFLAGS) -g $(SOURCES) $(LDFLAGS)
	sudo $(DEBUG) $(FILEOUT)

cmp: $(FILEOUT)

run:
	./$(FILEOUT) $(FILE)
