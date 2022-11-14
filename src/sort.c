#include "sort.h"
#include "record.h"
#include "data_input.h"
#include <stdbool.h>
#include <stdlib.h>

#define TAPE_1 0
#define TAPE_2 1
#define DISTRIBUTION_TAPES 2
void zero_block(struct block *b);
void distribute_new(struct record *records, int rec_counter);
void load_records(struct record *records, int *rec_counter, FILE** file);

int sort_natural_merge(FILE** file)
{
    /*
    Load all records to the array
    */
    int rec_counter = 0;
    struct record *records = malloc(MAX_RECORDS_IN_FILE * sizeof(struct record));
    load_records(records, &rec_counter, file);
    
    /*
    Distribute
    */
    distribute_new(records, rec_counter);
    free(records);
    /*
    Merge runs onto t3
    */
    FILE* tape[DISTRIBUTION_TAPES];
    tape[TAPE_1] = fopen("./data/t1", "rb");
    tape[TAPE_2] = fopen("./data/t2", "rb");
    FILE *t3 = fopen("./data/t3", "wb");
    // load records from tapes
    struct record *tape_records[DISTRIBUTION_TAPES];
    int tape_size[DISTRIBUTION_TAPES] = {0};
    for(int i=0; i<DISTRIBUTION_TAPES; i++)
    {
        tape_records[i] = malloc(MAX_RECORDS_IN_FILE * sizeof(struct record));
        load_records(tape_records[i], &tape_size[i], &tape[i]);
    }
    int no_records = tape_size[TAPE_1] + tape_size[TAPE_2];
    //determine the smallest value from two tapes
    int current_tape = get_record_sorting_value(tape_records[TAPE_1][0]) > get_record_sorting_value(tape_records[TAPE_2][0]) ? TAPE_2 : TAPE_1;
    int tape_counter[DISTRIBUTION_TAPES] = {0};
    // structures for saving
    struct block block_to_save;

    // actual merging
    for(int i=0; i<no_records; i++)
    {
        // TO JEST WSZYSTKO BEZ SENSU BO DZIELE TASMY NA BLOKI A TRZEBA PO JEDNYM BLOKU DO T3 ZAPISYWAĆ
        block_to_save.data[i % RECORDS_IN_BLOCK] = tape_records[current_tape][tape_counter[current_tape]];
        tape_counter[current_tape]++;
        // save block
        if(tape_counter[current_tape] % RECORDS_IN_BLOCK == 0)
        {
            //save_block(&tape[current_tape], (tape_counter[current_tape] / RECORDS_IN_BLOCK) - 1, &block_to_save);
            save_block_at_end(&tape[current_tape], &block_to_save);
            zero_block(&block_to_save);
        }


        // check if tapes changes.
        int tv[DISTRIBUTION_TAPES];
        for(int j = 0; j<DISTRIBUTION_TAPES; j++)
        {
            tv[j] = get_record_sorting_value(tape_records[j][tape_counter[j]]);
        }
        
        if(tv[current_tape] > tv[!current_tape])
        {
            current_tape = !current_tape;
        }
    }
    // save blocks that aren't full
    // if(tape_counter[j] % RECORDS_IN_BLOCK != 0)
    // {
    //     save_block(&tape[j], (tape_counter[j] / RECORDS_IN_BLOCK), &block_to_save);
    // }
    

    // free tapes
    fclose(tape[TAPE_1]);
    fclose(tape[TAPE_2]);
    fclose(t3);

    return 0;
}

void load_records(struct record *records, int *rec_counter, FILE** file)
{
    struct block loaded_block;
    int pos = 0;

    while(load_block(file, pos, &loaded_block) == 0)
    {
        for(int i=0; i<RECORDS_IN_BLOCK; i++)
        {
            records[*rec_counter] = loaded_block.data[i];
            (*rec_counter)++;
        }
        pos++;
    }
}

void distribute_new(struct record *records, int rec_counter)
{
    /*
    Prepare distribution tapes
    */
    FILE* tape[DISTRIBUTION_TAPES];
    tape[TAPE_1] = fopen("./data/t1", "wb");
    tape[TAPE_2] = fopen("./data/t2", "wb");

    struct block block_to_save[DISTRIBUTION_TAPES];
    zero_block(&block_to_save[TAPE_1]);
    zero_block(&block_to_save[TAPE_2]);
    /*
    Distribute
    */
    int current_tape = TAPE_1;
    int tapes_positions[DISTRIBUTION_TAPES] = {0};
    for(int i=0; i<rec_counter; i++)
    {
        // wrtie record to the tape
        block_to_save[current_tape].data[tapes_positions[current_tape] % RECORDS_IN_BLOCK] = records[i];
        tapes_positions[current_tape]++;
        if(tapes_positions[current_tape] % RECORDS_IN_BLOCK == 0)
        {
            save_block(&tape[current_tape], (tapes_positions[current_tape] / RECORDS_IN_BLOCK) - 1, &block_to_save[current_tape]);
            zero_block(&block_to_save[current_tape]);
        }
        // don't check if this was the last record
        if(i==rec_counter-1)
            break;
        // check if next record is lesser than current
        int g_x = get_record_sorting_value(records[i]);
        int g_x_p1 = get_record_sorting_value(records[i+1]);

        if(g_x_p1 < g_x) // change tapes
        {
            current_tape = current_tape == TAPE_1 ? TAPE_2 : TAPE_1;
        }
        
    }
    // save blocks that aren't full
    for(int j=0; j<DISTRIBUTION_TAPES; j++)
    {
        if(tapes_positions[j] % RECORDS_IN_BLOCK != 0)
        {
            save_block(&tape[j], (tapes_positions[j] / RECORDS_IN_BLOCK), &block_to_save[j]);
        }
    }
    /*
    Close distribution tapes
    */
    fclose(tape[TAPE_1]);
    fclose(tape[TAPE_2]);
}

void zero_block(struct block *b)
{
    struct record rec;
    zero_record(&rec);
    b->data[0] = rec;
    b->data[1] = rec;
    b->data[2] = rec;
    b->data[3] = rec;
}


void merge_runs(FILE** t3, FILE* tape[], struct block tape_block[], int tape_counter[])
{
    // merge two runs at once
    
    //find the smallest number from two runs

    //make like queue and check wich number (first in quque is bigger)

    // put the smaller one on to t3 

    //repeat with next runs
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