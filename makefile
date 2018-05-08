CFLAGS=-g
#CFLAGS=
#CFLAGS+=-DDEBUG
#CFLAGS+=-DJSONDEBUG

all: calc.o list.o list_map.o improved_list_iterator.o hash_map.o JParser.o calcul.o
	gcc $(CFLAGS) calc.o list.o list_map.o improved_list_iterator.o hash_map.o JParser.o calcul.o
main: calc.c
	gcc $(CFLAGS) -c calc.c
list: list.c
	gcc $(CFLAGS) -c list.c
list_iterator: improved_list_iterator.c
	gcc $(CFLAGS) -c improved_list_iterator.c
simple_map: list_map.c
	gcc $(CFLAGS) -c list_map.c
hash_map: hash_map.c
	gcc $(CFLAGS) -c hash_map.c
json_parser: JParser.c
	gcc $(CFLAGS) -c JParser.c
calcul: calcul.c
	gcc $(CFLAGS) -c calcul.c
clear:
	rm *.o a.out
