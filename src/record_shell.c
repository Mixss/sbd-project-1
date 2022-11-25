#include "record_shell.h"
#include <memory.h>

void reader_init(FILE** file, struct record_shell *reader)
{
    reader->index = 0;
    reader->disk = file;
    load_block(reader->disk, reader->index / RECORDS_IN_BLOCK, &(reader->disk_block));
}

void writer_init(FILE** file, struct record_shell *writer)
{
    writer->index = 0;
    writer->disk = file;
}

void get_current_record(struct record *rec, struct record_shell *shell)
{
    *rec = shell->disk_block.data[shell->index % RECORDS_IN_BLOCK];
}

int load_next_record(struct record_shell *reader)
{
    reader->index = reader->index + 1;
    // check if there is a need to load new block
    if(reader->index % RECORDS_IN_BLOCK == 0)
    {
        if(load_block(reader->disk, reader->index / RECORDS_IN_BLOCK, &reader->disk_block) != 0)
        {
            // EOF
            return 1;
        }
        // assume that there is at least one valid record on newly loaded block
        return 0;
    }
    struct record rec;
    get_current_record(&rec, reader);
    // check if record in this block is valid
    if(is_null(&rec))
    {
        reader->index = reader->index - 1;
        return 2;
    }
    return 0;
}

int write_record(struct record *rec, struct record_shell *writer)
{
    writer->disk_block.data[writer->index % RECORDS_IN_BLOCK] = *rec;
    writer->index = writer->index + 1;

    if(writer->index % RECORDS_IN_BLOCK == 0)
    {
        if(save_block(writer->disk, (writer->index / RECORDS_IN_BLOCK) - 1, &writer->disk_block) != 0)
        {
            //failed to save the block
            return 1;
        }
    }
    return 0;
}

void write_end(struct record_shell *writer)
{
    // if last block was saved correctly we can return here
    if(writer->index % RECORDS_IN_BLOCK == 0)
        return;
    
    struct record rec;
    zero_record(&rec);
    while(writer->index % RECORDS_IN_BLOCK != 0)
    {
        writer->disk_block.data[writer->index % RECORDS_IN_BLOCK] = rec;
        writer->index = writer->index + 1;
    }
    if(save_block(writer->disk, (writer->index / RECORDS_IN_BLOCK) - 1, &writer->disk_block) != 0)
    {
        printf("Failed to save last block!\n");
        return;
    }
}