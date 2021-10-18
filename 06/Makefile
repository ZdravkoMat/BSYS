CC := clang
CFLAGS := -std=gnu11 -Wall -Wextra -Wpedantic

all: 6_1.out 6.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out
	rm -f ./*.txt