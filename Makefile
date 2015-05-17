CC=gcc
ICSOS_ROOT=../..
SDK=../../sdk
CFLAGS=-nostdlib -fno-builtin -static
LIBS=$(SDK)/tccsdk.c $(SDK)/libtcc1.c $(SDK)/crt1.c 
EXE=mnswpr.exe

$(EXE): mnswpr.c
	$(CC) $(CFLAGS) -o${EXE} mnswpr.c $(LIBS)

install: $(EXE)
	cp $(EXE) $(ICSOS_ROOT)/apps

uninstall:
	rm $(ICSOS_ROOT)/apps/$(EXE)

clean:
	rm $(EXE)


