#ifndef LIST_H
    #define LIST_H
    #include "./types.h"

    typedef struct {
        void ** data;
        u32     capacity;
        u32     len;
    } list_t;

    list_t list_create    (const u32 capacity);
    void   list_insert    (list_t * list, void * data);
    i32    list_get_idx_of(const list_t list, void * data);
    void   list_rm_at     (list_t * list, u32 idx);
    void   list_rm_data   (list_t * list, void * data);
    void   list_rm        (list_t * list);

    #define list_get_at(list, index) \
        list.data[index]

    #define list_get_data(list, data) \
        get_at_list(list, get_list_idx(&list, (void *)data))

#endif
