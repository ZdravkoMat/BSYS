CC := gcc
OSFLAG := -D $(shell uname -s)
CFLAGS := -Wall -Wextra -Wpedantic -pthread

all: sloppy_counter.out simple_counter.out hand_over_hand.out

sloppy_counter.out: sloppy_counter.c
	$(CC) -o $@ $^ $(CFLAGS) -lm $(OSFLAG)

simple_counter.out: simple_counter.c thread_helper.h
	$(CC) -o $@ $< $(CFLAGS) $(OSFLAG)

hand_over_hand.out: hand-over-hand.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f ./*.out