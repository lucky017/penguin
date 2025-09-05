
compile:
	make Lib/.
	gcc Main.c Lib/*.o src/*.c -Wall -o penguin
run:
	./penguin
