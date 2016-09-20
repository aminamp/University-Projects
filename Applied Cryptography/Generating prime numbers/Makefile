CC = g++
CFLAGS = -Wall -g -Wno-sign-compare

all : hw6

hw6: hw6.o primes.o trialdiv.o millerrabin.o rndsearch.o maurer.o
	${CC} ${CFLAGS} hw6.o primes.o trialdiv.o millerrabin.o rndsearch.o maurer.o -I/home/scf-22/csci551b/openssl/include -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm -o hw6

hw6.o: hw6.cpp primes.h trialdiv.h millerrabin.h rndsearch.h maurer.h
	${CC} ${CFLAGS} -c hw6.cpp -I/home/scf-22/csci551b/openssl/include

primes.o: primes.cpp primes.h
	${CC} ${CFLAGS} -c primes.cpp -I/home/scf-22/csci551b/openssl/include

trialdiv.o: trialdiv.cpp trialdiv.h
	${CC} ${CFLAGS} -c trialdiv.cpp -I/home/scf-22/csci551b/openssl/include

millerrabin.o: millerrabin.cpp millerrabin.h
	${CC} ${CFLAGS} -c millerrabin.cpp -I/home/scf-22/csci551b/openssl/include

rndsearch.o: rndsearch.cpp rndsearch.h millerrabin.h trialdiv.h
	${CC} ${CFLAGS} -c rndsearch.cpp -I/home/scf-22/csci551b/openssl/include

maurer.o: maurer.cpp maurer.h trialdiv.h
	${CC} ${CFLAGS} -c maurer.cpp -I/home/scf-22/csci551b/openssl/include

clean:
	rm -f *.o hw6


