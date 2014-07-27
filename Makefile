# compile with mingw
all: mixunprotect.c
	gcc -Wall -O2 -c -g mixunprotect.c -o mixunprotect.o
	gcc -static -static-libgcc -o mixunprotect.exe mixunprotect.o

clean:
	rm mixunprotect.o
