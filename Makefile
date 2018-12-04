CFLAGS += -Wall -Wextra

LDFLAGS += -nostdlib -ffreestanding 
LDFLAGS += -static

all: guess

guess: guess.o syscall.o

clean:
	rm -f guess guess.o syscall.o
