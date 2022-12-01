/*
Temat:
44. Rekordy pliku: parametry a0,a1,a2,a3,a4,x.
Uporządkowanie wg wartości funkcji g(x)=a0+a1x +a2x2+a3x3+a4x4
*/

#include <stdio.h>
#include "disk_reader.h"
#include "disk_generator.h"
#include "sort.h"
#include <string.h>
#include "data_input.h"
#include <stdlib.h>
#include "record_shell.h"
#include "stats.h"

#define DEFAULT_DISK "./data/disk.bin"

enum Disk_type
{
    random_generated = 0,
    text = 1,
    input = 2,
    own_location = 3
};

int main(int argc, char* argv[])
{
    enum Disk_type disktype = random_generated;
    int random_number_of_blocks = 2;
    const char* diskname;
    bool print_phases = false;
    
    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
        {
            if(argc <= i + 1)
            {
                printf("File not specified.\n");
                return 1;
            }
            // TODO remove temp file!
            if(load_from_text_file(argv[i+1]) != 0)
            {
                return 1;
            }
            printf("Loaded disk data from the text file: %s\n", argv[i+1]);
            disktype = text;
        }
        else if(strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--keyboard") == 0)
        {
            load_from_user_input();
            disktype = input;
        }
        else if(strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--random") == 0)
        {
            if(argc <= i + 1)
            {
                printf("Number of blocks not specified.\n");
                return 1;
            }
            random_number_of_blocks = atoi(argv[i+1]);
            disktype = random_generated;
        }
        else if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--print-phases") == 0)
        {
            print_phases = true;
        }
        else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printf("Options:\n-r\t--random <number>\t\tspecify number of blocks to be generated in random disk (./data/disk.bin). -r is default option with 2 blocks to generate\n-k\t--keyboard\t\ttype in input data\n-f\t--file <filename>\ttake input data from text file. One record per line with format: 'id x a0 a1 a2 a3 a4' separated with space\n-p\t--print-phases\t\tprint sorted file after each sorting phase\n\n");
            return 0;
        }
    }

    if(disktype == random_generated)
    {
        generate_disk_random(DEFAULT_DISK, random_number_of_blocks, 20);
        diskname = DEFAULT_DISK;
    }
    else if(disktype == text || disktype == input)
    {
        diskname = TEMP_DISK;
    }

    FILE* disk;
    load_disk(&disk, diskname);
    print_disk(&disk);
    remove_disk(&disk);

    set_disk_reads(0);
    set_disk_writes(0);
    
    sort_natural_merge(diskname, print_phases);

    if(disktype == text || disktype == input){
        diskname = TEMP_DISK;
    }

    load_disk(&disk, diskname);
    printf("\nSORTED: \n\n");
    print_disk(&disk);
    remove_disk(&disk);

    // if(disktype == text || disktype == input){
    //     remove(TEMP_DISK);
    // }

    return 0;
}