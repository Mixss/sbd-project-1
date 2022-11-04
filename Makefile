ODIR=./build
IDIR=./include
EXEC=program

_OBJ = program.o disk_reader.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
FLAGS = -Wall -I$(IDIR)

_DEPS = disk_reader.h 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: src/%.c $(DEPS)
	gcc -c $< -o $@  $(FLAGS)

all: $(OBJ)
	gcc $(OBJ) -o $(EXEC) $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*
	rm $(EXEC)

