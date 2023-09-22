#  time ./main Others/exemplos/exemplos/in/berlin52.tsp 
all:
	@gcc -o trab1 Source/libs/src/*.c Source/*.c -Wall -lm
	@echo 'Compilado!'

profiler:
	@gcc -o trab1 Source/libs/src/*.c Source/*.c -Wall -lm -pg
	@./trab1
	@gprof trab1 gmon.out > Profiler/gprof.txt
	@rm gmon.out
	@echo 'Profiler gerado com sucesso!'

dev:
	@gcc -o trab1 Source/libs/src/*.c Source/*.c -Wall -g -D _DEV_ -lm
	@echo 'Compilado!'

read_test:
	@gcc -o trab1 Source/libs/src/*.c Tests/Read/*.c -g -D _DEV_ -lm
	@echo 'Compilado!'