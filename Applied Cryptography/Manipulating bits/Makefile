CC = g++
CFLAGS = -Wall -g

all : hw1

hw1 : hw1.o tohexdump.o encbase64.o decbase64.o
	$(CC) $(CFLAGS) hw1.o tohexdump.o encbase64.o decbase64.o -o hw1

hw1.o : hw1.cpp tohexdump.h encbase64.h decbase64.h
	$(CC) $(CFLAGS) -c hw1.cpp

tohexdump.o : tohexdump.cpp tohexdump.h
	$(CC) $(CFLAGS) -c tohexdump.cpp

encbase64.o : encbase64.cpp encbase64.h
	$(CC) $(CFLAGS) -c encbase64.cpp

decbase64.o : decbase64.cpp decbase64.h
	$(CC) $(CFLAGS) -c decbase64.cpp



clean:
	rm -f *.o hw1

