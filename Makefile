CC=gcc
CFLAGS=-Wall -Wextra -std=c99 
TARGETS=image_editor
build:
	$(CC) $(CFLAGS) -o image_editor main.c -lm
clean:
	rm -f $(TARGETS)