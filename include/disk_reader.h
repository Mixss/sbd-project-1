#ifndef DISK_READER_H
#define DISK_READER_H
#include <stdio.h>

#define BLOCK_SIZE sizeof(struct block)

/*44. File records: parameters a0,a1,a2,a3,a4,x.
Sorting by the value of the function g(x)=a0+a1x +a2x2+a3x3+a4x4*/
struct record 
{
    int id;
    int a[5];
    int x;
} __attribute__((packed)); 

struct block 
{
    struct record data[4];
} __attribute__((packed)); 

//returns 0 if file was opened correctly
int load_disk(FILE** file, const char* filename);
void remove_disk(FILE** file);
int load_block(FILE** disk, int pos, struct block* data);
int save_block(FILE** disk, int pos, struct block* data);


#endif