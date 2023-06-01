CC = gcc
CFLAGS = -std=c99 -Wall -Werror 
DEBUG = gdb
FILEOUT = src/out/main.out
MAIN_SOURCES = src/main.c
GLOBALS_SOURCES = src/abiturient.c
CONV_TXT = src/txtToBin.c
CONV_BIN = src/binToTxt.c
CONVOUT = src/out/conv.out
GEN = src/dbgenerator.c
GENOUT = src/out/db.out

all:
	$(CC) $(CFLAGS) $(SOURCES)  -o $(FILEOUT)
	$(CC) $(CFLAGS) $(CONV) -o $(CONVOUT)
	$(CC) $(CFLAGS) $(GEN) -o $(GENOUT)
clean:
	rm -f *.out
debug:
	$(CC) -g $(CFLAGS) $(SOURCES)  -o $(FILEOUT)
	$(CC) -g $(CFLAGS) $(CONV) -o $(CONVOUT)
	$(CC) -g $(CFLAGS) $(GEN) -o $(GENOUT)
cmp:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(MAIN_SOURCES) -o $(FILEOUT)
main:
	./$(FILEOUT) $(FILE)
convertation:
	./$(CONVOUT) $(FILE1) $(FILE2)
generation:
	./$(GENOUT) $(FILE) 
converttxt:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(CONV_TXT) -o $(CONVOUT)
convertbin:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(CONV_BIN) -o $(CONVOUT)

generate:
	$(CC) $(CFLAGS) $(GLOBALS_SOURCES) $(GEN) -o $(GENOUT)
