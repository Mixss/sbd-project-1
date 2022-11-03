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
        printf("Error reading disk!\n");
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