gq: gq.o types.o queue.o input.o
	gcc gq.o types.o queue.o input.o -o gq

gq.o: gq.c types.h queue.h input.h
	gcc -g -Wall -std=c99 -c -o gq.o gq.c

types.o: types.c types.h queue.h
	gcc -c -Wall -std=c99 -g types.c -o types.o

queue.o: queue.c queue.h
	gcc -g -Wall -std=c99 -c -o queue.o queue.c

input.o: input.c input.h
	gcc -g -Wall -std=c99 -c -o input.o input.c

clean:
	rm -f *.o
	rm -f gq
	rm -f output.txt
	rm -f stderr.txt