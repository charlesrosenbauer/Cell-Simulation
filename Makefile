fast:
	clang -lSDL -O3 src/*.c -o bin/cellsim

test:
	clang -lSDL -O0 src/*.c -o bin/cellsim
