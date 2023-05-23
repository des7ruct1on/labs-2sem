CC = gcc
CFLAGS = -std=c99 -Wall -Werror
GLOBALS = src/abiturient.c src/table.c

MAIN_SRC = src/main.c
MAIN_OUT = main.out
GEN_SRC = src/dbgenerator.c
GEN_OUT = dbgen.out 
CONV_SRC = src/generate.c
CONV_OUT = gen.out 

all: 
	$(CC) $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT) 
	$(CC) $(CFLAGS) $(GEN_SRC) -o $(GEN_OUT) 
	$(CC) $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT) 

generate: 
	$(CC) $(CFLAGS) $(GEN_SRC) -o $(GEN_OUT) 

convert: 
	$(CC) $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT) 

debug: 
	$(CC) -g $(CFLAGS) $(MAIN_SRC) -o $(MAIN_OUT) 
	$(CC) -g $(CFLAGS) $(GEN_SRC) -o $(GEN_OUT) 
	$(CC) -g $(CFLAGS) $(CONV_SRC) -o $(CONV_OUT) 

clean: 
	rm -f *.out