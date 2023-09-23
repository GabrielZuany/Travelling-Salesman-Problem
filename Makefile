all:
	@gcc -o trab1 Source/libs/src/*.c Source/*.c -Wall -lm
	@echo 'Compilado!'

profiler:
	@gcc -o trab1 Source/libs/src/*.c Source/*.c -Wall -lm -pg
	@./trab1
	@gprof trab1 gmon.out > Profiler/gprof.txt
	@rm gmon.out
	@echo 'Profiler gerado com sucesso!'
