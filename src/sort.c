#include "sort.h"
#include "record.h"
#include <stdbool.h>
#include <stdlib.h>

#define TAPE_1 0
#define TAPE_2 1
#define DISTRIBUTION_TAPES 2

int sort_natural_merge(FILE** file)
{
    FILE* tape[DISTRIBUTION_TAPES];
    FILE* t3 = *file;
    struct block t_block[DISTRIBUTION_TAPES];
    int t_counter[DISTRIBUTION_TAPES] = {0};
    struct record last_record;

    zero_record(&last_record);

    tape[TAPE_1] = fopen("./data/t1", "wrb");
    tape[TAPE_2] = fopen("./data/t2", "wrb");

    printf("Sorting started...\n");

    distribute(&t3, tape, t_block, t_counter);
    fill_blocks(tape, t_block, t_counter);
    //t3 = fopen("./data/t3", "wrb");



    fclose(tape[TAPE_1]);
    fclose(tape[TAPE_2]);
    return 0;

}

void merge_tapes(FILE** target_tape, FILE* tapes[], unsigned int number_of_records)
{
    struct block loaded_block;
    int pos = 0;
    struct record* records = malloc(number_of_records * sizeof(struct record));
    int records_counter = 0;

    while(load_block(target_tape, pos, &loaded_block) == 0)
    {
        for(int i=0; i<RECORDS_IN_BLOCK; i++)
        {
            records[records_counter] = loaded_block.data[i];
        }
    }




    free(records);
}

void distribute(FILE** t3, FILE* tape[], struct block tape_block[], int tape_counter[])
{
    int pos = 0;
    struct block loaded_block;

    struct record rec;
    struct record last_record;  

    int g_x;
    int current_tape = TAPE_1;

    bool new_run = true;

    while(load_block(t3, pos, &loaded_block) == 0)
    {
        for(int i=0; i<RECORDS_IN_BLOCK; i++)
        {
            rec = loaded_block.data[i];
            g_x = get_record_sorting_value(rec);
            // if g_x is greater than in last record in tape save it in 
            if(g_x >= get_record_sorting_value(last_record) || new_run)
            {
                new_run = false;
                // save this record to the block on current tape
                tape_block[current_tape].data[tape_counter[current_tape] % RECORDS_IN_BLOCK] = rec;
                tape_counter[current_tape] += 1;

                // save block to tape if its full
                if(tape_counter[current_tape] % RECORDS_IN_BLOCK == 0)
                {
                    if(save_block(&tape[current_tape], tape_counter[current_tape] / RECORDS_IN_BLOCK - 1, &tape_block[current_tape]) != 0)
                    {
                        printf("Error saving block to the tape!\n");
                        return;
                    }
                    //printf("Saved block to tape %d\n", current_tape+1);
                }
                last_record = rec;
            }
            else 
            {
                // change distribution tape
                if(current_tape == TAPE_1)
                    current_tape = TAPE_2;
                else current_tape = TAPE_1;
                // back the counter to save the record on other tape
                i--;
                new_run = true;
            }
        }
        pos++;
    }
    printf("Wykryto %d bloków\n", pos);
}

void fill_blocks(FILE* tape[], struct block t_block[], int t_counter[])
{
    struct record rec_zero;
    zero_record(&rec_zero);

    for(int i=0; i<DISTRIBUTION_TAPES; i++)
    if(t_counter[i] % RECORDS_IN_BLOCK != 0)
    {
        while(t_counter[i] % RECORDS_IN_BLOCK != 0)
        {
            t_block[i].data[t_counter[i] % RECORDS_IN_BLOCK] = rec_zero;
            t_counter[i] += 1;
        }
        save_block(&tape[i], t_counter[i] / RECORDS_IN_BLOCK - 1, &t_block[i]);
    }
}