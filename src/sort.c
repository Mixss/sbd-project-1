#include "sort.h"
#include "record.h"
#include "data_input.h"
#include <stdbool.h>
#include <stdlib.h>
#include "record_shell.h"
#include "stats.h"

// assumes that input_tape_reader is initialized
void distribute(FILE* tapes[], FILE** input_tape, struct record_shell* input_tape_reader);
// retunrs true if t3 is sorted after merging
bool merge(FILE* tapes[], FILE** t3);

#define TAPE_1 0
#define TAPE_2 1
#define DISTRIBUTION_TAPES 2

#define T1_LOCATION "./data/t1"
#define T2_LOCATION "./data/t2"
#define T3_LOCATION "./data/t3"


int sort_natural_merge(const char* filename, bool print_disk_after_phase)
{
    int phase = 1;
    
    FILE* file = fopen(filename, "rb");
    if(!file)
    {
        printf("Failed to load disk!\n");
        return 1;
    }
    
    struct record_shell reader;
    reader_init(&file, &reader);
    FILE* t3;
    bool sorted = false;
    
    FILE* tapes[DISTRIBUTION_TAPES];

    tapes[0] = fopen(T1_LOCATION, "wb");
    tapes[1] = fopen(T2_LOCATION, "wb");

    distribute(tapes, &file, &reader);

    fclose(tapes[0]);
    fclose(tapes[1]);
    t3 = fopen(T3_LOCATION, "wb");
    tapes[0] = fopen(T1_LOCATION, "rb");
    tapes[1] = fopen(T2_LOCATION, "rb");

    sorted = merge(tapes, &t3);

    fclose(tapes[0]);
    fclose(tapes[1]);
    fclose(t3);
    fclose(file);

    while(!sorted)
    {
        t3 = fopen(T3_LOCATION, "rb");
        
        if(print_disk_after_phase)
        {
            printf("\nDisk after phase %d of sorting:\n", phase);
            print_disk(&t3);
        }
        
        
        reader_init(&t3, &reader);
        tapes[0] = fopen(T1_LOCATION, "wb");
        tapes[1] = fopen(T2_LOCATION, "wb");

        distribute(tapes, &t3, &reader);

        fclose(tapes[0]);
        fclose(tapes[1]);
        t3 = fopen(T3_LOCATION, "wb");
        tapes[0] = fopen(T1_LOCATION, "rb");
        tapes[1] = fopen(T2_LOCATION, "rb");

        sorted = merge(tapes, &t3);

        fclose(tapes[0]);
        fclose(tapes[1]);
        fclose(t3);

        phase++;
        
    }

    t3 = fopen(T3_LOCATION, "rb"); 
    file = fopen(filename, "wb");   
    copy_disk(&t3, &file);
    fclose(t3);
    fclose(file);

    printf("\nSort has ended in %d phases with %d disk reads and %d disk writes\n", phase, get_reads(), get_writes());

    return 0;
}

void distribute(FILE* tapes[], FILE** input_tape, struct record_shell* input_tape_reader)
{
    int current_tape = TAPE_1;
    int last_record_value = -__INT_MAX__;
    struct record loaded_record;
    struct record_shell tape_writers[DISTRIBUTION_TAPES];
    writer_init(&tapes[0], &tape_writers[0]);
    writer_init(&tapes[1], &tape_writers[1]);
    int record_value;
    do 
    {
        get_current_record(&loaded_record, input_tape_reader);
        record_value = get_record_sorting_value(loaded_record);
        // check if there is a new run
        if(last_record_value > record_value)
        {
            current_tape = current_tape == TAPE_1 ? TAPE_2 : TAPE_1;
        }
        
        write_record(&loaded_record, &tape_writers[current_tape]);
        last_record_value = record_value;


    } while(load_next_record(input_tape_reader) == 0);

    write_end(&tape_writers[0]);
    write_end(&tape_writers[1]);
}

bool merge(FILE* tapes[], FILE** t3)
{
    struct record loaded_records[DISTRIBUTION_TAPES];
    int record_to_save_value;
    struct record_shell tape_readers[DISTRIBUTION_TAPES];
    struct record_shell t3_writer;
    writer_init(t3, &t3_writer);
    reader_init(&tapes[0], &tape_readers[0]);
    reader_init(&tapes[1], &tape_readers[1]);

    bool sorted = true;
    // the value of the last pur record to t3
    int last_put_element = -__INT_MAX__;
    int record_current_values[DISTRIBUTION_TAPES];
    int last_record_values[DISTRIBUTION_TAPES];
    last_record_values[0] = -__INT_MAX__;
    last_record_values[1] = -__INT_MAX__;
    // flag indicating if run has ended
    bool runs[DISTRIBUTION_TAPES];
    runs[0] = true;
    runs[1] = true;
    // flag indicating if tape has ended
    bool ends[DISTRIBUTION_TAPES] = {0};
    int current_tape = TAPE_1;

    while(1)
    {
        get_current_record(&loaded_records[0], &tape_readers[0]);
        get_current_record(&loaded_records[1], &tape_readers[1]);
        record_current_values[0] = get_record_sorting_value(loaded_records[0]);
        record_current_values[1] = get_record_sorting_value(loaded_records[1]);
        
        // check if two runs has ended
        if (runs[0] == false && runs[1] == false)
        {
            if(ends[0] && ends[1])
                break;
            runs[0] = ends[0] == false ? true : false;
            runs[1] = ends[1] == false ? true : false;
            last_record_values[0] = -__INT_MAX__;
            last_record_values[1] = -__INT_MAX__;
            continue;
        }
        
        // if two runs are still going decide which tape should be current
        if(runs[0] && runs[1])
        {
            current_tape = record_current_values[0] < record_current_values[1] ? 0 : 1;
        }
        else // if one of the runs has ended select second one
        {
            current_tape = runs[0] == false ? 1 : 0;
        }

        record_to_save_value = get_record_sorting_value(loaded_records[current_tape]);

        write_record(&loaded_records[current_tape], &t3_writer);
        if (last_put_element > record_to_save_value)
            {
                sorted = false;
            }

        last_put_element = record_to_save_value;
        last_record_values[current_tape] = record_to_save_value;

        // load and check if tape has ended
        if(load_next_record(&tape_readers[current_tape]) != 0)
        {
            ends[current_tape] = true;
            runs[current_tape] = false;
        }
        else // check if run ended
        {
            get_current_record(&loaded_records[current_tape], &tape_readers[current_tape]);
            if(last_record_values[current_tape] > get_record_sorting_value(loaded_records[current_tape]))
            {
                runs[current_tape] = false;
            }
        }

    }

    write_end(&t3_writer);

    return sorted;
}