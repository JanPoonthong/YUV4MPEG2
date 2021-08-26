all:
	$(CC) -o run main.c
	./run
	mplayer output.y4m
