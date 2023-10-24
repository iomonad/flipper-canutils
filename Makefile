CC = ufbt

all:
	$(CC) build
install:
	$(CC) launch
debug:
	$(CC) blackmagic BLACKMAGIC=
clean:
	$(CC) -c
