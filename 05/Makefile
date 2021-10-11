CC := clang
CFLAGS := -Wall -Wextra -Wpedantic

all: fork_1.out fork_2.out fork_3.out fork_4.out fork_5.out \
	fork_6.out fork_7.out fork_8.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out