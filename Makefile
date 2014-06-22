

gcc: dummy_shell.c
	gcc -O2 -g dummy_shell.c -o dummy
	strip dummy

clang: dummy_shell.c
	clang -O2 -g dummy_shell.c -o dummy
	strip dummy

install: 
	cp dummy_shell /usr/bin/dummy

clean:
	rm -f dummy

uninstall:
	rm -f /usr/bin/dummy
