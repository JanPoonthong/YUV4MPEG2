all:
	$(CC) -Wall -Wextra -o run main.c
	./run
	vlc output.y4m
