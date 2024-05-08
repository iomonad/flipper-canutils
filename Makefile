CC = ufbt

all:
	$(CC) build
install:
	$(CC) launch
boostrap:
	ufbt-bootstrap update
debug:
	$(CC) blackmagic BLACKMAGIC=
clean:
	$(CC) -c
re: clean all
