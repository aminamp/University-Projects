CC = g++
CFLAGS = -Wall -g

all : hw3

hw3: hw3.o crypt.o histo.o invkey.o keygen.o solve.o
	${CC} ${CFLAGS} hw3.o crypt.o histo.o invkey.o keygen.o solve.o -I/home/scf-22/csci551b/openssl/include -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm -o hw3

hw3.o: hw3.cpp keygen.h crypt.h histo.h invkey.h solve.h
	${CC} ${CFLAGS} -c hw3.cpp -I/home/scf-22/csci551b/openssl/include

keygen.o: keygen.cpp keygen.h
	${CC} ${CFLAGS} -c keygen.cpp -I/home/scf-22/csci551b/openssl/include

crypt.o: crypt.cpp crypt.h
	${CC} ${CFLAGS} -c crypt.cpp 

histo.o: histo.cpp histo.h
	${CC} ${CFLAGS} -c histo.cpp 

invkey.o: invkey.cpp invkey.h
	${CC} ${CFLAGS} -c invkey.cpp 

solve.o: solve.cpp solve.h
	${CC} ${CFLAGS} -c solve.cpp 

clean:
	rm -f *.o hw3


