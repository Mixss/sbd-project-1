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

int main(int argc, char* argv[])
{
    for(int i=1; i<argc; i++)
    {
        if(strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0)
        {
            if(argc <= i + 1)
            {
                printf("File not specified.\n");
                return 1;
            }
            // creates mock disk file, at the end of program removes it from
            // user's disk
            printf("Dysk jako plik tekstowy\n");
        }
        else if(strcmp(argv[i], "-k") == 0 || strcmp(argv[i], "--keyboard") == 0)
        {
            printf("Dysk z klawiatury");
        }
        else if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--disk") == 0)
        {
            if(argc <= i + 1)
            {
                printf("File not specified.\n");
                return 1;
            }
            printf("Inna scieżka do dysku\n");
        }
        else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
        {
            printf("Options:\n-k\t--keyboard\t\ttype in input data\n-f\t--file <filename>\ttake input data from text file. One record per line with format: 'id x a0 a1 a2 a3 a4' separated with space\n-d\t--disk <filename>\tspecify own disk file location\n\n");
        }

    }

    load_from_text_file("./data/data.txt");


    generate_disk_random("./data/disk.bin", 2, 100);
    
    // const char* diskname = "./data/disk.bin";
    const char* diskname = "./data/temp";
    FILE* disk;
    load_disk(&disk, diskname);
    print_disk(&disk);
    sort_natural_merge(&disk);

    remove_disk(&disk);

    load_disk(&disk, "./data/t1");
    printf("\nTAPE 1: \n\n");
    print_disk(&disk);
    remove_disk(&disk);

    load_disk(&disk, "./data/t2");
    printf("\nTAPE 2: \n\n");
    print_disk(&disk);
    remove_disk(&disk);
    return 0;
}