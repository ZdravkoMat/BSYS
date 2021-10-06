CC := clang
CFLAGS := -Wall

all: 6.out measure.out

%.out: %.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f ./*.out