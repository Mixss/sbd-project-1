#include "stats.h"

void add_read()
{
    disk_reads++;
}

void add_write()
{
    disk_writes++;
}

int get_reads()
{
    return disk_reads;
}

int get_writes()
{
    return disk_writes;
}

void set_disk_reads(int n)
{
    disk_reads = n;
}

void set_disk_writes(int n)
{
    disk_writes = n;
}