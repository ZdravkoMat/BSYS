CC := clang
CFLAGS := -Wall -Werror

all: memory-user.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out