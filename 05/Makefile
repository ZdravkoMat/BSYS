CC := clang
CFLAGS := -Wall

all: fork.out fork-open.out fork-wait.out fork-exec.out fork-wait-return.out \
	fork-waitpid.out fork-stdout.out fork-pipe.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out