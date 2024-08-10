all : main.o common_functions.o read_store_update.o search.o
	gcc main.o common_functions.o read_store_update.o search.o -o inverted_search

main.o : main.c
	gcc -c main.c

common_functions.o : common_functions.c
	gcc -c common_functions.c

read_store_update.o : read_store_update.c
	gcc -c read_store_update.c

search.o : search.c
	gcc -c search.c

clean : 
	rm *.o inverted_search
