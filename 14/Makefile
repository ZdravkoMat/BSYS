CC := clang
CFLAGS := -std=gnu11 -Wall -Wextra -Wpedantic

all: null.out 4.out 5.out 6.out 7.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS) -g

clean:
	rm -f ./*.out