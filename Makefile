

dummy: dummy_shell.c
	$(CC) -O2 -g dummy_shell.c -o dummy
	strip dummy

install: 
	cp dummy_shell /usr/bin/dummy

clean:
	rm -f dummy

uninstall:
	rm -f /usr/bin/dummy
