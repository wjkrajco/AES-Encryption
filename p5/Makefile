all: encrypt decrypt

encrypt: encrypt.o io.o aes.o field.o
	gcc encrypt.o io.o aes.o field.o -o encrypt

decrypt: decrypt.o io.o aes.o field.o
	gcc decrypt.o io.o aes.o field.o -o decrypt

fieldTest: fieldTest.o field.o
	gcc fieldTest.o field.o -o fieldTest

aesTest: aesTest.o aes.o field.o
	gcc aesTest.o aes.o field.o -o aesTest

encrypt.o: encrypt.c io.h aes.h field.h
	gcc -g -Wall -std=c99 -c -o encrypt.o encrypt.c

decrypt.o: decrypt.c io.h aes.h field.h
	gcc -g -Wall -std=c99 -c -o decrypt.o decrypt.c

fieldTest.o: fieldTest.c field.h
	gcc -g -Wall -std=c99 -c -o fieldTest.o fieldTest.c

aesTest.o: aesTest.c aes.h field.h
	gcc -g -Wall -std=c99 -c -o aesTest.o aesTest.c

io.o: io.c io.h field.h
	gcc -c -Wall -std=c99 -g io.c -o io.o

aes.o: aes.c aes.h field.h
	gcc -c -Wall -std=c99 -g aes.c -o aes.o

field.o: field.c field.h
	gcc -g -Wall -std=c99 -c -o field.o field.c



clean:
	rm -f *.o
	rm -f aesTest
	rm -f fieldTest
	rm -f encrypt
	rm -f decrypt
	rm -f output.dat
	rm -f output.txt
	rm -f stderr.txt