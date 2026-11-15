#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

// 64 kb of memory 
#define capacity 64000

// initialise the memory
char heap[capacity] = {0};

// current position
size_t heap_size = 0;

typedef struct chunk {
    void* start;
    size_t size;
    bool is_free;
} chunk;

// Store current pointers(to be removed)
chunk pointers[50];
static int pointers_count = 0; // count (for maintaining index)

void* heap_alloc(size_t size) { // allocator
    for (int i = 0; i < pointers_count; i++) { // check if there are any previously freed spaces
        if (pointers[i].is_free && pointers[i].size >= size) { // if yes
            pointers[i].is_free = false; // mark are used
            if (pointers[i].size > size) { // if requested is smaller than available
                assert(pointers_count < 50);
                pointers[pointers_count].size = pointers[i].size - size; // Then break it up
                pointers[pointers_count].is_free = true;
                pointers[pointers_count].start = (char*)pointers[i].start + size;
                pointers_count++;
            }
            pointers[i].size = size;
            return pointers[i].start;
        }
    }

    assert(heap_size + size <= capacity); // requested memory may not be more than available memory
    assert(pointers_count < 50);         // can not have more than 50 pointera 

    // pointer to start of "content"
    chunk* ptr = &pointers[pointers_count];

    ptr->start = &heap[heap_size];
    ptr->size = size;
    ptr->is_free = false;

    heap_size += size; // push the start forward
    pointers_count += 1;

    return ptr->start;
}

void free_heap(void* ptr) {
    for (int i = 0; i < pointers_count; i++) {
        if (pointers[i].start == ptr) { // Find where the pointer is
            // pointers[i].start = null;
            // pointers[i].size = 0;
            pointers[i].is_free = true; // And make it available
            return;
        }
    }
    assert(false && "pointer not found"); // Else assert
}

int main(void){
    size_t mem_size = 5; // request 5

    char* first_5_characters = heap_alloc(mem_size); // pointer to start of 10
    for (size_t i = 0; i < mem_size; i++) {
        *(first_5_characters + i) = i + 'a'; // write the first 10 alphabets
    }

    // print the first 5 alphabets
    for (size_t i = 0; i < mem_size; i++) {
        printf("%c",*(first_5_characters + i));
    }
    printf("\n\n");

    mem_size = 10;
    char* next_10_characters = heap_alloc(mem_size);
    for (size_t i = 0; i < mem_size; i++) {
        *(next_10_characters+i) = i + 'f'; // write the next 10 alphabets
    }

    // print the next 10 alphabets
    for (size_t i = 0; i < mem_size; i++) {
        printf("%c",*(next_10_characters+i));
    }

    printf("\n\n");

    mem_size = 11;
    char* next_11_characters = heap_alloc(mem_size);
    for (size_t i = 0; i < mem_size; i++) {
        *(next_11_characters+i) = i + 'p'; // write the next 10 alphabets
    }

    // print the next 10 alphabets
    for (size_t i = 0; i < mem_size; i++) {
        printf("%c",*(next_11_characters+i));
    }

    printf("\n\n");

    free_heap(next_10_characters);

    mem_size = 5;
    char* first_5_numbers = heap_alloc(mem_size);
    for (size_t i = 0; i < mem_size; i++) {
        *(first_5_numbers+i) = i + '0'; // write the next 5 numbers
    }

    // print the next 5 numbers
    for (size_t i = 0; i < mem_size; i++) {
        printf("%c",*(first_5_numbers+i));
    }

    printf("\n\n");

    printf("%zu should be 26",heap_size);

    return 0;
}
