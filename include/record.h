#ifndef RECORD_H
#define RECORD_H

/*44. File records: parameters a0,a1,a2,a3,a4,x.
Sorting by the value of the function g(x)=a0+a1x +a2x2+a3x3+a4x4*/
struct record 
{
    int id;
    int a[5];
    int x;
} __attribute__((packed)); 

int get_record_sorting_value(struct record rec);

#endif