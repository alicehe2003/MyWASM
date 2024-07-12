IDIR =../include
CC=clang++
CFLAGS=-I$(IDIR) -I$(BOOST_INCLUDE_DIR) -std=c++20
LDFLAGS = -L$(BOOST_LIB_DIR) $(BOOST_LIBS)

ODIR=../obj
LDIR =../lib

# Specify the Boost include directory (update this path to your Boost include path)
BOOST_INCLUDE_DIR = /opt/homebrew/opt/boost/include

# Specify the Boost library directory (update this path to your Boost library path)
BOOST_LIB_DIR = /opt/homebrew/opt/boost/lib

# Specify the Boost libraries you need (update these as needed)
BOOST_LIBS = 

_DEPS = Parser.hpp CmdLineRepl.hpp Interpreter.hpp State.hpp ArithInstr.hpp ConstInstr.hpp LoadInstr.hpp SizeInstr.hpp StoreInstr.hpp	# header files (separated by space)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o Parser.o CmdLineRepl.o Interpreter.o State.o ArithInstr.o ConstInstr.o LoadInstr.o SizeInstr.o StoreInstr.o				# .o files 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 



