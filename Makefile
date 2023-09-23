all:
	@gcc -o trab1 Source/libs/src/*.c Source/*.c -lm
	@echo 'Compilado!'
