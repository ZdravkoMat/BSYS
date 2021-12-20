CC := clang
CFLAGS := -Wall -Wextra -pthread


all: simple.out sloopy.out hand.out

simple.out: simple.c
	$(CC) -o $@ $< $(CFLAGS)

sloppy.out: sloppy.c
	$(CC) -o $@ $< $(CFLAGS)

hand.out: hand.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out