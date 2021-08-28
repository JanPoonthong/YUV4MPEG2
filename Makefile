all:
	$(CC) -Wall -Wextra -o run main.c -lm
	./run
	vlc output.y4m
