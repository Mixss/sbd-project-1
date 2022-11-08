#ifndef DATA_INPUT_H
#define DATA_INPUT_H
#include "disk_reader.h"
#include "record.h"

#define MAX_RECORDS_IN_FILE 256

/*loads records from specified text file and creates new file stream(disk) to use*/
int load_from_text_file(const char* filename);
/* user can input own data*/
int load_from_user_input();
#endif