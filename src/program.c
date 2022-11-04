/*
Temat:
44. Rekordy pliku: parametry a0,a1,a2,a3,a4,x.
Uporządkowanie wg wartości funkcji g(x)=a0+a1x +a2x2+a3x3+a4x4
*/

#include <stdio.h>
#include "disk_reader.h"

int main(){
    
    const char* diskname = "./data/disk.bin";
    FILE* disk;
    load_disk(&disk, diskname);

    printf("dupa");

    remove_disk(&disk);
    return 0;
}