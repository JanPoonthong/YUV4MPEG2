all:
	$(CC) -Wall -Wextra -o run main.c
	./run
	mplayer output.y4m
