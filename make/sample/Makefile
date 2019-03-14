test:main.o add.o sub.o mul.o div.o mod.o sum.o
	gcc main.o add.o sub.o mul.o div.o mod.o sum.o -o test
main.o:main.c make.h
	gcc -c main.c
add.o:add.c make.h
	gcc -c add.c
sub.o:sub.c make.h
	gcc -c sub.c
mul.o:mul.c make.h
	gcc -c mul.c
div.o:div.c make.h
	gcc -c div.c
mod.o:mod.c make.h
	gcc -c mod.c
