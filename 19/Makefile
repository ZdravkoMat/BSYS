CC := clang
CFLAGS := -std=gnu11 -Wall -Wextra -Wpedantic

all: tlb.out

%.out: %.c
	$(CC) -O0 -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out