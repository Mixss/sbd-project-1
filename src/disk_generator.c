#include "disk_generator.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void generate_disk_random(const char* filename, int number_of_blocks, int max_value)
{
    srand(time(NULL));
    
    FILE* disk = fopen(filename, "wb+");
    struct record new_record;
    struct block new_block;

    for(int i=0; i<number_of_blocks; i++)
    {
        for(int j=0; j<RECORDS_IN_BLOCK; j++)
        {
            new_record.id = i * RECORDS_IN_BLOCK + j;
            generate_random_record(&new_record, max_value);
            new_block.data[j] = new_record;
        }
        save_block(&disk, i, &new_block);
    }
    // save random block at the end of the file 
    //save_block(&disk, number_of_blocks, &new_block);
    fclose(disk);
}

void generate_random_record(struct record* rec, int max_value)
{
    (*rec).a[0] = (rand() % (2 * max_value)) - max_value;
    (*rec).a[1] = (rand() % (2 * max_value)) - max_value;
    (*rec).a[2] = (rand() % (2 * max_value)) - max_value;
    (*rec).a[3] = (rand() % (2 * max_value)) - max_value;
    (*rec).a[4] = (rand() % (2 * max_value)) - max_value;
    (*rec).x = (rand() % (2 * max_value)) - max_value;
}