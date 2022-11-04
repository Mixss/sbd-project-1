#include "record.h"

/*44. File records: parameters a0,a1,a2,a3,a4,x.
Sorting by the value of the function g(x)=a0+a1x +a2x2+a3x3+a4x4*/
int get_record_sorting_value(struct record rec)
{
    int x = rec.x;
    return rec.a[0]  + rec.a[1] * x + rec.a[2] * x * x + rec.a[3] * x * x * x + rec.a[4] * x * x * x * x;
}