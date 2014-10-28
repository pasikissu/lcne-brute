CC=gcc
CFLAGS=-Wall -flto -O2
CLIBS=-ldl
SRC=main.c
OBJ=$(SRC:.c=.o)
EXE=brute
MODSRC=test.c
MODSO=$(MODSRC:.c=.so)
MODFLAGS=-Wall -O2 -fPIC -shared

all: MODS $(SRC) $(EXE)
	strip $(EXE)

debug: CFLAGS=-Wall -g
debug: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(CLIBS) $(OBJ) -o $@

MODS: $(MODSRC) $(MODSO)

%.so: %.c
	$(CC) $(MODFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm *.o *.so $(EXE)
