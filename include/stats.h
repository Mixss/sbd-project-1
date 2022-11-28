#ifndef STATS_H
#define STATS_H

static int disk_reads = 0;
static int disk_writes = 0;

void add_read();
void add_write();
int get_reads();
int get_writes();
void set_disk_reads(int n);
void set_disk_writes(int n);

#endif