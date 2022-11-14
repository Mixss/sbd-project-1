#ifndef RECORD_SHELL_H
#define RECORD_SHELL_H
#include "disk_reader.h"

struct record_shell
{
    FILE** disk;
    int index;
    struct block disk_block;
} __attribute__((__packed__)); 

/* assumes that file is already opened */
void reader_init(FILE** file, struct record_shell *reader);
void get_current_record(struct record *rec, struct record_shell *reader);
/*returns 0 if record was loaded correctly*/
int load_next_record(struct record_shell *reader);
/* assumes that file is already opened */
void writer_init(FILE** file, struct record_shell *writer);
/*returns 0 if record was writed successfully*/
int write_record(struct record *rec, struct record_shell *writer);
/*it is required to run this function at the end of writing to properly save the block that wasn't fulled*/
void write_end(struct record_shell *writer);

#endif