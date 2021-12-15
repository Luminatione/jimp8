all:
	gcc -Wall --pedantic src/*.c -o bin/gauss

test:
	gcc -Wall --pedantic -DRUN_TESTS src/*.c -o bin/gauss
