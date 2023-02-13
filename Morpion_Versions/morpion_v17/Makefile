make:
	@clear
	@gcc -Wall -Wextra -pedantic -std=c99 -o Morpion *.c -ISDL2\x86_64-w64-mingw32\include\SDL2 -lm -lSDL2main -lSDL2 -lSDL2main -lSDL2
run: make
	@./Morpion
@val:
	@clear
	@gcc -Wall -Wextra -pedantic -std=c99 -o Morpion *.c -g 
	@valgrind --leak-check=full -s --track-origins=yes ./Morpion
clean:
	@rm Morpion
