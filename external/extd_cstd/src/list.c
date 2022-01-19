#include <extd_cstd/lib.h>

list_t list_create(const u32 capacity) {
    list_t list;
    list.data = calloc(capacity, sizeof(void*)); 
    assert(list.data != NULL);
    list.capacity = capacity;
    list.len = 0;
    return list;
}

void list_insert(list_t * list, void * data) {
    assert(list != NULL && data != NULL);
    if (list -> len + 1 > list -> capacity) {   
        list -> capacity += 10;
        void * new_data = realloc(list -> data, list -> capacity);
        assert(new_data != NULL);
        list -> data = new_data;
    }
    list -> data[list -> len] = data;
    list -> len++; 

}

i32 list_get_len_of(const list_t list, void * data) {
    assert(data != NULL);
    for (i32 i = 0; i < list.capacity - 1; i++) {
        if (list.data[i] == data) {
            return i;
        }
    }

    return 0x0;
}

void list_rm_at(list_t * list, u32 len) {
    assert(list != NULL);
    while (len + 1 < list -> capacity) {
        list -> data[len] = list -> data[len + 1]; 
    }      
}

void list_rm_data(list_t * list, void * data) {
    assert(list != NULL && data != NULL);
    u32 len = list_get_len_of(*list, data);
    list_rm_at(list, len);
}

void list_rm(list_t * list) {
    assert(list != NULL);
    for (i32 i = 0; i < list -> capacity - 1; i++) {
        free(list -> data[i]);
    } 

    free(list -> data);
}


