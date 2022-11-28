#ifndef SORT_H
#define SORT_H
#include "disk_reader.h"

/*Sorts file using natural merge with 2+1 scheme*/
int sort_natural_merge(const char* filename, bool print_disk_after_phase);

#endif