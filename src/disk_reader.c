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
            printf("%d: id=%d -> g(x)=%d\t(a0=%d, a1=%d, a2=%d, a3=%d, a4=%d, x=%d)\n", pos * RECORDS_IN_BLOCK + i, loaded_record.id, get_record_sorting_value(loaded_record),  loaded_record.a[0], loaded_record.a[1], loaded_record.a[2], loaded_record.a[3], loaded_record.a[4], loaded_record.x);
        }
        pos++;
    }
}