/*
Temat:
44. Rekordy pliku: parametry a0,a1,a2,a3,a4,x.
Uporządkowanie wg wartości funkcji g(x)=a0+a1x +a2x2+a3x3+a4x4
*/

#include <stdio.h>
#include "disk_reader.h"
#include "disk_generator.h"

int main(){
    
    generate_disk_random("./data/disk.bin", 32, 1000);
    
    const char* diskname = "./data/disk.bin";
    FILE* disk;
    load_disk(&disk, diskname);

    print_disk(&disk);

    remove_disk(&disk);
    return 0;
}