CC := clang
CFLAGS := -Wall

all: measurements.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out