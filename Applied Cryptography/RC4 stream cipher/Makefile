CC = g++
CFLAGS = -Wall -g

all : hw7

hw7: hw7.o rc4.o x1.o x2.o x3.o x4.o x5.o
	${CC} ${CFLAGS} hw7.o rc4.o x1.o x2.o x3.o x4.o x5.o -I/home/scf-22/csci551b/openssl/include -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm -o hw7

hw7.o: hw7.cpp rc4.h x1.h x2.h x3.h x4.h x5.h
	${CC} ${CFLAGS} -c hw7.cpp -I/home/scf-22/csci551b/openssl/include

rc4.o: rc4.cpp rc4.h
	${CC} ${CFLAGS} -c rc4.cpp -I/home/scf-22/csci551b/openssl/include

x1.o: x1.cpp x1.h
	${CC} ${CFLAGS} -c x1.cpp -I/home/scf-22/csci551b/openssl/include

x2.o: x2.cpp x2.h
	${CC} ${CFLAGS} -c x2.cpp -I/home/scf-22/csci551b/openssl/include

x3.o: x3.cpp x3.h 
	${CC} ${CFLAGS} -c x3.cpp -I/home/scf-22/csci551b/openssl/include

x4.o: x4.cpp x4.h 
	${CC} ${CFLAGS} -c x4.cpp -I/home/scf-22/csci551b/openssl/include

x5.o: x5.cpp x5.h 
	${CC} ${CFLAGS} -c x5.cpp -I/home/scf-22/csci551b/openssl/include

clean:
	rm -f *.o hw7


