# Author: Marcus Ross
#         MR867434

p2: clean main.o binaryrw.o
	gcc main.o binaryrw.o -o p2
main.o: main.c
	gcc -c main.c
binaryrw.o: binaryrw.c
	gcc -c binaryrw.c
clean:
	rm -f *.o core