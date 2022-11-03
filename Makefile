FILES = ./build/program.o ./build/disk_reader.o
INCLUDES = -I.*
FLAGS = -Wall

all: $(FILES)
	gcc $(FILES) -o program

./build/disk_reader.o: ./src/disk_reader.c
	gcc $(INCLUDES) $(FLAGS) -c ./src/disk_reader.c -o ./build/disk_reader.o

./build/program.o: ./src/program.c 
	gcc $(INCLUDES) $(FLAGS) -c ./src/program.c -o ./build/program.o

clean:
	rm -rf ./build/*
	rm ./program

