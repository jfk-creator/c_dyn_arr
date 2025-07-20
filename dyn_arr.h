#ifndef DYN_ARR_H_
#define DYN_ARR_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t count; 
    size_t size;
    uint64_t cursor;
    void* start; 
} Dyn; 
static inline int Init_dyn(Dyn *dyn, size_t size){
    dyn->count = 10;
    dyn->size = size;
    dyn-> cursor = 0;
    dyn->start = malloc(dyn->count*size);
    if(dyn->start == NULL) return -1;
    return 0;
} 
static inline int Grow_dyn(Dyn *dyn){
    void *new_start = malloc(dyn->count*dyn->size *2);
    memcpy(new_start, dyn->start, (dyn->size*dyn->count));
    dyn->count *= 2;
    dyn->start = new_start;
    return 0;
}
static inline void Push_dyn(Dyn *dyn, void *value){
    if(dyn->count <= dyn->cursor) Grow_dyn(dyn); 
    void *insert = dyn->start + (dyn->size) * dyn->cursor;
    dyn->cursor += 1;
    memcpy(insert, value, dyn->size);
    return;
}
static inline int Set_dyn(Dyn *dyn, uint64_t place, void *value){
    if(place >= dyn->count) return -1;
    void *insert = dyn->start + (dyn->size) * place;
    memcpy(insert, value, dyn->size);
    return 0;
}
static inline int Insert_dyn(Dyn *dyn, uint64_t place, void *value){
    if(place >= dyn->count) return -1; 
    if(dyn->count <= dyn->cursor +1) Grow_dyn(dyn);
    void *insert = dyn->start + (dyn->size) * place;
    int amount = dyn->cursor - place;
    memcpy(insert + dyn->size, insert, dyn->size * amount);
    dyn->cursor += 1;
    memcpy(insert, value, dyn->size);
    return 0;
}
static inline void *Get_dyn(Dyn *dyn, uint64_t place){
    if(place >= dyn->cursor) return NULL;
    return dyn->start + (dyn->size) * place;
}
static inline void *For_each_dyn(Dyn *dyn, int (*func)(void*, void*, int64_t), void *func_args){
    for(int64_t i = 0; i < dyn->cursor; i += 1) {
        void *iterator = dyn->start + (dyn->size * i);
        int return_value = func(iterator, func_args, i);
        if(return_value != 0) return NULL;
    }
    return func_args;
}
#endif
