ODIR=./build
IDIR=./include
EXEC=program

_OBJ = program.o disk_reader.o disk_generator.o record.o sort.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
FLAGS = -Wall -I$(IDIR) -g

_DEPS = disk_reader.h disk_generator.h record.h sort.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

$(ODIR)/%.o: src/%.c $(DEPS)
	gcc -c $< -o $@  $(FLAGS)

all: $(OBJ)
	gcc $(OBJ) -o $(EXEC) $(FLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR)/*
	rm $(EXEC)

