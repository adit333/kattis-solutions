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

    int key = 8;
    valueRec_t val_rec = {3, "abc"};
    char *val = (char*)&val_rec;
	valueRec_t *value_record = (valueRec_t *)val;
	int value_size = 4 + value_record->length;
    int required_storage = 8 + value_size;

    heapPage_t *heap_page = (heapPage_t *)malloc(sizeof(heapPage_t));
    heap_page->startOfEmptySpace = 2;
    heap_page->nextPage = 0;
	char *empty_space = heap_page->records + heap_page->startOfEmptySpace; // Pointer to start of empty space
	memcpy(empty_space, &key, 8);		// Copy the key
	empty_space += 8;					// Advance pointer to now store the (value_len, value)
	memcpy(empty_space, val, value_size);
	heap_page->startOfEmptySpace += required_storage;

    char *val2 = (char *)malloc(13);
    memcpy(val2, empty_space, value_size);
    value_record = (valueRec_t *)val2;

    printf("%d\n", record->key);
}