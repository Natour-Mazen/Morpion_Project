make:
	@clear
	@gcc -Wall -Wextra -pedantic -std=c99 -o Morpion *.c -lm
run: make
	@./Morpion
val:
	@clear
	@gcc -Wall -Wextra -pedantic -std=c99 -o Morpion *.c -g -lm
	@valgrind --leak-check=full -s --track-origins=yes ./Morpion
clean:
	@rm Morpion
