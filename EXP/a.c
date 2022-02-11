#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>


#define PAGESIZE 4096
#define HEADERPAGENUM 0
#define KEY_SIZE 8   // 8 bytes for the key
#define VALUE_LENGTH_SIZE 4
#define RESERVED_SPACE_AT_START_HEAP_PAGE 2
#define RESERVED_SPACE_AT_END_HEAP_PAGE 8
#define RESERVERD_SPACE_IN_HEAP_PAGE 10

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


void insert_record(heapPage_t *heap_page, int64_t key, char *val) {
	valueRec_t *value_record = (valueRec_t *)val;
	int value_size = VALUE_LENGTH_SIZE + value_record->length;
    int required_storage = KEY_SIZE + value_size;  // = 15

	char *empty_space = heap_page->records + heap_page->startOfEmptySpace; // Pointer to start of empty space
	memcpy(empty_space, &key, KEY_SIZE);		// Copy the key
	empty_space += KEY_SIZE;					// Advance pointer to now store the (value_len, value)
	memcpy(empty_space, val, value_size);
	heap_page->startOfEmptySpace += required_storage;
}

heapPage_t* init() {
    // Create heap page
    heapPage_t *heap_page = (heapPage_t *)malloc(sizeof(heapPage_t));
    heap_page->startOfEmptySpace = 2;
    heap_page->nextPage = 0;

    // Record 1 - size 15
    int64_t key = 8;
    valueRec_t val_rec = {3, "abc"};
    char *val = (char*)&val_rec;

    // Record 2 - size 16
    int64_t key2 = 16;
    valueRec_t val_rec2 = {4, "defg"};
    char *val2 = (char*)&val_rec2;

    // Record 3 - size 17
    int64_t key3 = 32;
    valueRec_t val_rec3 = {5, "hijkl"};
    char *val3 = (char*)&val_rec3;

    // Insert Record 1 Expected start_of_record = 2
    insert_record(heap_page, key, val);
    // Insert record 2 - Expected start_of_record is 17
    insert_record(heap_page, key2, val2);
    // Insert record 3 - Expected start_of_record is 33 and startSpace is 50
    insert_record(heap_page, key3, val3);

    return heap_page;
}

bool is_key_in_page(int64_t key, heapPage_t *heap_page, int *start_of_record_offset) {
	char *pointer_to_end_of_records = heap_page->records + heap_page->startOfEmptySpace;
	char *pointer_to_record = heap_page->records + RESERVED_SPACE_AT_START_HEAP_PAGE;	// First record

	bool found = false;
	int64_t record_key;
	while (pointer_to_record < pointer_to_end_of_records) {
		memcpy(&record_key, pointer_to_record, KEY_SIZE);
		if (record_key == key) {
			found = true;
			break;
		}
		int record_value_length;
		memcpy(&record_value_length, pointer_to_record + KEY_SIZE, VALUE_LENGTH_SIZE);
		pointer_to_record = pointer_to_record + KEY_SIZE + VALUE_LENGTH_SIZE + record_value_length;
	}
	if (found) {
		*start_of_record_offset = pointer_to_record - heap_page->records;
		return true;
	} else {
		return false;
	}
}

void test_find(){
    // Create heap page
    heapPage_t *heap_page = init();

    // Now find the record
    int start_of_record_offset;
    bool key_present = is_key_in_page(16, heap_page, &start_of_record_offset);
    printf("%d, %d\n", key_present, start_of_record_offset);


    char *result = (char *)malloc(15);
	char *pointer_to_record = heap_page->records + start_of_record_offset;
	int record_value_length;
	memcpy(&record_value_length, pointer_to_record + KEY_SIZE, VALUE_LENGTH_SIZE);
	memcpy(result, pointer_to_record + KEY_SIZE, VALUE_LENGTH_SIZE + record_value_length);
    valueRec_t *result_record = (valueRec_t *)result;
    printf("%d, %s\n", result_record->length, result_record->string);
}

void test_delete() {
    // Create heap page
    heapPage_t *heap_page = init();

    // Now find the record
    int start_of_record_offset;
    bool key_present = is_key_in_page(16, heap_page, &start_of_record_offset);

    // Now delete the record
	char *pointer_to_record = heap_page->records + start_of_record_offset;
	int record_value_length;
	memcpy(&record_value_length, pointer_to_record + KEY_SIZE, VALUE_LENGTH_SIZE);

	int size_of_record_to_be_deleted = KEY_SIZE + VALUE_LENGTH_SIZE + record_value_length;
	char *pointer_to_record_following_the_record_to_be_deleted = pointer_to_record + \
		size_of_record_to_be_deleted;
	char *pointer_to_start_of_empty_space = heap_page->records + heap_page->startOfEmptySpace;
	int size_of_records_following_the_record_to_be_deleted = pointer_to_start_of_empty_space - \
		pointer_to_record_following_the_record_to_be_deleted;

	char *temp = (char *)malloc(PAGESIZE);
	memcpy(temp, pointer_to_record_following_the_record_to_be_deleted, \
		size_of_records_following_the_record_to_be_deleted);
	memcpy(pointer_to_record, temp, size_of_records_following_the_record_to_be_deleted);
	free(temp);
	heap_page->startOfEmptySpace -= size_of_record_to_be_deleted;

    printf("%dSize of record delete: %d\n", size_of_record_to_be_deleted);
    printf("Start of empty space: %d\n", heap_page->startOfEmptySpace);
}


void test_update() {
    heapPage_t *heap_page = init();
    // Now update the record
    int start_of_record_offset;
    bool key_present = is_key_in_page(32, heap_page, &start_of_record_offset);

    // Now update the record
	char *pointer_to_record = heap_page->records + start_of_record_offset;
	int record_value_length;
	memcpy(&record_value_length, pointer_to_record + KEY_SIZE, VALUE_LENGTH_SIZE);

    valueRec_t val_rec_new = {4, "wxyza"};
    char *val_new = (char*)&val_rec_new;
	valueRec_t *val_record = (valueRec_t *)val_new;
	if (val_record->length == record_value_length) {	// Update row in-place
		memcpy(pointer_to_record + KEY_SIZE, val_new, VALUE_LENGTH_SIZE + record_value_length);
	} else {
        int a = 1;
	}
}

int main(){
    // test_find();
    test_delete();
    // test_update();
}