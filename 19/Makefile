CC := clang
CFLAGS := -Wall -Wextra

all: tlb.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out