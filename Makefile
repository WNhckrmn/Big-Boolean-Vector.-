all:build

build: tests.c bigbool.obj
	gcc bigbool.obj tests.c

bigbool.obj: bigbool.c
	gcc -o bigbool.obj bigbool.c
clean:
	rm -f a.exe
	rm -f bigbool.obj