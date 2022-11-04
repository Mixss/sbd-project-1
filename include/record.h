#ifndef RECORD_H
#define RECORD_H
#include <stdio.h>

/*44. File records: parameters a0,a1,a2,a3,a4,x.
Sorting by the value of the function g(x)=a0+a1x +a2x2+a3x3+a4x4*/
struct record 
{
    int id;
    int a[5];
    int x;
} __attribute__((packed)); 

/* computes value of the function g(x)=a0+a1x +a2x2+a3x3+a4x4*/
int get_record_sorting_value(struct record rec);
/* loads the record from disk, at given position*/
int load_record(FILE** disk, struct record* rec, int pos);
/* saves the record to the disk, at given position*/
int save_record(FILE** disk, struct record* rec, int pos);

#endif