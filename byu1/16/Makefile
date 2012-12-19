main: clean
	cc -Wall -c -fPIC rev.c
	mkdir lib
	cc -shared -Wl,-soname,librev.so.1 -o ./lib/librev.so.1.0 rev.o
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./lib
	ln -s librev.so.1.0 ./lib/librev.so.1
	ln -s librev.so.1.0 ./lib/librev.so
	cc -Wall main.c -o main -L./lib -lrev -ldl
clean:
	rm -rf lib rev.o main
