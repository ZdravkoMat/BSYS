CC := clang
CFLAGS := -std=gnu11 -Wall -Wextra -Wpedantic

all: null.out 4.out 5.out 6.out 7.out 8.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out