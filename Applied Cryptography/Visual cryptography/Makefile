CC = g++
CFLAGS = -Wall -g

all : hw2

hw2 : hw2.o stream.o encrypt.o merge.o decrypt.o
	$(CC) $(CFLAGS) hw2.o stream.o encrypt.o merge.o decrypt.o -I/home/scf-22/csci551b/openssl/include -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm -o hw2

hw2.o : hw2.cpp stream.h encrypt.h merge.h decrypt.h
	$(CC) $(CFLAGS) -c hw2.cpp -I/home/scf-22/csci551b/openssl/include

stream.o : stream.cpp stream.h
	$(CC) $(CFLAGS) -c stream.cpp -I/home/scf-22/csci551b/openssl/include

encrypt.o : encrypt.cpp encrypt.h
	$(CC) $(CFLAGS) -c encrypt.cpp -I/home/scf-22/csci551b/openssl/include

merge.o : merge.cpp merge.h
	$(CC) $(CFLAGS) -c merge.cpp -I/home/scf-22/csci551b/openssl/include

decrypt.o : decrypt.cpp decrypt.h
	$(CC) $(CFLAGS) -c decrypt.cpp -I/home/scf-22/csci551b/openssl/include



clean:
	rm -f *.o hw2

