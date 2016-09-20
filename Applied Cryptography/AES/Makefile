CC = g++
CFLAGS = -Wall -g

all : hw5

hw5: hw5.o tablecheck.o modprod.o keyexpand.o encrypt.o decrypt.o inverse.o
	${CC} ${CFLAGS} hw5.o tablecheck.o modprod.o keyexpand.o encrypt.o decrypt.o inverse.o -o hw5

hw5.o: hw5.cpp tablecheck.h modprod.h keyexpand.h encrypt.h decrypt.h inverse.h
	${CC} ${CFLAGS} -c hw5.cpp 

tablecheck.o: tablecheck.cpp tablecheck.h modprod.h
	${CC} ${CFLAGS} -c tablecheck.cpp 

modprod.o: modprod.cpp modprod.h
	${CC} ${CFLAGS} -c modprod.cpp 

keyexpand.o: keyexpand.cpp keyexpand.h modprod.h tablecheck.h
	${CC} ${CFLAGS} -c keyexpand.cpp 

encrypt.o: encrypt.cpp encrypt.h tablecheck.h modprod.h
	${CC} ${CFLAGS} -c encrypt.cpp 

decrypt.o: decrypt.cpp decrypt.h tablecheck.h modprod.h
	${CC} ${CFLAGS} -c decrypt.cpp 

inverse.o: inverse.cpp inverse.h modprod.h
	${CC} ${CFLAGS} -c inverse.cpp 

clean:
	rm -f *.o hw5


