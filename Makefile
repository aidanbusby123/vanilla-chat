IDIR=include/
CC=gcc
LIBS=-pthread
SRC=src/main.c
BIN=bin

GNUBLD=GNU_x86_64_0-0-1.out
WINBLD=WIN_x86_64_0-0-1.exe
MACBLD=MAC_x86_64_0-0-1.app

GNUFLG=-D GNU=1
WINFLG=-D WIN=1
MACFLG=-D MAC=1

all:
	$(CC) $(GNUFLG) $(SRC) -o $(BIN)/$(GNUBLD) $(LIBS)
gnu:
	$(CC) $(GNUFLG) $(SRC) -o $(BIN)/$(GNUBLD) $(LIBS)
win:
#	$(CC) $(WINFLG) -o bin/$(WINBLD)  src/main.c
mac:
#	$(CC) $(MACFLG) -o bin/$(MACBLD)  src/main.c