all:
	gcc -I src/include -L src/lib -o main test.c -lmingw32 -lSDL2main -lSDL2