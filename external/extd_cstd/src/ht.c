#include <extd_cstd/lib.h>


#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
u64 hash_id(const char * id) {
    assert(id != NULL);
    u64 hash = FNV_OFFSET;
    for (const char * p = id; *p; p++) {
        hash ^= (u64)(u08)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

// Capacity MUST BE power of 2
void increase_ht_capacity(ht_t * ht, u32 capacity) {
    assert(ht != NULL && capacity % 2 == 0);
    ht_t new_ht;
    new_ht.data = calloc(capacity, sizeof(ht_item_t*));
    assert(new_ht.data != NULL);
    new_ht.len = 0;
    new_ht.capacity = capacity;
    for (u64 i = 0; i < ht -> capacity; i++) {
        if (ht -> data[i] -> val != NULL) {
            ht_insert(&new_ht, ht -> data[i] -> id, ht -> data[i] -> val);
        }
    }

    ht_rm(ht);
    ht = &new_ht;
}

// - Add collision handling -> linear probing 
// - More functionality:
//  - Add          O(1)
//  - Remove       O(1) 
//  - Get          O(1)
//  - Expand       O(n)
// - Good hash function

// Capacity MUST BE power of 2
ht_t ht_create(const u32 capacity) {
    assert(capacity % 2 == 0);
    ht_t table;
    table.data = calloc(capacity, sizeof(ht_item_t*));
    assert(table.data != NULL); 
    table.len = 0;
    table.capacity = capacity;
    return table;
}

u64 ht_insert(ht_t * ht, const char * id, void * data) {
    assert(ht != NULL && id != NULL && data != NULL);
    ht_item_t * item = calloc(1, sizeof(ht_item_t));
    assert(item != NULL);
    item -> hash = hash_id(id);
    item -> id = id;
    item -> val = data;
    u64 index = item -> hash & (u64)(ht -> capacity - 1);

    ht_item_t * current = ht -> data[index];
    while (current != NULL) {
        index++;
        current = ht -> data[index];
    }

    if (index > ht -> capacity) {
        increase_ht_capacity(ht, ht -> capacity * 2);
        ht -> data[index] = item;
    }

    if (ht -> data[index] == NULL) {
        ht -> data[index] = item;
    } 

    ht -> len++;   
    return index;
} 

void * ht_get(const ht_t * ht, const char * id) {
    assert(ht != NULL && id != NULL);
    u64 index = hash_id(id) & (u64)(ht -> capacity - 1); 
    ht_item_t * data = ht -> data[index];
     
    if (data == NULL) {
        return NULL;
    }

    if (data -> val == NULL) {
        return NULL;
    }

    while (strcmp(data -> id, id) != 0) {
        index++; 
        data = ht -> data[index]; 
    }

    if (data -> val != NULL && strcmp(data -> id, id) == 0) {
        return data -> val; 
    }

    return NULL;
}


u64 ht_rm_data(ht_t * ht, const char * id) {
    assert(ht != NULL && id != NULL);
    u64 index = hash_id(id) & (u64)(ht -> capacity - 1); 
    ht_item_t * data = ht -> data[index];
    
    if (data -> val == NULL) {
        return 0;
    }

    while (strcmp(data -> id, id) != 0) {
        index++; 
        data = ht -> data[index]; 
    }

    if (data -> val != NULL && strcmp(data -> id, id) == 0) {
        data = NULL;
        ht -> data[index] = NULL;
    }
    return index;
}


void ht_rm(ht_t * ht) {
    assert(ht != NULL);
    for (u32 i = 0; i < ht -> capacity; i++) {
        free(ht -> data[i]);
    }
    free(ht -> data);   
}



