CC=clang -g -fno-stack-protector
CFLAGS = -W -Wall -std=$(STD) -pedantic -pthread
CPPCHECK = cppcheck --enable=all --std=$(STD)
STD=c11

.PHONY: all clean cppcheck

all: $(TARGET)

clean:
	$(RM) $(TARGET) $(TARGET).o

cppcheck: $(TARGET).c
	$(CPPCHECK) $<