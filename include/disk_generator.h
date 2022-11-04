#ifndef DISK_GENERATOR_H
#define DISK_GENERATOR_H
#include "disk_reader.h"

void generate_disk_random(const char* filename, int number_of_blocks, int max_value);
void generate_random_record(struct record* rec, int max_value);

#endif