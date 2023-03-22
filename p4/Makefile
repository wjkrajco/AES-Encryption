schedule: schedule.o catalog.o input.o
	gcc schedule.o catalog.o input.o -o schedule

schedule.o: schedule.c catalog.h input.h
	gcc -g -Wall -std=c99 -c -o schedule.o schedule.c

catalog.o: catalog.c catalog.h input.h
	gcc -c -Wall -std=c99 -g catalog.c -o catalog.o

input.o: input.c input.h
	gcc -g -Wall -std=c99 -c -o input.o input.c

clean:
	rm -f *.o
	rm -f schedule
	rm -f output.txt
	rm -f stderr.txt