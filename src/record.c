#include "record.h"
#include "disk_reader.h"

/*44. File records: parameters a0,a1,a2,a3,a4,x.
Sorting by the value of the function g(x)=a0+a1x +a2x2+a3x3+a4x4*/
int get_record_sorting_value(struct record rec)
{
    int x = rec.x;
    return rec.a[0]  + rec.a[1] * x + rec.a[2] * x * x + rec.a[3] * x * x * x + rec.a[4] * x * x * x * x;
}

int load_record(FILE** disk, struct record* rec, int pos)
{
    int block_no = pos / RECORDS_IN_BLOCK;
    int pos_in_block = pos % RECORDS_IN_BLOCK;

    struct block loaded_block;
    if(load_block(disk, block_no, &loaded_block) != 0)
    {
        printf("Failed to load one record!\n");
        return 1;
    }

    *rec = loaded_block.data[pos_in_block];
    return 0;
}

int save_record(FILE** disk, struct record* rec, int pos)
{
    
    int block_no = pos / RECORDS_IN_BLOCK;
    int pos_in_block = pos % RECORDS_IN_BLOCK;

    struct block loaded_block;
    if(pos == 0)
    {
        struct record recz;
        zero_record(&recz);
        for(int i=0; i<RECORDS_IN_BLOCK; i++)
            loaded_block.data[i] = recz;
    }
    else if(load_block(disk, block_no, &loaded_block) == 0)
    {
        printf("Failed to load one record!\n");
        return 1;
    }
    loaded_block.data[pos_in_block] = *rec;

    if(fwrite(&loaded_block, sizeof(loaded_block), 1, *disk) < 1)
    {
        printf("Failed to save one record! %s\n", __func__);
        return 2;
    }
    return 0;
}

void zero_record(struct record* rec)
{
    (*rec).id = -1;
    (*rec).a[0] = 0;
    (*rec).a[1] = 0;
    (*rec).a[2] = 0;
    (*rec).a[3] = 0;
    (*rec).a[4] = 0;
    (*rec).x = 0;
}

void print_record(struct record* rec)
{
    printf("id=%d ->\t g(x) = %d\t\t(a0=%d, a1=%d, a2=%d, a3=%d, a4=%d, x=%d)\n", (*rec).id, get_record_sorting_value((*rec)),  (*rec).a[0], (*rec).a[1], (*rec).a[2], (*rec).a[3], (*rec).a[4], (*rec).x);
}

bool is_null(struct record *rec)
{
    return rec->id == -1 ? true : false;
}