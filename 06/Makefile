CC := clang
CFLAGS := -Wall -Wextra -Wpedantic

all: 6.out measure.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out