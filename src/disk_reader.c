#include "disk_reader.h"

int load_disk(FILE** file, const char* filename)
{
    *file = fopen(filename, "rb+");
    if(*file == NULL)
    {
        printf("Failed to open the file!\n");
        return 1;
    }
    return 0;
}

void remove_disk(FILE** file)
{
    fclose(*file);
}

int load_block(FILE** disk, int pos, struct block* data)
{
    fseek(*disk, BLOCK_SIZE * pos, 0);
    if(fread(data, sizeof(struct block), 1, *disk) < 1)
    {
        //printf("Error reading disk!\n");
        return 1;
    }
    return 0;
}

int save_block(FILE** disk, int pos, struct block* data)
{
    fseek(*disk, BLOCK_SIZE * pos, 0);
    int err = 0;
    if((err = fwrite(data, BLOCK_SIZE, 1, *disk)) < 1)
    {
        printf("Error writing to the disk! (%d)\n", err);
        return 1;
    }
    return 0;
}

int save_block_at_end(FILE** disk, struct block* data)
{
    printf("Zapisuję: ");
    print_record(&((*data).data[0]));
    if(fwrite(data, BLOCK_SIZE, 1, *disk) < 1)
    {
        printf("Error writing to the disk!\n");
        return 1;
    }
    return 0;
}


void print_disk(FILE** disk)
{
    struct block loaded_block;
    struct record loaded_record;
    int pos = 0;

    printf("Disk contents:\n");

    while(load_block(disk, pos, &loaded_block) == 0)
    {
        printf("block: %d\n", pos);
        for(int i=0; i<RECORDS_IN_BLOCK; i++){
            loaded_record = loaded_block.data[i];
            printf("%d: ", pos * RECORDS_IN_BLOCK + i);
            print_record(&loaded_record);
        }
        pos++;
    }
}

void print_block(struct block* b)
{
    printf("Block:\n");
    for(int i=0; i<RECORDS_IN_BLOCK; i++)
    {
        print_record(&b->data[i]);
    }
}

int save_records_to_disk(FILE** disk, struct record records[], int count)
{
    int i = 0;
    struct block block_to_write;

    while(i < count)
    {
        block_to_write.data[i % RECORDS_IN_BLOCK] = records[i];
        i++;
        // check if block is full
        if(i % RECORDS_IN_BLOCK == 0)
        {
            save_block(disk, i / RECORDS_IN_BLOCK - 1, &block_to_write);
        }
    }
    // fill rest of block with empty records
    if(i % RECORDS_IN_BLOCK != 0)
    {
        struct record rec_zero;
        zero_record(&rec_zero);

        while(i % RECORDS_IN_BLOCK != 0)
        {
            block_to_write.data[i % RECORDS_IN_BLOCK] = rec_zero;
            i++;
        }
        printf("i=%d\n", i);
        save_block(disk, i / RECORDS_IN_BLOCK - 1, &block_to_write);
        // we have to add any block at the end of the file
        save_block(disk, i / RECORDS_IN_BLOCK - 1, &block_to_write);
    }

    return 0;
}

int load_records_from_disk(FILE** disk, struct record *records)
{
    struct block loaded_block;
    int pos = 0;
    int count = 0;

    while(load_block(disk, pos, &loaded_block) == 0)
    {
        for(int i=0; i<RECORDS_IN_BLOCK; i++){
            records[count] = loaded_block.data[i];
            count++;
        }
        pos++;
    }
    return count;
}