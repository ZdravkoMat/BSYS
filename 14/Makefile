CC := clang
CFLAGS := -Wall -Werror

all: null.out malloc.out malloc-data.out malloc-print.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out