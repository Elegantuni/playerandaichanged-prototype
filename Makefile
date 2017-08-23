playerandai1:
	$(CC) -std=c99 -o playerandai1 main.c `pkg-config --cflags --libs ncurses`
	
clean:
	rm -f playerandai1

