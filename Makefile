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

uf_test_int:
	@gcc -o main Source/libs/src/*.c Tests/IntUnionFind/*.c -g -D _DEV_ -lm
	@echo 'Compilado!'
	
uf_test_generic:
	@gcc -o main Source/libs/src/*.c Tests/GenericUnionFind/*.c -g -D _DEV_ -lm
	@echo 'Compilado!'

uf_test_profiler_int:
	@gcc -o main Source/libs/src/*.c Tests/IntUnionFind/*.c -g -D _DEV_ -lm -pg
	@echo 'Compilado!'
	@./main
	@gprof main gmon.out > Profiler/gprof.txt
	@rm gmon.out

uf_test_profiler_generic:
	@gcc -o main Source/libs/src/*.c Tests/GenericUnionFind/*.c -g -D _DEV_ -lm -pg
	@echo 'Compilado!'
	@./main
	@gprof main gmon.out > Profiler/gprof.txt
	@rm gmon.out

full_graph_test_profile:
	@gcc -o main Source/libs/src/*.c Tests/Dumb_BuildGraphConnections/build_graph_connections.c -g -D _DEV_ -lm -pg
	@echo 'Compilado!'
	@./main
	@gprof main gmon.out > Profiler/gprof.txt
	@rm gmon.out

tree_graph_test_profile:
	@gcc -o main Source/libs/src/*.c Tests/Dumb_BuildGraphConnections/build_graph_tree.c -g -D _DEV_ -lm -pg
	@echo 'Compilado!'
	@./main
	@gprof main gmon.out > Profiler/gprof.txt
	@rm gmon.out

read_test:
	@gcc -o main Source/libs/src/*.c Tests/Read/*.c -g -D _DEV_ -lm
	@echo 'Compilado!'