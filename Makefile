# makefile bem cachorro só pra testar mesmo
all:
	@gcc -o main Source/libs/src/*.c Source/*.c -Wall -lm
	@echo 'Compilado!'

profiler:
	@gcc -o main Source/libs/src/*.c Source/*.c -Wall -lm -pg
	@./main
	@gprof main gmon.out > Profiler/gprof.txt
	@rm gmon.out
	@echo 'Profiler gerado com sucesso!'

dev:
	@gcc -o main Source/libs/src/*.c Source/*.c -Wall -g -D _DEV_ -lm
	@echo 'Compilado!'

test_int:
	@gcc -o main Source/libs/src/*.c Tests/IntUnionFind/*.c -g -D _DEV_ -lm
	@echo 'Compilado!'
	
test_generic:
	@gcc -o main Source/libs/src/*.c Tests/GenericUnionFind/*.c -g -D _DEV_ -lm
	@echo 'Compilado!'

test_profiler_int:
	@gcc -o main Source/libs/src/*.c Tests/IntUnionFind/*.c -g -D _DEV_ -lm -pg
	@echo 'Compilado!'
	@./main
	@gprof main gmon.out > Profiler/gprof.txt
	@rm gmon.out

test_profiler_generic:
	@gcc -o main Source/libs/src/*.c Tests/GenericUnionFind/*.c -g -D _DEV_ -lm -pg
	@echo 'Compilado!'
	@./main
	@gprof main gmon.out > Profiler/gprof.txt
	@rm gmon.out