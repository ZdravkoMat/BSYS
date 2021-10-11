CC := clang
CFLAGS := -Wall -Wextra -Wpedantic

all: context.out system.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out