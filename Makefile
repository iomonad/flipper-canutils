CC = ufbt

all:
	$(CC) build
install:
	$(CC) launch
toolchain:
	python3 -m pip install --upgrade ufbt
	ufbt-bootstrap update
debug:
	$(CC) blackmagic BLACKMAGIC=
clean:
	$(CC) -c

re: clean all
