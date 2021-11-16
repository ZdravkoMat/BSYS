CC := clang
CFLAGS := -std=gnu11 -Wall -Wextra -Wpedantic -pthread

all: tlb.out

%.out: %.c
	$(CC) -O0 -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out