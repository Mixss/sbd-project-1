#ifndef DISK_READER_H
#define DISK_READER_H
#include <stdio.h>
#include "record.h"

#define BLOCK_SIZE sizeof(struct block)
#define RECORDS_IN_BLOCK 4

struct block 
{
    struct record data[RECORDS_IN_BLOCK];
} __attribute__((__packed__)); 

//returns 0 if file was opened correctly
int load_disk(FILE** file, const char* filename);
void remove_disk(FILE** file);
/*loads block from disk at given position, returns 0 if successfull*/
int load_block(FILE** disk, int pos, struct block* data);
/*saves block from disk at given position, returns 0 if successfull*/
int save_block(FILE** disk, int pos, struct block* data);

void print_disk(FILE** disk);
void print_block(struct block* b);
/*writes record to specified file*/
int save_records_to_disk(FILE** file, struct record* records, int count);
/*returns how much records have been loaded. Doesn't allocates records!*/
int load_records_from_disk(FILE** disk, struct record *records);

#endif