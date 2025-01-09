c-sweeper: main.o $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))
	gcc -Wall -Wextra -O2 -o c-sweeper main.o $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))

main.o: main.c
	gcc -Wall -Wextra -O2 -c main.c -o main.o

src/%.o: src/%.c
	gcc -Wall -Wextra -O2 -c $< -o $@

clean:
	rm -f src/*.o main.o c-sweeper
