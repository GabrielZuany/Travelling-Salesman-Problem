# makefile bem cachorro só pra testar mesmo
all:
	gcc -o main Source/libs/src/*.c Source/*.c -Wall -lm

dev:
	gcc -o main Source/libs/src/*.c Source/*.c -Wall -g -D _DEV_ -lm

test_int:
	gcc -o main Source/libs/src/*.c Tests/IntUnionFind/*.c -g -D _DEV_ -lm
	
test_generic:
	gcc -o main Source/libs/src/*.c Tests/GenericUnionFind/*.c -g -D _DEV_ -lm