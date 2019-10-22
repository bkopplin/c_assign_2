CC=gcc
CFLAGS=-Wall -Werror -Wpedantic -g
HEADERS=playlist.h

all: playlist.o playlist_tester.o
	$(CC) $(CFLAGS) playlist_tester.o playlist.o -o a

playlist.o: playlist.c $(HEADERS)
	$(CC) $(CFLAGS) -c playlist.c -o playlist.o

playlist_tester.o: playlist_tester.c $(HEADERS)
	$(CC) $(CFLAGS) -c playlist_tester.c -o playlist_tester.o
