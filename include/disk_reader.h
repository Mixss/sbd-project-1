#ifndef DISK_READER_H
#define DISK_READER_H
#include <stdio.h>

#define BLOCK_SIZE sizeof(struct block)

struct record 
{
    int id;
    long data;
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