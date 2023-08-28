# makefile bem cachorro só pra testar mesmo
all:
	gcc -o main Source/libs/src/*.c Source/*.c -Wall

dev:
	gcc -o main Source/libs/src/*.c Source/*.c -Wall -g -D _DEV_

test_int:
	gcc -o main Source/libs/src/*.c Source/*.c Tests/IntUnionFind/*.c -g -D _DEV_
	
test_generic:
	gcc -o main Source/libs/src/*.c Source/*.c Tests/GenericUnionFind/*.c -g -D _DEV_