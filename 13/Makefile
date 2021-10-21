CC := clang
CFLAGS := -std=gnu11 -Wall -Wextra -Wpedantic

all: memory-user.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out