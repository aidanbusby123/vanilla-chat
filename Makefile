CC=gcc
LIBS=-pthread
SRC=src/main.c include/server.c include/client.c
BIN=bin

DEBFLGS=-g -Wall
FLGS=-O2

GNUBLD=vanillaChat_GNU_x86_64.out
WINBLD=vanillaChat_WIN_x86_64.exe
MACBLD=vanillaChat_MAC_x86_64.app

GNUFLG=-D GNU=1
WINFLG=-D WIN=1
MACFLG=-D MAC=1

DEB=-D DEBON

all:
	$(CC) $(GNUFLG) $(FLGS) $(SRC) -o $(BIN)/$(GNUBLD) $(LIBS)
	$(CC) $(WINFLG) $(FLGS) $(SRC) -o $(BIN)/$(WINBLD) $(LIBS)
	$(CC) $(MACFLG) $(FLGS) $(SRC) -o $(BIN)/$(MACBLD) $(LIBS)
gnu:
	$(CC) $(GNUFLG) $(FLGS) $(SRC) -o $(BIN)/$(GNUBLD) $(LIBS)
win:
	$(CC) $(WINFLG) $(FLGS) $(SRC) -o $(BIN)/$(WINBLD) $(LIBS)
mac:
	$(CC) $(MACFLG) $(FLGS) $(SRC) -o $(BIN)/$(MACBLD) $(LIBS)

allDeb:
	$(CC) $(GNUFLG) $(DEB) $(DEBFLGS) $(SRC) -o $(BIN)/$(GNUBLD) $(LIBS)
	$(CC) $(WINFLG) $(DEB) $(DEBFLGS) $(SRC) -o $(BIN)/$(WINBLD) $(LIBS)
	$(CC) $(MACFLG) $(DEB) $(DEBFLGS) $(SRC) -o $(BIN)/$(MACBLD) $(LIBS)
gnuDeb:
	$(CC) $(GNUFLG) $(DEB) $(DEBFLGS) $(SRC) -o $(BIN)/$(GNUBLD) $(LIBS)
winDeb:
	$(CC) $(WINFLG) $(DEB) $(DEBFLGS) $(SRC) -o $(BIN)/$(WINBLD) $(LIBS)
macDeb:
	$(CC) $(MACFLG) $(DEB) $(DEBFLGS) $(SRC) -o $(BIN)/$(MACBLD) $(LIBS)