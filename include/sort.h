#ifndef SORT_H
#define SORT_H
#include "disk_reader.h"

/*Sorts file using natural merge with 2+1 scheme*/
int sort_natural_merge(FILE** file);
void distribute(FILE** t3, FILE* tape[], struct block tape_block[], int tape_counter[]);
/*When input tape has ended, then we need to save blocks with partially filled records*/
void fill_blocks(FILE* tape[], struct block t_block[], int t_counter[]);

#endif