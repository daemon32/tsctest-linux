all: tsctest

tsctest: main.o cpu.o
	gcc -g -o tsctest main.o cpu.o

cpu.o:
	gcc -std=c99 -g -c -o cpu.o cpu.c

main.o:
	gcc -std=c99 -g -c -o main.o main.c

clean:
	rm -vf *.o tsctest
