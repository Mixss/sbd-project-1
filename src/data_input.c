#include "data_input.h"
#include <stdlib.h>

int read_data()
{

}

int load_from_text_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if(file == NULL)
    {
        printf("Failed to open specified text file.\n");
        return 1;
    }

    // load records from text file to the array
    int id;
    int x;
    int a[5];

    struct record rec;
    struct record *records = malloc(MAX_RECORDS_IN_FILE * sizeof(struct record));
    int counter = 0;
    while(fscanf(file, "%d %d %d %d %d %d %d", &id, &x, &a[0], &a[1], &a[2], &a[3], &a[4]) != EOF)
    {
        rec.id = id;
        rec.x = x;
        rec.a[0] = a[0];
        rec.a[1] = a[1];
        rec.a[2] = a[2];
        rec.a[3] = a[3];
        rec.a[4] = a[4];
        records[counter] = rec;
        counter++;
    }
    fclose(file);
    // create temp disk and fill it with records
    FILE* created_disk = fopen("./data/temp", "wb");

    save_records_to_disk(&created_disk, records, counter);
    fclose(created_disk);
    
    return 0;
}

int load_from_user_input()
{
    int id;
    int x;
    int a[5];

    struct record rec;
    struct record *records = malloc(MAX_RECORDS_IN_FILE * sizeof(struct record));
    int counter = 0;
    int numbers;
    while((numbers = scanf("%d %d %d %d %d %d %d", &id, &x, &a[0], &a[1], &a[2], &a[3], &a[4])) != EOF)
    {
        rec.id = id;
        rec.x = x;
        rec.a[0] = a[0];
        rec.a[1] = a[1];
        rec.a[2] = a[2];
        rec.a[3] = a[3];
        rec.a[4] = a[4];
        records[counter] = rec;
        counter++;
    }
    // create temp disk and fill it with records
    FILE* created_disk = fopen("./data/temp", "wb");

    save_records_to_disk(&created_disk, records, counter);
    fclose(created_disk);
    
    return 0;
}