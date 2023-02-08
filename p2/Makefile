infix_10: infix.o number_10.o operation.o 
	gcc infix.o number_10.o operation.o -o infix_10

infix.o: infix.c operation.h number.h
	gcc -g -Wall -std=c99   -c -o infix.o infix.c

number_10.o: number_10.c number.h operation.h
	gcc -c -Wall -std=c99 -g number_10.c -o number_10.o

operation.o: operation.c operation.h
	gcc -g -Wall -std=c99   -c -o operation.o operation.c



infix_12: infix.o number_12.o operation.o

infix.o: infix.c operation.h number.h

number_12.o: number_12.c number.h operation.h

operation.o: operation.c operation.h

clean:
	rm -f *.o
	rm -f output.txt