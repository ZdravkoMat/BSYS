CC := clang
CFLAGS := -Wall -Wextra -Wpedantic

all: 6_1.out 6_2.out 6_2_2.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out