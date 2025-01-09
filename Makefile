c-sweeper: src/main.o $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))
	gcc -Wall -Wextra -O2 -o c-sweeper src/main.o $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))

src/main.o: src/main.c
	gcc -Wall -Wextra -O2 -c src/main.c -o src/main.o

src/%.o: src/%.c
	gcc -Wall -Wextra -O2 -c $< -o $@

clean:
	rm -f src/*.o c-sweeper