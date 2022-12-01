#include "data_input.h"
#include <stdlib.h>
#include "record_shell.h"

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

    FILE* created_disk = fopen("./data/temp", "wb");

    struct record rec;
    struct record_shell writer;
    writer_init(&created_disk, &writer);
    while(fscanf(file, "%d %d %d %d %d %d %d", &id, &x, &a[0], &a[1], &a[2], &a[3], &a[4]) != EOF)
    {
        rec.id = id;
        rec.x = x;
        rec.a[0] = a[0];
        rec.a[1] = a[1];
        rec.a[2] = a[2];
        rec.a[3] = a[3];
        rec.a[4] = a[4];
        write_record(&rec, &writer);
    }
    write_end(&writer);

    fclose(file);
    fclose(created_disk);
    
    return 0;
}

int load_from_user_input()
{
    int id;
    int x;
    int a[5];

    FILE* created_disk = fopen("./data/temp", "wb");

    struct record rec;
    struct record_shell writer;
    writer_init(&created_disk, &writer);
    printf("Type in data in format: 'id x a0 a1 a2 a3 a4' separated with spaces:\n");
    while(scanf("%d %d %d %d %d %d %d", &id, &x, &a[0], &a[1], &a[2], &a[3], &a[4]) != EOF)
    {
        rec.id = id;
        rec.x = x;
        rec.a[0] = a[0];
        rec.a[1] = a[1];
        rec.a[2] = a[2];
        rec.a[3] = a[3];
        rec.a[4] = a[4];
        write_record(&rec, &writer);
    }
    // create temp disk and fill it with records
    write_end(&writer);

    fclose(created_disk);
    
    return 0;
}