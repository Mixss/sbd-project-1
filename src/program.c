/*
Temat:
44. Rekordy pliku: parametry a0,a1,a2,a3,a4,x.
Uporządkowanie wg wartości funkcji g(x)=a0+a1x +a2x2+a3x3+a4x4
*/

#include <stdio.h>
#include "disk_reader.h"
#include "disk_generator.h"
#include "sort.h"

int main(){
    
    generate_disk_random("./data/disk.bin", 2, 100);
    
    const char* diskname = "./data/disk.bin";
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