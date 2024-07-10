IDIR =../include
CC=clang++
CFLAGS=-I$(IDIR) 

ODIR=../obj
LDIR =../lib

LIBS=

_DEPS = Parser.hpp CmdLineRepl.hpp									# header files (separated by space)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Parser.o CmdLineRepl.o								# .o files 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 



