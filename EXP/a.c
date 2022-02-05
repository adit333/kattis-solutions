#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>


#define PAGESIZE 4096
#define HEADERPAGENUM 0

typedef uint64_t pagenum_t;

// disable byte padding
#pragma pack(push, 1)

typedef struct valueRec_t {
    int length;
    char string[PAGESIZE];
} valueRec_t;

typedef struct recordInfo_t {
    int64_t key;
    int valueSize;
} recordInfo_t;

typedef struct heapPage_t {
    int16_t startOfEmptySpace;      // 2 bytes
    char records[PAGESIZE - 10];
    pagenum_t nextPage;             // 8 bytes
} heapPage_t;

#pragma pack(pop)

int main() {
    recordInfo_t record_info = {2, 8};
    char *record_info_string = (char *)&record_info;
    recordInfo_t *record = (recordInfo_t*)record_info_string;

    char storage[1000];
    memcpy(storage, record_info_string, 13);
    char *record2 = (char *)malloc(13);
    memcpy(record2, storage, 13);
    record = (recordInfo_t*)record2;

    // valueRec_t value = {9, "lmnopqrst"};
    // char *value_string = (char*)&value;

    printf("%d\n", record->key);
}