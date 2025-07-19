#ifndef DYN_ARR_H_
#define DYN_ARR_H_

typedef struct {
    uint64_t count; 
    size_t size;
    uint64_t cursor;
    void* start; 
} Dyn; 


int Init_dyn(Dyn *dyn, size_t size){
    dyn->count = 10;
    dyn->size = size;
    dyn-> cursor = 0;
    dyn->start = malloc(dyn->count*size);
    if(dyn->start == NULL) return -1;
    return 0;
} 
int Grow_dyn(Dyn *dyn){
    void *new_start = malloc(dyn->count*dyn->size *2);
    memcpy(new_start, dyn->start, (dyn->size*dyn->count));
    dyn->count *= 2;
    dyn->start = new_start;
    return 0;
}
void Push_dyn(Dyn *dyn, void *value){
    if(dyn->count <= dyn->cursor) Grow_dyn(dyn); 
    void *insert = dyn->start + (dyn->size) * dyn->cursor;
    dyn->cursor += 1;
    memcpy(insert, value, dyn->size);
    return;
}
int Insert_dyn(Dyn *dyn, uint64_t place, void *value){
    if(place >= dyn->count) return -1;
    void *insert = dyn->start + (dyn->size) * place;
    memcpy(insert, value, dyn->size);
    return 0;
}
void* Get_dyn(Dyn *dyn, uint64_t place){
    if(place >= dyn->count) return NULL;
    return dyn->start + (dyn->size) * place;
    
}
#endif
