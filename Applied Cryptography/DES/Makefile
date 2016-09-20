CC = g++
CFLAGS = -Wall -g -Wno-missing-braces

all : hw4

hw4 : hw4.o tablecheck.o enc.o dec.o enc3.o dec3.o
	$(CC) $(CFLAGS) hw4.o tablecheck.o enc.o dec.o enc3.o dec3.o -o hw4

hw4.o : hw4.cpp tablecheck.h enc.h dec.h enc3.h dec3.h
	$(CC) $(CFLAGS) -c hw4.cpp

tablecheck.o : tablecheck.cpp tablecheck.h
		$(CC) $(CFLAGS) -c tablecheck.cpp

enc.o : enc.cpp enc.h tablecheck.h
	$(CC) $(CFLAGS) -c enc.cpp

dec.o : dec.cpp dec.h tablecheck.h enc.h
	$(CC) $(CFLAGS) -c dec.cpp

enc3.o : enc3.cpp enc3.h tablecheck.h enc.h dec.h
	$(CC) $(CFLAGS) -c enc3.cpp

dec3.o : dec3.cpp dec3.h tablecheck.h enc.h dec.h
	$(CC) $(CFLAGS) -c dec3.cpp


clean:
	rm -f *.o hw4

