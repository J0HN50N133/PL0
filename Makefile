SRC=src

OBJECTS = token.o

.SILENT: all token.o clean

all: $(OBJECTS)
	flex $(SRC)/scanner.l
	gcc -g lex.yy.c $(OBJECTS) -lfl -o pl0

token.o: $(SRC)/token.h $(SRC)/token.c $(SRC)/array.h
	gcc -g -c $(SRC)/token.c

clean:
	rm -f *.o a.out lex.yy.c

test: all
	./pl0 test/squares.pl0
	./pl0 test/prime.pl0

leak_check: all
	valgrind --leak-check=full --show-leak-kinds=all ./pl0 test/squares.pl0
	valgrind --leak-check=full --show-leak-kinds=all ./pl0 test/prime.pl0
