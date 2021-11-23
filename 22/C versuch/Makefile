CC := clang
CFLAGS := -std=gnu11 -Wall

all: convert.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out